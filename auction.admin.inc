<?php

/**
 * May 27, 2012
 * @file auction.admin.inc
 * @author blazey http://drupal.org/user/353861
 */

/**
 * Module settings form.
 *
 * @return array
 */
function auction_settings_form() {
  $settings = auction_get_settings();

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );
  $form['general']['auction_currency'] = array(
    '#type' => 'textfield',
    '#title' => t('Currency code'),
    '#default_value' => $settings['currency'],
    '#required' => TRUE,
    '#maxlength' => 3,
    '#size' => 5,
  );
  $form['general']['auction_bid_step'] = array(
    '#type' => 'textfield',
    '#title' => t('Bid step'),
    '#default_value' => $settings['bid_step'],
    '#required' => TRUE,
    '#size' => 5,
  );

  $form['buy_now'] = array(
    '#type' => 'fieldset',
    '#title' => t('Buy now settings'),
  );
  $form['buy_now']['auction_buy_now_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Disable buy now when'),
    '#default_value' => $settings['buy_now_mode'],
    '#options' => array(
      'first bid' => t('first bid is placed.'),
      'percentage' => t('auction price reaches threshold.'),
    ),
  );
  $form['buy_now']['auction_buy_now_threshold'] = array(
    '#type' => 'textfield',
    '#title' => t('Threshold'),
    '#default_value' => $settings['buy_now_threshold'],
    '#required' => FALSE,
    '#size' => 5,
    '#field_suffix' => t('% of buy now price.'),
  );

  $form['fees'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fees'),
  );
  $form['fees']['auction_usage_fee'] = array(
    '#type' => 'textfield',
    '#title' => t('Usage fee'),
    '#default_value' => $settings['usage_fee'],
    '#required' => TRUE,
    '#size' => 5,
  );
  $form['fees']['auction_provision_fee'] = array(
    '#type' => 'textfield',
    '#title' => t('Provision fee'),
    '#default_value' => $settings['provision_fee'],
    '#required' => TRUE,
    '#size' => 5,
  );


  return system_settings_form($form);
}