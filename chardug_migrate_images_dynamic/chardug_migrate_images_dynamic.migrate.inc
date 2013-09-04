<?php

/**
 * @file
 * Migration api hooks.
 */

/**
 * Implements chardug_migrate_images_dynamic_migrate_api().
 */
function chardug_migrate_images_dynamic_api() {
  $api = array(
    'api' => 2,
  );
  return $api;
}
