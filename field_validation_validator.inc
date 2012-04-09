<?php
/**
 * Basic class for field validation validator.
 *
 * All field validation validator classes should inherit this basic class.
 */

abstract class field_validation_validator {
  // Numbers we make calculations on.
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
  function __construct($entity_type, $entity, $field, $instance, $langcode, $items, $delta, $item, $rule, $errors) {
    $this->entity_type = $entity_type;
    $this->entity = $entity;
    $this->field = $field;
    $this->instance = $instance;
    $this->langcode = $langcode;
    $this->items = $items;
	$this->delta = $delta;
	$this->item = $item;
	$this->value = $item[$rule->col];
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
    $form['settings']['data'] = array(
      '#title' => t('Config data'),
      '#description' => t("Config data."),
      '#type' => 'textfield',
      //'#default_value' => $this->options['link_to_user'],
	  '#default_value' => '',
    );
  }
  /**
   * Return error message string for the validation rule.
   */
  public function error_message() {
    $error_message = $this->rule->error_message;
    return $error_message;
  }
  
  /**
   * Return error element for the validation rule.
   */
  public function error_element() {
    $error_element = $this->rule->field_name.']['.$this->langcode.']['.$this->delta.']['.$this->rule->col;
    return  $error_element;
  }
}