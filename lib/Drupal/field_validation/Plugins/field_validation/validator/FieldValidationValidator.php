<?php
namespace Drupal\field_validation\Plugins\field_validation\validator;

use Drupal\Component\Plugin\PluginAbstract;
use Drupal\Component\Plugin\Plugin;

abstract class FieldValidationValidator extends PluginAbstract {
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
  function __construct($entity_type = 'node', $entity = NULL, $field = '', $instance = NULL, $langcode = 'und', $items = array(), $delta = 0, $item = array(), $value = '', $rule = NULL, &$errors = array()) {
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
    $this->errors = &$errors;
  }

  /**
   * Validate field. 
   */
  public function validate() {}

  /**
   * Provide settings option
   */
  function settingsForm(&$form, &$form_state) {
    $default_settings = $this->getDefaultSettings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['errors'] = array(
      '#title' => t('Set errors using field API'),
      '#description' => t("There are two methods to set error: using form_set_error provided by form api, using errors provided by field api. form_set_error does not work correctly when a sub form embed into another form. errors does not work correctly when current field does not support hook_field_widget_error."),
      '#type' => 'checkbox',
      '#default_value' => isset($default_settings['errors']) ? $default_settings['errors'] : FALSE,
    );
  }
  /**
   * Return error message string for the validation rule.
   */
  public function getErrorMessage() {
    $error_message = $this->rule->error_message;
    return $error_message;
  }
  
  /**
   * Return error element for the validation rule.
   */
  public function getErrorElement() {
    $error_element = $this->rule->field_name . '][' . $this->langcode . '][' . $this->delta . '][' . $this->rule->col;
    return  $error_element;
  }
  
  /**
   * Return default settingsfor the validator.
   */
  public function getDefaultSettings(&$form, &$form_state) {
    $rule = isset($form_state['item']) ? $form_state['item'] : new stdClass();
    $default_settings = isset($rule->settings) ? $rule->settings : array();
    $default_settings = isset($form_state['values']['settings']) ? $form_state['values']['settings'] : $default_settings;
    return  $default_settings;
  }
  
  /**
   * Set error message.
   */
  public function setError() {
    $error_element = $this->getErrorElement();
    $error_message = t($this->getErrorMessage());
	//drupal_set_message('123ac:'.$error_element.':'.$error_message.':'.$this->rule->settings['errors']);
	//form_set_error($error_element,  check_plain($error_message));
    //We support two methods to set error: using form_set_error provided by form api, using errors provided by field api.
    //form_set_error does not work correctly when a sub form embed into another form; 
    //errors does not work correctly when current field does not support hook_field_widget_error.
    if (empty($this->rule->settings['errors'])) {
      form_set_error($error_element,  check_plain($error_message));
	 // drupal_set_message('123ac:123');
    }
    else{
	  drupal_set_message('123ac:123456');
      $this->errors[$this->rule->field_name][$this->langcode][$this->delta][] = array(
        'error' => $this->rule->col,
        'message' => $error_message,
      );
    }
  }

}