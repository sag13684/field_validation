<?php
namespace Drupal\field_validation\Plugins\field_validation\validator;

use Drupal\Component\Plugin\PluginAbstract;
use Drupal\Component\Plugin\Plugin;
use Drupal\field_validation\Plugins\field_validation\validator\FieldValidationValidator;

class FieldValidationEmailValidator extends FieldValidationValidator {

  /**
   * Validate field. 
   */
  public function validate() {
    //drupal_set_message('abcdefg');
    if ($this->value != '' && (!valid_email_address($this->value))) {
	//drupal_set_message('abcdefg123');
      $this->setError();
    }
  }

}