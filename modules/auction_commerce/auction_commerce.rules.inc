<?php

/**
 * Aug 30, 2012
 * @file auction.rules.inc
 * @author blazey http://drupal.org/user/353861
 */

/**
 * Implements hook_rules_event_info().
 */
function auction_commerce_rules_event_info() {
  $defaults = array(
    'group' => t('auction'),
    'module' => 'auction',
  );
  
  $events = array();
  $events['auction_bill_created'] = $defaults + array(
    'label' => t('Auction order has been created'),
    'variables' => array(
      'auction' => array(
        'type' => 'auction',
        'label' => t('Target auction'),
      ),
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('Created order'),
      ),
    ),
  );
  
  return $events;
}