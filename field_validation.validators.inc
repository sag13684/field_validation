<?php

/**
 * @file
 * Provides validation functionality and hooks
 */

/**
 * Implements hook_webform_validation_validators().
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
  );
}

/**
 * Implements hook_webform_validation_validate().
 */
function field_validation_field_validation_validate($validator_name, $items, $rule) {
  if ($items) {
    $error = array();
    switch ($validator_name) {
     
      case "regex":
        mb_regex_encoding('UTF-8');
        $regex = $rule['data'];
				//debug($items);
				//debug($regex);
        foreach ($items as $delta => $item) {
          if ($item['value'] != '' && (!mb_ereg("$regex", $item['value']))) {
				    $error[$delta][] = array(
              'error' => 'regex', 
              'message' =>$rule['error_message'],
            );
						//debug($errors);
          }
        }
        return $error;
        break;

    }
  }
}

/**
 * Helper function to deal with submitted values that are arrays (e.g. multiple select component)
 * We flatten the array as a comma-separated list to do the comparison.
 */
function _field_validation_flatten_array($val) {
  if (is_array($val)) {
    $arr = array_filter($val, '_field_validation_check_false');
    return implode(',', $arr);
  }
  return $val;
}

/**
 * Get a list of validator definitions
 */
function field_validation_get_validators() {
  $validators = module_invoke_all("field_validation_validators");
  // let modules use hook_webform_validator_alter($validators) to change validator settings
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
 * Get a list of valid component types per validator, as defined via hook_webform_validation_validators().
 * If 'all' is specified, all available component types will be returned.
 */
function field_validation_valid_component_types($validator) {
  $validators = field_validation_get_validators();
  if ($info = $validators[$validator]) {
    $allowed_types = $info['component_types'];
    if (_field_validation_all_allowed($allowed_types)) {
      return array_keys(field_components());
    }
    return $info['component_types'];
  }
}

/**
 * Helper function to check whether all components are allowed to be used for a certain validator
 */
function _field_validation_all_allowed($allowed) {
  if ($allowed) {
    foreach ($allowed as $type) {
      if ($type == "all") {
        return TRUE;
      }
    }
  }
  return FALSE;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function field_validation_get_validator_info($validator_key) {
  $validators = field_validation_get_validators();
  return $validators[$validator_key];
}

/**
 * Handle translatable error messages, if available
 */
function _field_validation_i18n_error_message($rule) {
  if (module_exists('i18nstrings')) {
    return i18nstrings('field_validation:error_message:' . $rule['ruleid'] . ':message', $rule['error_message']);
  }
  return $rule['error_message'];
}

/**
 * Helper function used by array_filter to determine if a value was selected or not
 */
function _field_validation_check_false($var) {
  return $var !== FALSE && $var !== 0;
}

/**
 * Process the numeric value validation range that was provided in the numeric validator options
 */
function _field_numeric_check_data($data) {
  $range = array('min' => NULL, 'max' => NULL);
  // if no value was specified, don't validate
  if ($data == '') {
    return $range;
  }

  // If only one numeric value was specified, this is the min value
  if (is_numeric($data)) {
    $range['min'] = (int) $data;
  }

  if (strpos($data, '|') !== FALSE) {
    list($min, $max) = explode('|', $data);
    if ($min != '' && is_numeric($min)) {
      $range['min'] = (int) $min;
    }
    if ($max != '' && is_numeric($max)) {
      $range['max'] = (int) $max;
    }
  }
  return $range;
}
