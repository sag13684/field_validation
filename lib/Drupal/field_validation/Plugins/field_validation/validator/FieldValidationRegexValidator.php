<?php
namespace Drupal\field_validation\Plugins\field_validation\validator;

use Drupal\Component\Plugin\PluginAbstract;
use Drupal\Component\Plugin\Plugin;
use Drupal\field_validation\Plugins\field_validation\validator\FieldValidationValidator;

class FieldValidationRegexValidator extends FieldValidationValidator {

  /**
   * Validate field. 
   */
  public function validate() {
    mb_regex_encoding('UTF-8');
    $regex = $this->rule->settings['data'];
    if ($this->value != '' && (!mb_ereg("$regex", $this->value))) {
      $this->setError();
    }
  }
  
  /**
   * Provide settings option
   */
  function settingsForm(&$form, &$form_state) {
    $default_settings = $this->getDefaultSettings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['data'] = array(
      '#title' => t('Regex code'),
      '#description' => t("Specify regex code to validate the user input against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['data']) ? $default_settings['data'] : '',
    );
    parent::settingsForm($form, $form_state);
  }

}