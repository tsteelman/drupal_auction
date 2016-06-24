<?php

/**
 * Aug 29, 2012
 * @file auction_commerce.rules_defaults.inc
 * @author blazey http://drupal.org/user/353861
 */

/**
 * Implements hook_default_rules_configuration().
 *
 * @return array 
 */
function auction_commerce_default_rules_configuration() {
  $configs = array();
  
  $rule = rules_reaction_rule();
  $rule->label = 'Notify auction creators about new monthly bill';
  $rule->active = TRUE;
  $rule->event('commerce_order_insert')
        ->condition('data_is', array(
          'data:select' => 'commerce_order:type',
          'value' => 'auction_monthly_bill',
        ))
       ->action('mail', array(
          'to' => 'commerce-order:owner:mail',
          'subject' => 'New monthly bill at [site:name].',
          'message' => 'Hi [commerce-order:owner:name],\r\n\r\nThere\u0027s a new monthly bill for you at [site:name]. Please check it out at [commerce-order:customer-url].',
          'from' => 'site:mail',
          'language' => '',
       ));
  
  $configs['rules_notify_auction_creators_about_new_monthly_bill'] = $rule;
  
  $rule = rules_reaction_rule();
  $rule->label = 'Notify sales that auction has ended';
  $rule->active = TRUE;
  $rule->event('auction_bill_created')
        ->condition('data_is', array(
          'data:select' => 'order:type',
          'value' => 'auction_bill',
        ))
       ->action('mail', array(
          'to' => 'pm@netzor.de',
          'subject' => 'Auction has ended.',
          'message' => "Auction [auction:link] has ended. Final price is [auction:current_price]. Bids placed in auction:[auction:bids_overview].",
          'from' => 'site:mail',
          'language' => '',
       ));
  
  $configs['rules_notify_sales_that_auction_has_ended'] = $rule;

  $rule = rules_reaction_rule();
  $rule->label = 'Redirect instant-buy users straight to checkout';
  $rule->active = TRUE;
  $rule->event('auction_bill_created')
        ->condition('data_is', array(
          'data:select' => 'order:type',
          'value' => 'auction_bill',
        ))
        ->condition('data_is', array(
          'data:select' => 'site:current-user:uid',
          'value:select' => 'order:uid',
        ))
        ->action('redirect', array(
          'url' => 'checkout/[order:order-id]',
        ));
  
  $configs['rules_redirect_instant_buy_users_straight_to_checkout'] = $rule;
  
  return $configs;
}