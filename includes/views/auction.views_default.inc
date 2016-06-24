<?php

/**
 * Jul 19, 2012
 * @file auction.views_default.inc
 * @author blazey http://drupal.org/user/353861
 */

function auction_views_default_views() {
  $views = array();

  // Auction bids view.
  $view = new view();
  $view->name = 'auction_bids';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'auction_bids';
  $view->human_name = 'Auction bids';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'created' => 'created',
    'name' => 'name',
    'amount' => 'amount',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'amount' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Auctions: Bidder */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'auction_bids';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Auctions: Auction */
  $handler->display->display_options['relationships']['auction_id']['id'] = 'auction_id';
  $handler->display->display_options['relationships']['auction_id']['table'] = 'auction_bids';
  $handler->display->display_options['relationships']['auction_id']['field'] = 'auction_id';
  /* Field: Auctions: Bid type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'auction_bids';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  /* Field: Auctions: Created  time */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'auction_bids';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: Auctions: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'auction_bids';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['element_label_colon'] = FALSE;
  /* Field: Auction: Starting price */
  $handler->display->display_options['fields']['field_auction_starting_price']['id'] = 'field_auction_starting_price';
  $handler->display->display_options['fields']['field_auction_starting_price']['table'] = 'field_data_field_auction_starting_price';
  $handler->display->display_options['fields']['field_auction_starting_price']['field'] = 'field_auction_starting_price';
  $handler->display->display_options['fields']['field_auction_starting_price']['relationship'] = 'auction_id';
  $handler->display->display_options['fields']['field_auction_starting_price']['label'] = '';
  $handler->display->display_options['fields']['field_auction_starting_price']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_auction_starting_price']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_auction_starting_price']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Sort criterion: Auctions: Bid type */
  $handler->display->display_options['sorts']['type']['id'] = 'type';
  $handler->display->display_options['sorts']['type']['table'] = 'auction_bids';
  $handler->display->display_options['sorts']['type']['field'] = 'type';
  $handler->display->display_options['sorts']['type']['order'] = 'DESC';
  /* Sort criterion: Auctions: Amount */
  $handler->display->display_options['sorts']['amount']['id'] = 'amount';
  $handler->display->display_options['sorts']['amount']['table'] = 'auction_bids';
  $handler->display->display_options['sorts']['amount']['field'] = 'amount';
  $handler->display->display_options['sorts']['amount']['order'] = 'DESC';
  /* Sort criterion: Auctions: Created  time */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'auction_bids';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Contextual filter: Auctions: Auction */
  $handler->display->display_options['arguments']['auction_id']['id'] = 'auction_id';
  $handler->display->display_options['arguments']['auction_id']['table'] = 'auction_bids';
  $handler->display->display_options['arguments']['auction_id']['field'] = 'auction_id';
  $handler->display->display_options['arguments']['auction_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['auction_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['auction_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['auction_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['auction_id']['summary_options']['items_per_page'] = '25';

  $views[$view->name] = $view;

  //Auctions listings view with multiple displays.
  $view = new view;
  $view->name = 'auctions_listings';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'auction';
  $view->human_name = 'Auctions listings';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Active auctions';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'bid in auctions';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'auction_id' => 'auction_id',
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'auction_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_auction_node']['id'] = 'reverse_field_auction_node';
  $handler->display->display_options['relationships']['reverse_field_auction_node']['table'] = 'auction';
  $handler->display->display_options['relationships']['reverse_field_auction_node']['field'] = 'reverse_field_auction_node';
  $handler->display->display_options['relationships']['reverse_field_auction_node']['required'] = 1;
  /* Relationship: Auction: Creator */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'auction';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'reverse_field_auction_node';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Auction: Auction ID */
  $handler->display->display_options['fields']['auction_id']['id'] = 'auction_id';
  $handler->display->display_options['fields']['auction_id']['table'] = 'auction';
  $handler->display->display_options['fields']['auction_id']['field'] = 'auction_id';
  $handler->display->display_options['fields']['auction_id']['label'] = '';
  $handler->display->display_options['fields']['auction_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['auction_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['auction_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['auction_id']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['auction_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['auction_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['auction_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['auction_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['auction_id']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['auction_id']['format_plural'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'reverse_field_auction_node';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Auction: Price */
  $handler->display->display_options['fields']['current_price']['id'] = 'current_price';
  $handler->display->display_options['fields']['current_price']['table'] = 'auction';
  $handler->display->display_options['fields']['current_price']['field'] = 'current_price';
  $handler->display->display_options['fields']['current_price']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['external'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['current_price']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['current_price']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['html'] = 0;
  $handler->display->display_options['fields']['current_price']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['current_price']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['current_price']['hide_empty'] = 0;
  $handler->display->display_options['fields']['current_price']['empty_zero'] = 0;
  $handler->display->display_options['fields']['current_price']['hide_alter_empty'] = 1;
  /* Field: Auction: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'auction';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = '';
  $handler->display->display_options['fields']['status']['exclude'] = TRUE;
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['status']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['status']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['status']['format_plural'] = 0;
  /* Field: Auction: Date */
  $handler->display->display_options['fields']['field_auction_date']['id'] = 'field_auction_date';
  $handler->display->display_options['fields']['field_auction_date']['table'] = 'field_data_field_auction_date';
  $handler->display->display_options['fields']['field_auction_date']['field'] = 'field_auction_date';
  $handler->display->display_options['fields']['field_auction_date']['label'] = 'Ends';
  $handler->display->display_options['fields']['field_auction_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_auction_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_auction_date']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_auction_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_auction_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_auction_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'value2',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_auction_date']['field_api_classes'] = 0;
  /* Sort criterion: Auction: Created time */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'auction';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Auction: User placed bid in auction */
  $handler->display->display_options['filters']['user_placed_bid']['id'] = 'user_placed_bid';
  $handler->display->display_options['filters']['user_placed_bid']['table'] = 'auction';
  $handler->display->display_options['filters']['user_placed_bid']['field'] = 'user_placed_bid';
  $handler->display->display_options['filters']['user_placed_bid']['value'] = '1';
  /* Filter criterion: Auction: User is winning auction */
  $handler->display->display_options['filters']['user_is_winning']['id'] = 'user_is_winning';
  $handler->display->display_options['filters']['user_is_winning']['table'] = 'auction';
  $handler->display->display_options['filters']['user_is_winning']['field'] = 'user_is_winning';
  $handler->display->display_options['filters']['user_is_winning']['value'] = '0';

  /* Display: Active */
  $handler = $view->new_display('page', 'Active', 'page_1');
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Auction: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'auction';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value']['value'] = '2';
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['expose']['use_operator'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['multiple'] = FALSE;
  $handler->display->display_options['path'] = 'auctions/active';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Active';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Auctions';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: I've bid */
  $handler = $view->new_display('page', 'I\'ve bid', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Auctions I\'ve bid';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'bid in auctions';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Auction: User placed bid in auction */
  $handler->display->display_options['filters']['user_placed_bid']['id'] = 'user_placed_bid';
  $handler->display->display_options['filters']['user_placed_bid']['table'] = 'auction';
  $handler->display->display_options['filters']['user_placed_bid']['field'] = 'user_placed_bid';
  $handler->display->display_options['filters']['user_placed_bid']['value'] = '1';
  $handler->display->display_options['path'] = 'auctions/mybids';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'I\'ve bid';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: My auctions */
  $handler = $view->new_display('page', 'My auctions', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My auctions';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create auctions';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';
  $handler->display->display_options['path'] = 'auctions/my';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'My auctions';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: My inactive auctions */
  $handler = $view->new_display('page', 'My inactive auctions', 'page_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My inactive auctions';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';
  /* Filter criterion: Auction: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'auction';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value']['value'] = '1';
  $handler->display->display_options['path'] = 'auctions/inactive';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'My inactive auctions';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Auctions where I'm outbid */
  $handler = $view->new_display('page', 'Auctions where I\'m outbid', 'page_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Active I\'m outbid';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'bid in auctions';
  $handler->display->display_options['path'] = 'auctions/outbid';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Auctions where I\'m outbid';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Winning */
  $handler = $view->new_display('page', 'Winning', 'page_6');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Winning';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Auction: User is winning auction */
  $handler->display->display_options['filters']['user_is_winning']['id'] = 'user_is_winning';
  $handler->display->display_options['filters']['user_is_winning']['table'] = 'auction';
  $handler->display->display_options['filters']['user_is_winning']['field'] = 'user_is_winning';
  $handler->display->display_options['filters']['user_is_winning']['value'] = '1';
  /* Filter criterion: Auction: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'auction';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value']['value'] = '2';
  $handler->display->display_options['path'] = 'auctions/winning';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Winning';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Won */
  $handler = $view->new_display('page', 'Won', 'page_7');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Won auctions';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Auction: User is winning auction */
  $handler->display->display_options['filters']['user_is_winning']['id'] = 'user_is_winning';
  $handler->display->display_options['filters']['user_is_winning']['table'] = 'auction';
  $handler->display->display_options['filters']['user_is_winning']['field'] = 'user_is_winning';
  $handler->display->display_options['filters']['user_is_winning']['value'] = '1';
  /* Filter criterion: Auction: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'auction';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value']['value'] = '3';
  $handler->display->display_options['path'] = 'auctions/won';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Won';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Relist finished auctions */
  $handler = $view->new_display('page', 'Relist finished auctions', 'page_8');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Relist finished auctions';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'reverse_field_auction_node';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Auction: Auction ID */
  $handler->display->display_options['fields']['auction_id']['id'] = 'auction_id';
  $handler->display->display_options['fields']['auction_id']['table'] = 'auction';
  $handler->display->display_options['fields']['auction_id']['field'] = 'auction_id';
  $handler->display->display_options['fields']['auction_id']['label'] = '';
  $handler->display->display_options['fields']['auction_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['auction_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['auction_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['auction_id']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['auction_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['auction_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['auction_id']['separator'] = '';
  $handler->display->display_options['fields']['auction_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['auction_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['auction_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['auction_id']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['auction_id']['format_plural'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'reverse_field_auction_node';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Auction: Price */
  $handler->display->display_options['fields']['current_price']['id'] = 'current_price';
  $handler->display->display_options['fields']['current_price']['table'] = 'auction';
  $handler->display->display_options['fields']['current_price']['field'] = 'current_price';
  $handler->display->display_options['fields']['current_price']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['external'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['current_price']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['current_price']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['current_price']['alter']['html'] = 0;
  $handler->display->display_options['fields']['current_price']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['current_price']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['current_price']['hide_empty'] = 0;
  $handler->display->display_options['fields']['current_price']['empty_zero'] = 0;
  $handler->display->display_options['fields']['current_price']['hide_alter_empty'] = 1;
  /* Field: Auction: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'auction';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = '';
  $handler->display->display_options['fields']['status']['exclude'] = TRUE;
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['status']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['status']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['status']['format_plural'] = 0;
  /* Field: Auction: Date */
  $handler->display->display_options['fields']['field_auction_date']['id'] = 'field_auction_date';
  $handler->display->display_options['fields']['field_auction_date']['table'] = 'field_data_field_auction_date';
  $handler->display->display_options['fields']['field_auction_date']['field'] = 'field_auction_date';
  $handler->display->display_options['fields']['field_auction_date']['label'] = 'Ends';
  $handler->display->display_options['fields']['field_auction_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_auction_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_auction_date']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_auction_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_auction_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_auction_date']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_auction_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'value2',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_auction_date']['field_api_classes'] = 0;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'relist';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'auctions/relist/[auction_id]';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';
  /* Filter criterion: Auction: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'auction';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value']['value'] = '3';
  /* Filter criterion: Auction: Relisted */
  $handler->display->display_options['filters']['relisted']['id'] = 'relisted';
  $handler->display->display_options['filters']['relisted']['table'] = 'auction';
  $handler->display->display_options['filters']['relisted']['field'] = 'relisted';
  $handler->display->display_options['filters']['relisted']['value'] = '0';
  $handler->display->display_options['path'] = 'auctions/finished';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Relist finished auctions';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['auctions_listings'] = array(
    t('Master'),
    t('Active auctions'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Content referencing Auction from field_auction'),
    t('Auction owner'),
    t('.'),
    t(','),
    t('Title'),
    t('Price'),
    t('Ends'),
    t('Active'),
    t('Status'),
    t('I\'ve bid'),
    t('Auctions I\'ve bid'),
    t('My auctions'),
    t('My inactive auctions'),
    t('Auctions where I\'m outbid'),
    t('Active I\'m outbid'),
    t('Winning'),
    t('Won'),
    t('Won auctions'),
    t('Relist finished auctions'),
    t('relist'),
  );

  $views[$view->name] = $view;

  return $views;
}
