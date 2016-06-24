<?php

/**
 * Jul 22, 2012
 * @file auction.relist.inc
 * @author blazey http://drupal.org/user/353861
 */

function auction_relist($auction) {
  if ($auction) {
    $controller = auction_get_controller();
    $parent = $controller->getParentEntityWrapper($auction->auction_id)->raw();

    if ($parent) {
      $auction->relisted = 1;
      auction_save($auction);

      $parent->status = 0;
      node_save($parent);

      $new_parent = $parent;
      unset($new_parent->nid);
      unset($new_parent->vid);
      $new_parent->is_new = TRUE;
      $new_parent->status = 1;
      node_save($new_parent);
      $new_parent_wrapper = entity_metadata_wrapper('node', $new_parent);

      $new_auction = auction_clone_auction($auction);
      try {
        $new_parent_wrapper->field_auction->set(array($new_auction->auction_id));
      }
      catch (EntityMetadataWrapperException $e) {
        $new_parent_wrapper->field_auction->set($new_auction->auction_id);
      }
      $new_parent_wrapper->save();

      drupal_goto('node/' . $new_parent_wrapper->nid->value() . '/edit');
    }
  }
  return MENU_ACCESS_DENIED;
}

function auction_clone_auction($auction) {
  unset($auction->auction_id);
  $auction->relisted = 0;
  $auction->status = AUCTION_STATUS_NOT_YET_STARTED;
  $auction->field_auction_date[LANGUAGE_NONE][0]['value'] = time() - 1;
  $auction->field_auction_date[LANGUAGE_NONE][0]['value2'] = time() + 3600 + 60 * 60 * 24 * 7;
  auction_save($auction);
  return $auction;
}
