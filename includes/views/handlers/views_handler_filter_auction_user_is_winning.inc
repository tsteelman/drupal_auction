<?php

/**
 * Jul 18, 2012
 * @file views_handler_filter_auction_user_is_winning.inc
 * @author blazey http://drupal.org/user/353861
 */

class views_handler_filter_auction_user_is_winning extends views_handler_filter_boolean_operator {

  function query() {
    global $user;
    $this->ensure_my_table();

    if ($this->value) {
      $operator = '=';
    }
    else {
      $operator = '!=';
    }

    $this->query->add_where_expression($this->options['group'], "$user->uid $operator (SELECT uid FROM auction_bids WHERE auction_id = $this->table_alias.auction_id ORDER BY amount DESC LIMIT 0, 1)");
  }

}
