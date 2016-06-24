<?php

/**
 * Jun 18, 2012
 * @file auction.bids.tpl.php
 * @author blazey http://drupal.org/user/353861
 */

?>

<div class="auction-bids">
  <?php if (!empty($form)) : ?>
    <?php print $form ?>
  <?php endif; ?>

  <?php if (!empty($instant_buy)) : ?>
    <?php print $instant_buy ?>
  <?php endif; ?>

  <?php if (!empty($history)) : ?>
    <?php print $history ?>
  <?php endif; ?>
</div>