<?php

/**
 * @file
 * Migration of test images from a source directory to Drupal's files directory.
 */
class CharDUGImagesStatic extends Migration {

  /**
   * Constructs a CharDUGImagesStatic instance.
   *
   * @param array $arguments
   */
  public function __construct($arguments) {

    parent::__construct($arguments);

    $this->description = t('Sample Images');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'filename' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Image filename',
        ),
      ),
      MigrateDestinationFile::getKeySchema()
    );

    $img_source_folder = DRUPAL_ROOT . '/' . drupal_get_path('module', 'chardug_migrate_images_static') . '/sample_images_source';
    $regex = '/(.*\.png)/i';

    $list_files = new MigrateListFiles(array($img_source_folder), $img_source_folder, $regex);
    $item_file = new MigrateItemFile($img_source_folder);

    // Source fields.
    $fields = array(
      'filename' => t('filename'),
    );
    $this->source = new MigrateSourceList($list_files, $item_file, $fields);
    $this->destination = new MigrateDestinationFile('file', 'MigrateFileUri');

    $this->addFieldMapping('uid')->defaultValue($GLOBALS['user']->uid);
    $this->addFieldMapping('source_dir')->defaultValue($img_source_folder);
    $this->addFieldMapping('destination_dir')->defaultValue('public://chardug/sample_images_destination');
    $this->addFieldMapping('value', 'filename');
    $this->addFieldMapping('file_replace')->defaultValue(MigrateFile::FILE_EXISTS_REUSE);
    $this->addFieldmapping('preserve_files')->defaultValue(FALSE);

    $this->addUnmigratedDestinations(array(
      'fid',
      'path',
      'timestamp',
      'destination_file',
      'urlencode',
    ));

  }

}
