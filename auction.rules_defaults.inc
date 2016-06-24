<?php

/**
 * Jul 20, 2012
 * @file auction.rules_defaults.inc
 * @author blazey http://drupal.org/user/353861
 */

/**
 * Implements hook_default_rules_configuration().
 *
 * @return array
 */
function auction_default_rules_configuration() {
  $configs = array();

  $rule = rules_reaction_rule();
  $rule->label = 'Notify auction author that it has started';
  $rule->active = TRUE;
  $rule->event('auction_started')
       ->action('mail', array(
          'to' => '[auction:author:mail]',
          'subject' => 'You auction has been started.',
          'message' => 'Your auction has started. You can check it at [auction:url].',
          'language' => '',
       ));

  $configs['rules_notify_auction_author_that_it_has_started'] = $rule;

  $rule = rules_reaction_rule();
  $rule->label = 'Notify auction author that it has ended';
  $rule->active = TRUE;
  $rule->event('auction_finished')
       ->action('mail', array(
          'to' => '[auction:author:mail]',
          'subject' => 'Your auction has finished.',
          'message' => 'Your auction has just finished. You can check it at [auction:url].',
          'language' => '',
       ));

  $configs['rules_notify_auction_author_that_it_has_ended'] = $rule;

  $rule = rules_reaction_rule();
  $rule->label = 'Notify auction author that a bid was placed';
  $rule->active = TRUE;
  $rule->event('auction_bid_placed')
       ->action('mail', array(
          'to' => '[auction:author:mail]',
          'subject' => 'Bid placed in your auction.',
          'message' => 'Bid has been placed in your auction. You can check it at [auction:url].',
          'language' => '',
       ));

  $configs['rules_notify_auction_author_that_bid_was_placed'] = $rule;

  return $configs;
}
