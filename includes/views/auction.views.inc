<?php

/**
 * Jun 22, 2012
 * @file auction.views.inc
 * @author blazey http://drupal.org/user/353861
 */

/**
 * Implements hook_views_data().
 */
function auction_views_data() {
  $data = array();

  $data['auction']['table']['group']  = t('Auction');

  $data['auction']['table']['base'] = array(
    'field' => 'auction_id',
    'title' => t('Auction'),
    'help' => t('Auction.'),
  );

  // Expose the auction ID.
  $data['auction']['auction_id'] = array(
    'title' => t('Auction ID'),
    'help' => t('The unique internal identifier of the auction.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['auction']['type'] = array(
    'title' => t('Auction type'),
    'help' => t('Type of the auction.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the creator uid.
  $data['auction']['uid'] = array(
    'title' => t('Creator'),
    'help' => t('Auction author.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('Auction owner'),
    ),
  );

  $data['auction']['relisted'] = array(
    'title' => t('Relisted'),
    'help' => t('Auction relisted.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['auction']['current_price'] = array(
    'title' => t('Price'),
    'help' => t('Current price.'),
    'field' => array(
      'handler' => 'views_handler_field_auction_amount',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['auction']['status'] = array(
    'title' => t('Status'),
    'help' => t('Auction state.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['auction']['user_placed_bid'] = array(
    'title' => t('User placed bid in auction'),
    'help' => t('True if current user placed bid in auction.'),
    'filter' => array(
      'handler' => 'views_handler_filter_auction_user_placed_a_bid',
    ),
  );

  $data['auction']['user_is_winning'] = array(
    'title' => t('User is winning auction'),
    'help' => t('Filters auctions that current user is or is not winning.'),
    'filter' => array(
      'handler' => 'views_handler_filter_auction_user_is_winning',
    ),
  );

  $data['auction']['created'] = array(
    'title' => t('Created time'),
    'help' => t('The date the auction was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['auction']['updated'] = array(
    'title' => t('Updated  time'),
    'help' => t('The date the auction was updated.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['auction_bids']['table']['group']  = t('Auctions');

  $data['auction_bids']['table']['base'] = array(
    'field' => 'bid_id',
    'title' => t('Bids'),
    'help' => t('Bids.'),
  );

  // Expose the auction ID.
  $data['auction_bids']['bid_id'] = array(
    'title' => t('Bid ID'),
    'help' => t('The unique internal identifier of the bid.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Expose the creator uid.
  $data['auction_bids']['uid'] = array(
    'title' => t('Bidder'),
    'help' => t('User that placed a bid.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('Bidder'),
    ),
  );

  $data['auction_bids']['auction_id'] = array(
    'title' => t('Auction'),
    'help' => t('Auction this bid was placed in.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'auction',
      'field' => 'auction_id',
      'label' => t('Auction this bid was placed in'),
    ),
  );

  $data['auction_bids']['type'] = array(
    'title' => t('Bid type'),
    'help' => t('Type of the bid.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['auction_bids']['amount'] = array(
    'title' => t('Amount'),
    'help' => t('Bid amount.'),
    'field' => array(
      'handler' => 'views_handler_field_auction_amount',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['auction_bids']['created'] = array(
    'title' => t('Created  time'),
    'help' => t('The date the auction was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_data_alter().
 *
 * @param array &$data
 */
function auction_views_data_alter(&$data) {
  $data['users']['auctions'] = array(
    'group' => t('Auction'),
    'title' => 'Auctions created by user',
    'help' => 'Auctions created by user',
    'relationship' => array(
      'base' => 'auction',
      'base field' => 'uid',
      'relationship field' => 'uid',
      'entity_type' => 'auction',
    )
  );

  $data['auction']['bids'] = array(
    'group' => t('Auction bids'),
    'title' => 'Bids from this auction',
    'help' => 'Bids from this auction',
    'relationship' => array(
      'base' => 'auction_bids',
      'base field' => 'auction_id',
      'relationship field' => 'auction_id',
      'entity_type' => 'auction',
    )
  );
}
