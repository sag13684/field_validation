<?php

/**
 * @file
 * A Ctools Export UI plugin for Field Validation rules.
 */

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'field_validation_rule',
  'access' => 'administer site configuration',
  'menu' => array(
    'menu item' => 'field_validation',
    'menu prefix' => 'admin/structure',
    'menu title' => 'Field Validation',
    'menu description' => 'Administer Field Validation rules.',
  ),

  'title singular' => t('rule'),
  'title plural' => t('rules'),
  'title singular proper' => t('Field Validation rule'),
  'title plural proper' => t('Field Validation rules'),

  'form' => array(
    'settings' => 'field_validation_ui_ctools_export_ui_form',
    'submit' => 'field_validation_ui_ctools_export_ui_form_submit',
  ),
);

/**
 * Define the add/edit form of validation rule.
 */
function field_validation_ui_ctools_export_ui_form(&$form, &$form_state) {
  $rule = $form_state['item'];
  $form['rulename'] = array(
    '#type' => 'textfield',
    '#title' => t('Rule name'),
    '#default_value' => $rule->rulename,
    '#required' => TRUE,
    '#size' => 60,
    '#maxlength' => 255,
   // '#weight' => 1,
  );

  $form['entity_type'] = array(
    '#type' => 'textfield', 
    '#title' => t('Entity type'),
    '#default_value' => $rule->entity_type,
    '#required' => TRUE,
  );

  $form['bundle'] = array(
    '#type' => 'textfield',
    '#title' => t('Bundle name'),
    '#default_value' => $rule->bundle,
    '#required' => TRUE,
  );
 
  $form['field_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Field name'),
    '#default_value' => $rule->field_name,
    '#required' => TRUE,
  ); 
 
  $form['col'] = array(
    '#type' => 'textfield',
    '#title' => t('Column'),
    '#description' => t('A column defined in the hook_field_schema() of this field.'),
    '#default_value' => $rule->col,
    '#required' => TRUE,
    //'#weight' => 2,
  );

  $form['validator'] = array(
    '#type' => 'textfield',
    '#title' => t('Validator'),
    '#default_value' => $rule->validator,
    '#required' => TRUE,
    //'#weight' => 3,
  );
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );
  $form['settings']['data'] = array(
    '#type' => 'textfield',
    '#title' => t('Config Data'),
    '#required' => FALSE,
    '#size' => 60,
    '#maxlength' => 255,
    '#default_value' => isset($rule->settings['data']) ? $rule->settings['data'] : '',
    //'#weight' => 4,
  );
  
  $form['error_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom error message'),
    '#description' => t("Specify an error message that should be displayed when user input doesn't pass validation"),
    '#required' => TRUE,
    '#size' => 60,
    '#maxlength' => 255,
    '#default_value' => $rule->error_message,
    '#weight' => 5,
  );
}
function field_validation_ui_ctools_export_ui_form_submit(&$form, &$form_state) {
  //$form_state['item']->settings['data'] = $form_state['values']['data'];
  //$form_state['item']->settings = $form_state['values']['settings'];
}
