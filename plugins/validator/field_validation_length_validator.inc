<?php
/**
 * @file
 * Field validation length validator.
 *
 */
$plugin = array(
  'label' => t('Length'),
  'description' => t('Verifies the length of user-entered values, with the option to specify minimum and maximum length.'),
  'handler' => array(
    'class' => 'field_validation_length_validator',
  ),
);

class field_validation_length_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $settings = $rule->settings;
    if ($this->value != '') {
      $flag = TRUE;

      if (isset($settings['min']) && $settings['min'] != '' && drupal_strlen($this->value) < $settings['min']) {
        $flag = FALSE;
      }
      if (isset($settings['max']) && $settings['max'] != '' && drupal_strlen($this->value) > $settings['max']) {
        $flag = FALSE;
      }       

      if (!$flag) {
        $token = array(
          '[min]' => isset($settings['min']) ? $settings['min'] : '',
          '[max]' => isset($settings['max']) ? $settings['max'] : '',
        );
        $this->set_error($token);
      }
    }
  }
  
  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['min'] = array(
      '#title' => t('Minimum length'),
      '#description' => t("Optionally specify the minimum length to validate the user-entered value against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['min']) ? $default_settings['min'] : '',
    );
    $form['settings']['max'] = array(
      '#title' => t('Maximum value'),
      '#description' => t("Optionally specify the maximum length to validate the user-entered value against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['max']) ? $default_settings['max'] : '',
    );
  }

}