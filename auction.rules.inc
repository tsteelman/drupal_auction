<?php

/**
 * Jul 20, 2012
 * @file auction.rules.inc
 * @author blazey http://drupal.org/user/353861
 */

/**
 * Implements hook_rules_event_info().
 */
function auction_rules_event_info() {
  $defaults = array(
    'group' => t('auction'),
    'module' => 'auction',
  );

  $events = array();
  $events['auction_started'] = $defaults + array(
    'label' => t('Auction has started'),
    'variables' => array(
      'auction' => array(
        'type' => 'auction',
        'label' => t('Started auction'),
      ),
      'auction_node' => array(
        'type' => 'node',
        'label' => t('Auction node'),
      ),
    ),
  );
  $events['auction_finished'] = $defaults + array(
    'label' => t('Auction has finished'),
    'variables' => array(
      'auction' => array(
        'type' => 'auction',
        'label' => t('Finished auction'),
      ),
      'auction_node' => array(
        'type' => 'node',
        'label' => t('Auction node'),
      ),
    ),
  );
  $events['auction_bid_placed'] = $defaults + array(
    'label' => t('Bid has been placed'),
    'variables' => array(
      'auction' => array(
        'type' => 'auction',
        'label' => t('Finished auction'),
      ),
      'bidder' => array(
        'type' => 'user',
        'label' => t('User who placed a bid'),
      ),
      'outbid_user' => array(
        'type' => 'user',
        'label' => t('User that was outbid. Requires conditions (CAN BE EMPTY!).'),
      ),
      'auction_node' => array(
        'type' => 'node',
        'label' => t('Auction node'),
      ),
    ),
  );

  return $events;
}
