<?php

/**
 * Jun 25, 2012
 * @file views_handler_field_auction_bid_amount.inc
 * @author blazey http://drupal.org/user/353861
 */

class views_handler_field_auction_amount extends views_handler_field {

  function construct() {
    parent::construct();
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['show_currency'] = array('default' => FALSE, 'bool' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['show_currency'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show currency suffix'),
      '#default_value' => $this->options['show_currency'],
    );
    parent::options_form($form, $form_state);

  }

  function options_submit(&$form, &$form_state) {
    $this->options['show_currency'] = $form_state['values']['show_currency'];
  }

  function query() {
    $this->additional_fields[$this->field] = $this->field;
    $this->additional_fields['currency_code'] = 'currency_code';
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $currency_code = ($this->options['show_currency']) ? $values->{$this->aliases['currency_code']} : '';
    $result = auction_format_price($values->{$this->aliases[$this->field]}, $currency_code);
    return $result;
  }

}
