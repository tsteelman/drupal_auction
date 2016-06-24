<?php

/**
 * Jun 15, 2012
 * @file auction.api.php
 * @author blazey http://drupal.org/user/353861
 */

/**
 * Tell auction module about you fee ranges.
 *
 * @return array
 */
function hook_auction_fee_ranges() {
  return array(
    array(
      'from' => 0,
      'sell_price_fee' => 0.03,
      'single_auction_fee' => 15,
    ),
    array(
      'from' => 10000,
      'sell-price-fee' => 0.025,
      'single_auction_fee' => 50,
    ),
    array(
      'from' => 100000,
      'sell-price-fee' => 0.02,
      'single_auction_fee' => 100,
    ),
  );
}

/**
 * Alter existing fee ranges.
 *
 * @param array &$ranges
 */
function hook_auction_fee_ranges_alter(&$ranges) {
  $ranges[1]['from'] = 15000;
}