<?php

/**
 * Jul 18, 2012
 * @file views_handler_filter_auction_user_placed_a_bid.inc
 * @author blazey http://drupal.org/user/353861
 */

class views_handler_filter_auction_user_placed_a_bid extends views_handler_filter_boolean_operator {

  function query() {
    global $user;
    $this->ensure_my_table();

    if ($this->value) {
      $keyword = 'EXISTS';
    }
    else {
      $keyword = 'NOT EXISTS';
    }

    $this->query->add_where_expression($this->options['group'], "$keyword (SELECT * FROM auction_bids WHERE auction_id = $this->table_alias.auction_id AND uid = $user->uid)");
  }

}
