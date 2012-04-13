<?php
/**
 * @file
 * Basic class for field validation validator.
 *
 * All field validation validator classes should inherit this basic class.
 */

abstract class field_validation_validator {
  // Variables associated with validation.
  protected $entity_type;
  protected $entity;
  protected $field;
  protected $instance;
  protected $langcode;
  protected $items;
  protected $delta;
  protected $item;
  protected $value;
  protected $rule;
  protected $errors;

  /**
   * Save arguments locally.
   */
  function __construct($entity_type = 'node', $entity = NULL, $field = '', $instance = NULL, $langcode = 'und', $items = array(), $delta = 0, $item = array(), $value = '', $rule = NULL, $errors = array()) {
    $this->entity_type = $entity_type;
    $this->entity = $entity;
    $this->field = $field;
    $this->instance = $instance;
    $this->langcode = $langcode;
    $this->items = $items;
    $this->delta = $delta;
    $this->item = $item;
    $this->value = $value;
    $this->rule = $rule;
    $this->errors = $errors;
  }

  /**
   * Validate field. 
   */
  public function validate() {}

  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['data'] = array(
      '#title' => t('Config data'),
      '#description' => t("Config data."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['data']) ? $default_settings['data'] : '',
    );
  }
  /**
   * Return error message string for the validation rule.
   */
  public function get_error_message() {
    $error_message = $this->rule->error_message;
    return $error_message;
  }
  
  /**
   * Return error element for the validation rule.
   */
  public function get_error_element() {
    $error_element = $this->rule->field_name . '][' . $this->langcode . '][' . $this->delta . '][' . $this->rule->col;
    return  $error_element;
  }
  
  /**
   * Return default settingsfor the validator.
   */
  public function get_default_settings(&$form, &$form_state) {
    $rule = $form_state['item'];
    $default_settings = isset($rule->settings) ? $rule->settings : array();
    $default_settings = isset($form_state['values']['settings']) ? $form_state['values']['settings'] : $default_settings;
    return  $default_settings;
  }
  
  /**
   * Set error message.
   */
  public function set_error($tokens = array()) {
    $error_element = $this->get_error_element();
    $error_message = $this->get_error_message();
    form_set_error($error_element,  check_plain($error_message));
  }
}