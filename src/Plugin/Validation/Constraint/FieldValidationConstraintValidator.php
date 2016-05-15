<?php

/**
 * @file
 * Contains \Drupal\field_validation\Plugin\Validation\Constraint\FieldValidationConstraintValidator.
 */

namespace Drupal\field_validation\Plugin\Validation\Constraint;

use Drupal\Core\Entity\Entity;
use Drupal\Core\Url;
use Symfony\Component\Validator\Constraint;
use Symfony\Component\Validator\ConstraintValidator;

/**
 * Validates the FieldValidation constraint.
 */
class FieldValidationConstraintValidator extends ConstraintValidator {

  /**
   * {@inheritdoc}
   */
  public function validate($items, Constraint $constraint) {
    $ruleset_name = $constraint->ruleset_name;
	$rule_uuid = $constraint->rule_uuid;
	$ruleset = \Drupal::entityManager()->getStorage('field_validation_rule_set')->load($ruleset_name);
	if(empty($ruleset)){
	  return;
	}
	//$rule = $ruleset->getFieldValidationRule($rule_uuid);
	$rules = $ruleset->getFieldValidationRules();
	$rules_available = array();
	$field_name = $items->getFieldDefinition()->getName();
	drupal_set_message($field_name);
	foreach($rules as $rule){
	  if($rule->getFieldName() == $field_name){
	    $rules_available[] = $rule;
	  }
	
	}
	if(empty($rules_available)){
	  return;
	}	
	drupal_set_message($ruleset_name);
	drupal_set_message($rule_uuid);
	drupal_set_message('count:' . count($rules_available));
	$params = array();
	$params['items'] = $items;
	//$params['rule'] = $rule;
	$params['context'] = $this->context;
	$column = $rule->getColumn();
	foreach($items as $delta => $item){
	   $value = $item->{$column};
	   $params['value'] = $value;
	   $params['delta'] = $delta;
	   $validator_manager = \Drupal::service('plugin.manager.field_validation.field_validation_rule');
       // You can hard code configuration or you load from settings.
	   foreach($rules_available as $rule){
         $config = [];
		 $params['rule'] = $rule;
         $plugin_validator = $validator_manager->createInstance($rule->getPluginId(), $config);
         $plugin_validator->validate($params);
	   }
	   
	}
/*	
    $value = $items->first()->value;
	$length = strlen($value);
	if($length > 10){
	   $this->context->addViolation("长度不能超多是10");
	}
	*/
	
	/*
    $title = explode(' ', $value_title);
    $node = \Drupal::routeMatch()->getParameter('node');
    if (isset($node)) {
      $node_type = $node->getType();
    }
    else {
      $url = Url::fromRoute('<current>', $route_parameters = array(), $options = array());
      $node_url_array = explode("node/add/", $url->toString());
      $node_type = $node_url_array[1];
    }
    $node_title_validation_config = \Drupal::config('node_title_validation_config.node_title_validation_settings')
      ->get('node_title_validation_config');
    foreach ($node_title_validation_config as $config_key => $config_value) {
      if ($config_value && $config_key == 'comma-' . $node_type) {
        $include_comma[] = ',';
      }
      if ($config_key == 'exclude-' . $node_type) {
        if (!empty($config_value)) {
          $config_values = array_map('trim', explode(',', $config_value));
          $config_values = array_merge($config_values, $include_comma);
          $findings = array();
          foreach ($title as $key => $title_value) {
            if (in_array(trim($title_value), $config_values)) {
                $findings[] = $title_value;
            }
          }
          $config_values = $include_comma = [];
          if($findings){
            $this->context->addViolation("This characters/words are not allowed to enter in the title. - " . implode(', ', $findings));
          }
        }
      }
      if ($config_key == 'min-' . $node_type) {
        if (strlen($value_title) < $config_value) {
          $this->context->addViolation("Title should have minimum $config_value characters");
        }
      }
      if ($config_key == 'max-' . $node_type) {
        if (strlen($value_title) > $config_value) {
          $this->context->addViolation("Title should not exceed $config_value characters");
        }
      }
      if ($config_key == 'min-wc-' . $node_type) {
        if (str_word_count($value_title) < $config_value) {
          $this->context->addViolation("Title should have minimum word count of $config_value");
        }
      }
      if ($config_key == 'max-wc-' . $node_type) {
        if (str_word_count($value_title) > $config_value) {
          $this->context->addViolation("Title should not exceed word count of $config_value");
        }
      }
      if ($config_key == 'unique-' . $node_type || $config_key == 'unique') {
        if ($config_value == 1) {
          $nodes = \Drupal::entityTypeManager()
            ->getStorage('node')
            ->loadByProperties(array('title' => $value_title));
          if (!empty($nodes)) {
            $this->context->addViolation("There is already a node exist with title -  $value_title");
          }
        }
      }
    }
	*/
  }
}
