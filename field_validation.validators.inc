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
 * - field types (required): defines which field types can be validated by this validator. Specify 'all' to allow all types
 * - custom_error (optional): define whether a user can specify a custom error message upon creating the validation rule.
 * - custom_data (optional): define whether custom data can be added to the validation rule
 * - description (optional): provide a descriptive explanation about the validator
 */
function field_validation_field_validation_validators() {
  return array(
    'regex' => array(
      'name' => "Regular expression",
      'field_types' => array(
        'textfield',
        'textarea',
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
      'field_types' => array(
        'textfield',
      ),
			'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Specify numeric validation range'),
        'description' => t('Optionally specify the minimum-maximum range to validate the user-entered numeric value against.') . ' ' . t('Usage') . ':'
        . theme('item_list', array('items' => array(t('empty: no value validation'), t('"100": greater than or equal to 100'), t('"|100": less than or equal to 100 (including negative numbers)'), t('"0|100": greater than or equal to 0 &amp; less than or equal to 100'), t('"10|100": greater than or equal to 10 &amp; less than or equal to 100'), t('"-100|-10": greater than or equal to -100 &amp; less than or equal to -10')))),
        'required' => FALSE,
      ),
      'description' => t('Verifies that user-entered values are numeric, with the option to specify min and / or max values.'),
    ),
    'min_length' => array(
      'name' => "Minimum length",
      'field_types' => array(
        'textfield',
        'textarea',
      ),
			'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Minimum number of characters'),
        'description' => t('Specify the minimum number of characters that have to be entered to pass validation.'),
      ),
      'description' => t('Verifies that a user-entered value contains at least the specified number of characters'),
    ),
    'max_length' => array(
      'name' => "Maximum length",
      'field_types' => array(
        'textfield',
        'textarea',
      ),
			'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Maximum number of characters'),
        'description' => t('Specify the maximum number of characters that can be entered to pass validation.'),
      ),
      'description' => t('Verifies that a user-entered value contains at most the specified number of characters'),
    ),
    'min_words' => array(
      'name' => "Minimum number of words",
      'field_types' => array(
        'textfield',
        'textarea',
      ),
			'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Minimum number of words'),
        'description' => t('Specify the minimum number of words that have to be entered to pass validation. Words are defined as strings of letters separated by spaces.')
      ),
      'description' => t('Verifies that a user-entered value contains at least the specified number of words'),
    ),		
    'max_words' => array(
      'name' => "Maximum number of words",
      'field_types' => array(
        'textfield',
        'textarea',
      ),
			'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Maximum number of words'),
        'description' => t('Specify the maximum number of words that have to be entered to pass validation. Words are defined as strings of letters separated by spaces.')
      ),
      'description' => t('Verifies that a user-entered value contains at most the specified number of words'),
    ),
    'plain_text' => array(
      'name' => "Plain text (disallow tags)",
      'field_types' => array(
        'textfield',
        'textarea',
      ),
			'custom_error' => TRUE,
      'description' => t("Verifies that user-entered data doesn't contain HTML tags"),
    ),
    'must_be_empty' => array(
      'name' => "Must be empty",
      'field_types' => array(
        'textfield',
      ),
			'custom_error' => TRUE,
      'description' => t('Verifies that a specified textfield remains empty - Recommended use case: used as an anti-spam measure by hiding the element with CSS'),
    ),
    'blacklist' => array(
      'name' => "Words blacklist",
      'field_types' => array(
        'textfield',
        'textarea',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Blacklisted words'),
        'description' => t('Specify illegal words, seperated by commas. Make sure to escape reserved regex characters with an escape (\) character.'),
      ),
      'description' => t("Validates that user-entered data doesn't contain any of the specified illegal words"),
    ),
    'select_min' => array(
      'name' => "Minimum number of selections required",
      'field_types' => array(
        'list_integer',
				'list_float',
				'list_text',
      ),
			'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Minimum number of selections'),
        'description' => t('Specify the minimum number of options a user should select.'),
      ),
      'description' => t('Forces the user to select at least a defined number of options from the specified list field'),
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
				
			case "numeric":
			  $num_range = _field_validation_numeric_check_data($rule['data']);
				foreach ($items as $delta => $item) {
				  if ($item['value'] != ''){
					  $error_flag = FALSE;
						if(!is_numeric($item['value'])){
						  $error_flag = TRUE;
						}
						if(isset($num_range['min']) && $item['value'] < $num_range['min']){
						  $error_flag = TRUE;
						}
            if(isset($num_range['max']) && $item['value'] > $num_range['max']){
						  $error_flag = TRUE;
						}
						if($error_flag){
						  $errors[$rule['field_name']][$langcode][$delta][] = array(
							  'error' => 'numeric_'.$rule['ruleid'],
								'message' => t($rule['error_message']),
							);
						}
					}
				}
			  break;
      case "min_length":
			  $min_length = $rule['data'];
				foreach ($items as $delta => $item) {
				  if ($item['value'] != '' && (drupal_strlen($item['value']) < $min_length)) {
					  $errors[$rule['field_name']][$langcode][$delta][] = array(
						  'error' => 'min_length_'.$rule['ruleid'],
							'message' => t($rule['error_message']),
						);
					}
				}
				break;				
      case "max_length":
			  $max_length = $rule['data'];
				foreach ($items as $delta => $item) {
				  if ($item['value'] != '' && (drupal_strlen($item['value']) > $max_length)) {
					  $errors[$rule['field_name']][$langcode][$delta][] = array(
						  'error' => 'max_length_'.$rule['ruleid'],
							'message' => t($rule['error_message']),
						);
					}
				}
				break;
      case "min_words":
			  $min_words = $rule['data'];
				foreach ($items as $delta => $item) {
				  if ($item['value'] != '' && (count(preg_split("/[\s]+/", trim($item['value']))) < $min_words)) {
					  $errors[$rule['field_name']][$langcode][$delta][] = array(
						  'error' => 'min_words_'.$rule['ruleid'],
							'message' => t($rule['error_message']),
						);
					}
				}
				break;
			case "max_words":
			  $max_words = $rule['data'];
				foreach ($items as $delta => $item) {
				  if ($item['value'] != '' && (count(preg_split("/[\s]+/", trim($item['value']))) > $max_words)) {
					  $errors[$rule['field_name']][$langcode][$delta][] = array(
						  'error' => 'max_words_'.$rule['ruleid'],
							'message' => t($rule['error_message']),
						);
					}
				}
				break;
			case "plain_text":
				foreach ($items as $delta => $item) {
				  if ($item['value'] != '' && (strcmp($item['value'], strip_tags($item['value'])))) {
					  $errors[$rule['field_name']][$langcode][$delta][] = array(
						  'error' => 'plain_text_'.$rule['ruleid'],
							'message' => t($rule['error_message']),
						);
					}
				}
				break;
			case "must_be_empty":
				foreach ($items as $delta => $item) {
				  if ($item['value']) {
					  $errors[$rule['field_name']][$langcode][$delta][] = array(
						  'error' => 'must_be_empty_'.$rule['ruleid'],
							'message' => t($rule['error_message']),
						);
					}
				}
				break;
			case "blacklist":
			  $blacklist = explode(',', $rule['data']);
				$blacklist = array_map('trim', $blacklist);
				$blacklist_regex = implode('|', $blacklist);
				foreach ($items as $delta => $item) {
				  if ($item['value'] != '' && (preg_match("/$blacklist_regex/i", $item['value']))) {
					  $errors[$rule['field_name']][$langcode][$delta][] = array(
						  'error' => 'blacklist_'.$rule['ruleid'],
							'message' => t($rule['error_message']),
						);
					}
				}
				break;
			case "select_min":
			  $min_selections = $rule['data'];
				$selected = 0;
				$total_items = count($items);
				foreach ($items as $delta => $item) {
				  if ($item['value'] != '') {
					  $selected ++;							
					}
				}
				if($total_items >= $min_selections && $selected < $min_selections){
				  $errors[$rule['field_name']][$langcode][0][] = array(
					  'error' => 'select_min_'.$rule['ruleid'],
						'message' => t($rule['error_message']),
					);
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

/**
 * Process the numeric value validation range that was provided in the numeric validator options
 */
function _field_validation_numeric_check_data($data) {
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
