<?php

/**
 * @file
 * Migration of test images from a source directory to Drupal's files directory.
 */
class CharDUGImagesDynamic extends Migration {

  /**
   * Constructs a CharDUGImagesDynamic instance.
   */
  public function __construct(array $arguments = array()) {

    $this->description = t('Sample images migration (dynamic).');

    parent::__construct($arguments);

    if (!isset($arguments['source_directory'])) {
      throw new Exception(t('Source directory is required.'));
    }

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

    $img_source_folder = $arguments['source_directory'];
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
    $this->addFieldMapping('destination_dir')->defaultValue('public://sampleimages');
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
