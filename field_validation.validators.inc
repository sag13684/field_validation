<?php

/**
 * @file
 * Provides validation functionality and hooks
 */

/**
 * Implements hook_field_validation_validators().
 *
 * This function returns an array of validators, in the validator key => options array form.
 * Possible options:
 * - name (required): name of the validator
 * - component types (required): defines which component types can be validated by this validator. Specify 'all' to allow all types
 * - custom_error (optional): define whether a user can specify a custom error message upon creating the validation rule.
 * - custom_data (optional): define whether custom data can be added to the validation rule
 * - min_components (optional): define the minimum number of components to be selected for creating a validation rule
 * - max_components (optional): define the maximum number of components to be selected for creating a validation rule
 * - description (optional): provide a descriptive explanation about the validator
 */
function field_validation_field_validation_validators() {
  return array(
    'regex' => array(
      'name' => "Regular expression",
      'component_types' => array(
        'textfield',
        'textarea',
        'email',
        'hidden',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Regex code'),
        'description' => t('Specify regex code to validate the user input against.'),
      ),
      'description' => t("Validates user-entered text against a specified regular expression. Note: don't include delimiters such as /."),
    ),
    'numeric' => array(
      'name' => "Numeric values",
      'component_types' => array(
        'textfield',
      ),
      'custom_data' => array(
        'label' => t('Specify numeric validation range'),
        'description' => t('Optionally specify the minimum-maximum range to validate the user-entered numeric value against.') . ' ' . t('Usage') . ':'
        . theme('item_list', array('items' => array(t('empty: no value validation'), t('"100": greater than or equal to 100'), t('"|100": less than or equal to 100 (including negative numbers)'), t('"0|100": greater than or equal to 0 &amp; less than or equal to 100'), t('"10|100": greater than or equal to 10 &amp; less than or equal to 100'), t('"-100|-10": greater than or equal to -100 &amp; less than or equal to -10')))),
        'required' => FALSE,
      ),
      'description' => t('Verifies that user-entered values are numeric, with the option to specify min and / or max values.'),
    ),		
		
  );
}

/**
 * Implements hook_field_validation_validate().
 */
function field_validation_field_validation_validate($validator_name, $rule, $langcode, $items, &$errors) {
  if (!empty($items)) {
    switch ($validator_name) {
     
      case "regex":
        mb_regex_encoding('UTF-8');
        $regex = $rule['data'];
				
        foreach ($items as $delta => $item) {
          if ($item['value'] != '' && (!mb_ereg("$regex", $item['value']))) {
				    $errors[$rule['field_name']][$langcode][$delta][] = array(
              'error' => 'regex_'.$rule['ruleid'], 
              'message' => t($rule['error_message']),
            );
          }
        }

        break;
    }
  }
}

/**
 * Get a list of validator definitions
 */
function field_validation_get_validators() {
  $validators = module_invoke_all("field_validation_validators");
  // let modules use hook_field_validator_alter($validators) to change validator settings
  drupal_alter('field_validator', $validators);
  return $validators;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function field_validation_get_validators_selection() {
  $selection = array();
  $validators = field_validation_get_validators();
  if ($validators) {
    foreach ($validators as $validator_key => $validator_info) {
      $selection[$validator_key] = $validator_info['name'];
    }
  }
  return $selection;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function field_validation_get_validator_info($validator_key) {
  $validators = field_validation_get_validators();
  return $validators[$validator_key];
}
