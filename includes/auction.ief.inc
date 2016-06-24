<?php

/**
 * Jun 6, 2012
 * @file auction.ief.inc
 * @author blazey http://drupal.org/user/353861
 */

class AuctionInlineEntityFormController extends EntityInlineEntityFormController {

  /**
   * Returns the entity form to be shown through the IEF widget.
   *
   * When adding data to $form_state it should be noted that there can be
   * several IEF widgets on one master form, each with several form rows,
   * leading to possible key collisions if the keys are not prefixed with
   * $entity_form['#parents'].
   *
   * @param $entity_form
   *   The entity form.
   * @param $form_state
   *   The form state of the parent form.
   */
  public function entityForm($entity_form, &$form_state) {
    $auction = &$entity_form['#entity'];

    if (auction_entity_access('edit', $auction)) {
      $language = LANGUAGE_NONE;
      field_attach_form('auction', $auction, $entity_form, $form_state, $language);

      $entity_form['status'] = array(
        '#type' => 'select',
        '#title' => t('Auction status'),
        '#options' => auction_statuses(),
        '#default_value' => $auction->status,
        '#access' => auction_entity_access('change status', $auction),
      );

    }
    else {
      $entity_form['message'] = array(
        '#markup' => t('Auction cannot be edited after it has started.'),
      );
    }

    return $entity_form;
  }

  /**
   * Validates the entity form.
   *
   * @param $entity_form
   *   The entity form.
   * @param $form_state
   *   The form state of the parent form.
   */
  public function entityFormValidate($entity_form, &$form_state) {
    $values = $form_state['values'];
    foreach ($entity_form['#parents'] as $parent) {
      $values = $values[$parent];
    }

    if (empty($values['field_auction_starting_price'][LANGUAGE_NONE][0]['value'])
      && empty($values['field_auction_buy_now_price'][LANGUAGE_NONE][0]['value'])) {
      form_error($entity_form['field_auction_starting_price'], t('Either starting price or buy now price has to be provided.'));
    }
  }

  /**
   * Returns an array of fields (which can be either Field API fields or
   * properties defined through hook_entity_property_info()) that should be
   * used to represent a selected entity.
   *
   * The IEF widget can have its own fields specified in the widget settings,
   * in which case the output of this function is ignored.
   *
   * @param $bundles
   *   An array of allowed $bundles for this widget.
   *
   * @return
   *   An array of field information, keyed by field name. Allowed keys:
   *   - type: 'field' or 'property',
   *   - label: Human readable name of the field, shown to the user.
   *   - weight: The position of the field relative to other fields.
   *   - visible: Whether the field should be displayed.
   *   Special keys for type 'field':
   *   - formatter: The formatter used to display the field, or "hidden".
   *   - settings: An array passed to the formatter. If empty, defaults are used.
   *   - delta: If provided, limits the field to just the specified delta.
   */
  public function defaultFields($bundles) {
    $fields = array();

    $fields['field_auction_starting_price'] = array(
      'type' => 'field',
      'label' => t('Starting price'),
      'formatter' => 'number_decimal',
      'settings' => array(),
      'delta' => 0,
      'visible' => TRUE,
      'weight' => -10,
    );
    $fields['field_auction_buy_now_price'] = array(
      'type' => 'field',
      'label' => t('Buy now price'),
      'formatter' => 'number_decimal',
      'settings' => array(),
      'delta' => 0,
      'visible' => TRUE,
      'weight' => -8,
    );
    $fields['field_auction_minimum_price'] = array(
      'type' => 'field',
      'label' => t('Minimum price'),
      'formatter' => 'number_decimal',
      'settings' => array(),
      'delta' => 0,
      'visible' => TRUE,
      'weight' => -6,
    );
    $fields['field_auction_bid_step'] = array(
      'type' => 'field',
      'label' => t('Bid step'),
      'formatter' => 'number_decimal',
      'settings' => array(),
      'delta' => 0,
      'visible' => TRUE,
      'weight' => -5,
    );
    $fields['field_auction_date'] = array(
      'type' => 'field',
      'label' => t('Date'),
      'formatter' => 'date_default',
      'settings' => array(
        'format_type' => 'short',
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_to' => '',
        'fromto' => 'both',
      ),
      'delta' => 0,
      'visible' => TRUE,
      'weight' => -4,
    );

    return $fields;
  }

}
