<?php

/**
 * Jun 3, 2012
 * @file auction.controller.inc
 * @author blazey http://drupal.org/user/353861
 */

class AuctionEntityController extends EntityAPIController {

  /**
   * Create a generic auctiln.
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   * @return
   *   An auction object with all default fields initialized.
   */
  public function create(array $values = array()) {
    global $user;
    $values += array(
      'auction_id' => '',
      'is_new' => TRUE,
      'uid' => $user->uid,
      'current_price' => 0,
      'currency_code' => auction_get_settings('currency'),
      'type' => 'auction',
      'relisted' => 0,
      'bids' => array(),
      'changed' => '',
      'status' => AUCTION_STATUS_NOT_YET_STARTED,
    );

    return parent::create($values);
  }

  /**
   * Builds a structured array representing the entity's content.
   *
   * The content built for the entity will vary depending on the $view_mode
   * parameter.
   *
   * @param $entity
   *   An entity object.
   * @param $view_mode
   *   View mode, e.g. 'full', 'teaser'...
   * @param $langcode
   *   (optional) A language code to use for rendering. Defaults to the global
   *   content language of the current request.
   * @return
   *   The renderable array.
   */
  public function buildContent($auction, $view_mode = 'full', $langcode = NULL, $content = array()) {
    module_load_include('inc', 'auction', 'auction.bids');
    $content = parent::buildContent($auction, $view_mode, $langcode, $content);
    $content['#attached']['css'][] = drupal_get_path('module', 'auction') . '/css/auction.view.css';

    $content['countdown'] = array(
      '#type' => 'item',
      '#title' => t('Auction ends in'),
      '#markup' => '<div id="countdown-' . $auction->auction_id . '"></div>',
      '#weight' => -15,
      '#access' => $auction->status == AUCTION_STATUS_ACTIVE,
    );
    jquery_countdown_add("#countdown-" . $auction->auction_id, array("until" => $this->getSecondsUntilEnd($auction), "onExpiry" => "auctionEnded"));
    drupal_add_js("function auctionEnded() { window.location.href = window.location.href; }", 'inline');

    if (!empty($auction->field_auction_rate_card_price[LANGUAGE_NONE][0]['value'])) {
      $content['rate_card_price'] = array(
        '#type' => 'item',
        '#title' => t('Rate card price'),
        '#markup' => auction_format_price($auction->field_auction_rate_card_price[LANGUAGE_NONE][0]['value'] * 100),
        '#field_suffix' => $auction->currency_code,
      );
    }

    if (user_access('view bids')) {
      $view = views_get_view('auction_bids');
      $history = $view->preview(NULL, array($auction->auction_id));
      $content['bids'] = array(
        '#theme' => 'auction_bids',
      );
    }
    else {
      $history = '';
    }
    switch (auction_get_status($auction)) {
      case AUCTION_STATUS_NOT_YET_STARTED:
        $content['bids']['#form'] = t('Auction is inactive.');
        break;

      case AUCTION_STATUS_ACTIVE:
        $content['bids']['#history'] = $history;

        // Attach bids form if user has access.
        if (auction_entity_access('bid', $auction)) {
          $form = drupal_get_form('auction_bids_form', $auction, $view_mode, $langcode);
          $content['bids']['#form'] = drupal_render($form);
        }
        break;

      case AUCTION_STATUS_FINISHED:
        $content['bids']['#history'] = $history;
        $content['bids']['#form'] = t('Auction has finished.');
        break;
    }
    return $content;
  }

  /**
   * Implements EntityAPIControllerInterface.
   *
   * @param $transaction
   *   Optionally a DatabaseTransaction object to use. Allows overrides to pass
   *   in their transaction object.
   */
  public function delete($ids, DatabaseTransaction $transaction = NULL) {
    parent::delete($ids, $transaction);
    foreach ($ids as $auction_id) {
      db_delete('auction_bids')->condition('auction_id', $auction_id)->execute();
    }
  }

  /**
   * Saves an auction.
   *
   * @param $auction
   *   The full auction object to save.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   SAVED_NEW or SAVED_UPDATED depending on the operation performed.
   */
  public function save($auction, DatabaseTransaction $transaction = NULL) {
    $auction->changed = REQUEST_TIME;

    $auction->is_new = empty($auction->auction_id);

    if (empty($auction->{$this->idKey}) || !empty($auction->is_new)) {
      // Set the creation timestamp if not set, for new entities.
      if (empty($auction->created)) {
        $auction->created = REQUEST_TIME;
      }
    }

    if (empty($auction->uid)) {
      global $user;
      $auction->uid = $user->uid;
    }

    if (!isset($auction->status)) {
      $auction->status = AUCTION_STATUS_NOT_YET_STARTED;
    }

    if (!isset($auction->bids)) {
      $auction->bids = array();
    }

    if ($auction->status == AUCTION_STATUS_FINISHED) {
      $auction->current_price = $this->determineFinishedAuctionPrice($auction) * 100;
    }
    else {
      $auction->current_price = $this->determineCurrentPrice($auction->bids, $this->getStartingPrice($auction)) * 100;
    }

    $auction->currency_code = empty($auction->bids) ? auction_get_settings('currency') : $auction->bids[0]->currency_code;

    return parent::save($auction, $transaction);
  }

  /**
   * Overridden.
   * @see EntityAPIController#load($ids, $conditions)
   */
  public function load($ids = array(), $conditions = array()) {
    $auctions = parent::load($ids, $conditions);
    foreach ($auctions as &$auction) {
      if (isset($auction->auction_id)) {
        $this->attachBids($auction);
        $auction = $this->changeStatusIfNeeded($auction);
      }
    }
    return $auctions;
  }

  /**
   * Attaches bids to auction entity.
   *
   * @param stdClass $auction
   */
  public function attachBids(&$auction) {
    $auction->bids = db_select('auction_bids', 'ab')
                          ->fields('ab')
                          ->condition('auction_id', $auction->auction_id)
                          ->orderBy('type', 'DESC')
                          ->orderBy('amount', 'DESC')
                          ->orderBy('created', 'ASC')
                          ->execute()
                          ->fetchAll();
  }

  /**
   * Saves a bid.
   *
   * @param stdClass $auction
   * @param int $amount
   * @param string $currency
   * @param int $uid
   * @param int $type
   * @param int $bid_id
   */
  function saveBid($auction, $amount, $currency, $uid, $type, $bid_id = NULL) {
    $controller = auction_get_controller();

    $outbid_user = new stdClass();
    $outbid_user_id = $controller->getWinningUserId($auction);
    if ($outbid_user_id && $outbid_user_id != $uid) {
      $outbid_user = user_load($outbid_user_id);
    }

    $record = array(
      'auction_id' => $auction->auction_id,
      'type' => $type,
      'uid' => $uid,
      'amount' => $amount * 100,
      'currency_code' => $currency,
      'created' => time(),
      'changed' => time()
    );
    $primary = array();
    if (!is_null($bid_id)) {
      $record['bid_id'] = $bid_id;
      $primary = array('bid_id');
      unset($record['created']);
    }
    drupal_write_record('auction_bids', $record, $primary);

    $controller->updateCurrentPrice($auction);
    $auction_node = $controller->getAuctionParentNode($auction);
    $bidder = user_load($uid);
    rules_invoke_all('auction_bid_placed', $auction, $bidder, $outbid_user, $auction_node);
  }

  /**
   * Activates an auction.
   *
   * @param stdClass $auction
   */
  public function activate($auction) {
    $controller = auction_get_controller();
    $auction_node = $controller->getAuctionParentNode($auction);
    rules_invoke_all('auction_started', $auction, $auction_node);

    $auction->status = AUCTION_STATUS_ACTIVE;

    $this->save($auction);

    return $auction;
  }

  /**
   * Activates an auction.
   *
   * @param stdClass $auction
   */
  public function deactivate($auction) {
    $controller = auction_get_controller();
    $auction_node = $controller->getAuctionParentNode($auction);
    rules_invoke_all('auction_finished', $auction, $auction_node);

    $auction->status = AUCTION_STATUS_FINISHED;

    $this->save($auction);

    return $auction;
  }

  /**
   * Returns node that references target auction.
   *
   * @param stdClass $auction
   * @return stdClass
   */
  public function getAuctionParentNode($auction) {
    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
            ->fieldCondition('field_auction', 'target_id', $auction->auction_id, '=')
            ->entityOrderBy('entity_id', 'DESC')
            ->addMetaData('account', user_load($auction->uid));

    $result = $query->execute();

    if (isset($result['node']) && !empty($result['node'])) {
      $nids = array_keys($result['node']);
      $nid = array_shift($nids);
      return node_load($nid);
    }
  }

  /**
   * Check if auction should change it's status and do it if needed.
   *
   * @param stdClass $auction
   */
  public function changeStatusIfNeeded($auction) {
    static $changing = array();
    if (!in_array($auction->auction_id, $changing)) {
      $changing[] = $auction->auction_id;
      $wrapper = entity_metadata_wrapper('auction', $auction);

      if (time() >= $wrapper->field_auction_date->value->value() && $auction->status == AUCTION_STATUS_NOT_YET_STARTED) {
        return $this->activate($auction);
      }
      elseif (time() >= $wrapper->field_auction_date->value2->value() && $auction->status == AUCTION_STATUS_ACTIVE) {
        return $this->deactivate($auction);
      }
    }
    return $auction;
  }

  /**
   * Returns starting price of an auction.
   *
   * @param stdClass $auction
   * @return int
   */
  public function getStartingPrice($auction) {
    $wrapper = $this->getWrapper($auction);
    return $wrapper->field_auction_starting_price->value();
  }

  /**
   * Returns minimum price of an auction.
   *
   * @param stdClass $auction
   * @return int
   */
  public function getMinimumPrice($auction) {
    $wrapper = $this->getWrapper($auction);
    return $wrapper->field_auction_minimum_price->value();
  }

  /**
   * Returns current price of an auction.
   *
   * @param stdClass $auction
   * @return int
   */
  public function getCurrentPrice($auction) {
    return $auction->current_price / 100;
  }

  /**
   * Returns current price of an auction.
   *
   * @param stdClass $auction
   * @return int
   */
  public function updateCurrentPrice($auction) {
    // Ensure bids are loaded. Even the one added in the same request.
    $this->attachBids($auction);
    $this->save($auction);
  }

  /**
   * Returns bid step of an auction.
   *
   * @param stdClass $auction
   * @return float
   */
  public function getBidStep($auction) {
    $wrapper = $this->getWrapper($auction);
    return $wrapper->field_auction_bid_step->value();
  }

  /**
   * Returns lowest bid amount that can be accepted.
   *
   * @param stdClass $auction
   * @return int
   */
  public function getMinimumBidAmount($auction) {
    return $this->getCurrentPrice($auction) + $this->getBidStep($auction);
  }

  /**
   * Returns amount of highest bid placed in auction.
   *
   * @param stdClass $auction
   * @return stdClass
   */
  public function getHighestBid($auction) {
    if (!empty($auction->bids)) {
      return $auction->bids[0];
    }
  }

  /**
   * Returns amount of highest bid placed in auction.
   *
   * @param stdClass $auction
   * @return stdClass
   */
  public function getHighestBidAmount($auction) {
    if (!empty($auction->bids)) {
      return $auction->bids[0]->amount / 100;
    }
  }

  /**
   * Returns number of seconds left until the end of auction.
   *
   * @param stdClass $auction
   * @return int
   */
  public function getSecondsUntilEnd(&$auction) {
    $wrapper = $this->getWrapper($auction);
    return $wrapper->field_auction_date->value2->value() - time() - 1;
  }

  /**
   * Returns uid of the user currenly winning in auction.
   *
   * @param stdClass $auction
   * @return int
   */
  public function getWinningUserId(&$auction) {
    if (!empty($auction->bids)) {
      return $auction->bids[0]->uid;
    }
  }

  /**
   * Returns name of the user currenly winning in auction.
   *
   * @param stdClass $auction
   * @return string
   */
  public function getWinningUserName(&$auction) {
    return db_select('users', 'u')
            ->fields('u', array('name'))
            ->condition('uid', $this->getWinningUserId($auction))
            ->execute()
            ->fetchField();
  }

  /**
   * Returns true if user is winning in auction or false otherwise.
   *
   * @param stdClass $auction
   * @param int uid
   * @return boolean
   */
  public function userIsWinning(&$auction, $uid) {
    return $uid == $this->getWinningUserId($auction);
  }

  /**
   * Chcecks wheather this auction can be instant bought.
   *
   * @param stdClass $auction
   * @return boolean
   */
  public function isInstantBuyActive(&$auction) {
    // Instant buy is only available in auctions with price set.
    $instantBuyPrice = $this->getInstantBuyPrice($auction);
    if (!$instantBuyPrice) {
      return FALSE;
    }

    $settings = auction_get_settings();
    // Disable buy now if first bid was placed.
    if ($settings['buy_now_mode'] == 'first bid') {
      $this->attachBids($auction);

      if (empty($auction->bids)) {
        return TRUE;
      }
      else {
        return FALSE;
      }
    }
    // Disable buy now when price reaches limit.
    if ($settings['buy_now_mode'] == 'percentage') {
      $currentPrice = $this->getHighestBidAmount($auction);
      $threshold = $instantBuyPrice / 100 * $settings['buy_now_threshold'] / 100;

      if ($currentPrice < $threshold) {
        return TRUE;
      }
      else {
        return FALSE;
      }
    }
  }

  /**
   * Chcecks wheather this auction is in bid mode.
   *
   * @param stdClass $auction
   * @return boolean
   */
  public function isBiddingActive(&$auction) {
    $startingPrice = $this->getStartingPrice($auction);
    return !empty($startingPrice);
  }

  /**
   * Chcecks wheather minimum price has been reached.
   *
   * @param stdClass $auction
   * @return boolean
   */
  public function minimumPriceReached(&$auction) {
    return $auction->current_price >= $this->getMinimumPrice($auction) * 100;
  }

  /**
   * Returns wrapper for given auction.
   *
   * @param stdClass $auction
   * @return EntityMetadataWrapper
   */
  public function getWrapper(&$auction) {
    return entity_metadata_wrapper('auction', $auction);
  }

  /**
   * Returns price for which auction can be instant bought.
   *
   * @param stdClass $auction
   * @return float
   */
  public function getInstantBuyPrice(&$auction) {
    $wrapper = $this->getWrapper($auction);
    return $wrapper->field_auction_buy_now_price->value() * 100;
  }

  /**
   * Returns parent entity wrapper.
   *
   * @param stdClass $auction
   * @return EntityMetadataWrapper
   */
  public function getParentEntityWrapper($auction_id) {
    $data = db_select('field_data_field_auction', 'fd')
            ->fields('fd', array('entity_type', 'entity_id'))
            ->condition('field_auction_target_id', $auction_id)
            ->execute()
            ->fetchAssoc();

    if ($data) {
      return entity_metadata_wrapper($data['entity_type'],
            entity_load_single($data['entity_type'], $data['entity_id']));
    }
  }

  /**
   * Calculates finished auction's price for billing purposes.
   *
   * @param stdClass $auction
   * @return int
   */
  public function determineFinishedAuctionPrice($auction) {
    $result = 0;
    if (!empty($auction->bids)) {
      $result = $this->determineCurrentPrice($auction->bids, $this->getStartingPrice($auction));
      $minimumPrice = $this->getMinimumPrice($auction);
      if ($result <= $minimumPrice) {
        $result = 0;
      }
    }
    return $result;
  }

  /**
   * Calculates current auction price.
   *
   * @param array $lastBids
   * @param int $startingPrice
   * @return int
   */
  public function determineCurrentPrice($lastBids, $startingPrice) {
    $result = $startingPrice;
    if (count($lastBids) > 0) {
      if (isset($lastBids[0]->auction_id)) {
        $auction = $this->load(array($lastBids[0]->auction_id));
      }
      elseif (isset($lastBids[0]->auction_auction_bids_auction_id)) {
        $auction = $this->load(array($lastBids[0]->auction_auction_bids_auction_id));
      }
      if (is_array($auction)) {
        $auction = reset($auction);
      }
      if (isset($lastBids[0]->type) && $lastBids[0]->type == AUCTION_BID_TYPE_INSTANT_BUY) {
        // Auction has been instant bought.
        $result = $lastBids[0]->amount / 100;
      }
      elseif (count($lastBids) == 1) {
        // Auction has only one bid.
        $result = $startingPrice + $this->getBidStep($auction);
      }
      elseif ($lastBids[1]->amount != $lastBids[0]->amount) {
        // Auction has more than one bid and 2 first bids aren't the same.
        $result = $lastBids[1]->amount / 100 + $this->getBidStep($auction);
      }
      else {
        // Both first bids have the same value.
        $result = $lastBids[0]->amount / 100;
      }
    }
    return $result;
  }

}
