<?php

/**
 * Jun 15, 2012
 * @file auction.bids.inc
 * @author blazey http://drupal.org/user/353861
 */

function auction_bids_form($form, &$form_state, $auction, $view_mode, $langcode) {
  global $user;
  $controller = auction_get_controller();

  $form_state['auction']['auction'] = $auction;
  $form_state['auction']['minimum'] = auction_get_minimum_bid_value($auction);
  $form_state['auction']['current_price'] = auction_get_current_price($auction);
  $form_state['auction']['currency'] = auction_get_settings('currency');

  if ($controller->isBiddingActive($auction)) {
    $form['current_price'] = array(
      '#type' => 'item',
      '#title' => t('Current price'),
      '#markup' => auction_format_price($form_state['auction']['current_price'] * 100),
      '#field_suffix' => $form_state['auction']['currency'],
    );

    if ($controller->userIsWinning($auction, $user->uid)) {
      $highest_bid = $controller->getHighestBidAmount($auction);
      $title = t('Your new bid');
      $default_value = $highest_bid + $controller->getBidStep($auction);
      $description = t('Your last bid is @amount', array('@amount' => $highest_bid));
    }
    else {
      $title = t('Your bid');
      $default_value = $form_state['auction']['minimum'];
      $description = '';
    }
    $form['bid_amount'] = array(
      '#type' => 'textfield',
      '#title' => $title,
      '#default_value' => $default_value,
      '#required' => TRUE,
      '#field_suffix' => $form_state['auction']['currency'],
      '#size' => 10,
      '#element_validate' => array('auction_bids_bid_amount_validate'),
      '#description' => $description,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Place a bid'),
      '#submit' => array('auction_bids_place_a_bid_submit'),
    );
  }

  if ($controller->isInstantBuyActive($auction)) {
    $form_state['auction']['instant_buy_price'] = $controller->getInstantBuyPrice($auction);

    $form['price'] = array(
      '#type' => 'item',
      '#title' => t('Instant buy price'),
      '#markup' => auction_format_price($controller->getInstantBuyPrice($auction), $auction->currency_code),
    );
    $form['instant_buy_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Buy now'),
      '#validate' => array('auction_bids_instant_buy_validate'),
    );

    return $form;
  }

  return $form;
}

function auction_bids_bid_amount_validate($element, &$form_state, $form) {
  if ($form_state['values']['op'] == t('Place a bid')) {
    $controller = auction_get_controller();
    // We load auction again to make sure it' it's active.
    $auction = $controller->changeStatusIfNeeded($form_state['auction']['auction']);

    if ($auction->status != AUCTION_STATUS_ACTIVE) {
      form_set_error('', t('Auction has ended.'));
    }
    else {
      $current_minimum = auction_get_minimum_bid_value($form_state['auction']['auction']);
      if ($element['#value'] < $current_minimum) {
        form_error($element, t('Your bid amount is too low. It has to be at least @minimum',
                array('@minimum' => $current_minimum . ' ' . $form_state['auction']['currency'])));
      }
      else {
        global $user;
        $controller = auction_get_controller();
        if ($controller->userIsWinning($form_state['auction']['auction'], $user->uid)) {
          $highest_bid_amount = $controller->getHighestBidAmount($form_state['auction']['auction']);
          if ($element['#value'] <= $highest_bid_amount) {
            form_error($element, t('Your bid amount is too low. It has to be at least @minimum',
                  array('@minimum' => $highest_bid_amount . ' ' . $form_state['auction']['currency'])));
          }
        }
      }
    }
  }
}

function auction_bids_place_a_bid_submit($form, &$form_state) {
  global $user;
  $controller = auction_get_controller();
  if ($controller->userIsWinning($form_state['auction']['auction'], $user->uid)) {
    $bid_id = $controller->getHighestBid($form_state['auction']['auction'])->bid_id;
  }
  else {
    $bid_id = NULL;
  }

  if ($controller->getHighestBidAmount($form_state['auction']['auction']) == $form_state['values']['bid_amount']) {
    drupal_set_message(t(
      'You\'ve been outbid by @username, because this user bet the same amount first.',
      array('@username' => auction_mask_username($controller->getWinningUserName($form_state['auction']['auction'])))
    ), 'warning');
  }
  elseif ($controller->getHighestBidAmount($form_state['auction']['auction']) > $form_state['values']['bid_amount']) {
    drupal_set_message(t(
      'You\'ve been outbid by @username.',
      array('@username' => auction_mask_username($controller->getWinningUserName($form_state['auction']['auction'])))
    ), 'warning');
  }
  else {
    drupal_set_message(t('Your bid has been saved.'));
  }

  $controller->saveBid(
          $form_state['auction']['auction'],
          $form_state['values']['bid_amount'],
          $form_state['auction']['currency'],
          $user->uid,
          AUCTION_BID_TYPE_STANDARD,
          $bid_id
  );
}

function auction_bids_instant_buy_validate($form, &$form_state) {
  global $user;
  $controller = auction_get_controller();

  // We load auction again to make sure it' it's active.
  $auction = $controller->changeStatusIfNeeded($form_state['auction']['auction']);

  if ($auction->status == AUCTION_STATUS_ACTIVE) {
    $controller->saveBid(
          $auction,
          $form_state['auction']['instant_buy_price'] / 100,
          $form_state['auction']['currency'],
          $user->uid,
          AUCTION_BID_TYPE_INSTANT_BUY,
          NULL
    );
    $controller->deactivate($auction);
  }
  else {
    form_set_error('', t('Auction has ended.'));
  }
}

/**
 * Return links to bidders profiles.
 *
 * @param array $variables
 * @return string
 */
function theme_auction_bids_overview($variables) {
  $output = '';
  foreach ($variables['bids'] as $bid) {
    $output .= auction_bids_format_bid_overview_row($bid) . "\n";
  }
  return $output;
}

/**
 * Returns human-readable information about single bid.
 *
 * @param stdClass $bid
 * @return string
 */
function auction_bids_format_bid_overview_row(&$bid) {
  $name = db_select('users', 'u')
          ->fields('u', array('name'))
          ->condition('uid', $bid->uid)
          ->execute()
          ->fetchColumn();

  $output = auction_format_price($bid->amount, $bid->currency_code) . ' - '
          . l($name, 'user/' . $bid->uid) . ' - ';

  $output .= $bid->type == AUCTION_BID_TYPE_STANDARD ? 'standard bid' : 'instant buy';
  return $output;
}
