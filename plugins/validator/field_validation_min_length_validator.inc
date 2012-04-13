<?php
/**
 * @file
 * Field validation min length validator.
 *
 */
$plugin = array(
  'label' => t('Min length'),
  'description' => t('Verifies that a user-entered value contains at least the specified number of characters.'),
  'handler' => array(
    'class' => 'field_validation_min_length_validator',
  ),
);

class field_validation_min_length_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $min_length = $this->rule->settings['data'];
    if ($this->value != '' && (drupal_strlen($this->value) < $min_length)) {
      $this->set_error();
    }
  }
  
  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['data'] = array(
      '#title' => t('Minimum number of characters'),
      '#description' => t("Specify the minimum number of characters that have to be entered to pass validation."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['data']) ? $default_settings['data'] : '',
    );
  }

}