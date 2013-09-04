<?php

/**
 * @file
 * Because the name of this file is the module name plus '.migrate.inc', when
 * hook_migrate_api is invoked by the Migrate module this file is automatically
 * loaded - thus, you don't need to implement your hook in the .module file.
 */

/**
 * Implements hook_migrate_api().
 */
function chardug_migrate_images_static_migrate_api() {
  $api = array(
    // Required - tells the Migrate module that you are implementing version 2
    // of the Migrate API.
    'api' => 2,
    // Migrations can be organized into groups. The key used here will be the
    // machine name of the group, which can be used in Drush:
    //  drush migrate-import --group=wine
    // The title is a required argument which is displayed for the group in the
    // UI. You may also have additional arguments for any other data which is
    // common to all migrations in the group.
    'groups' => array(
      'chardug' => array(
        'title' => t('CharDUG Sample Migrations'),
      ),
    ),
    // Here we register the individual migrations. The keys (BeerTerm, BeerUser,
    // etc.) are the machine names of the migrations, and the class_name
    // argument is required. The group_name is optional (defaulting to 'default')
    // but specifying it is a best practice.
    'migrations' => array(
      'CharDUGImages' => array(
        'class_name' => 'CharDUGImagesStatic',
        'group_name' => 'chardug',
      ),
    ),
  );
  return $api;
}
