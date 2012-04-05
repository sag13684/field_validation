<?php

/**
 * @file
 * Provides default field validation rules
 */
 
/**
 * Implementation of hook_default_field_validation_rule().
 * 
 * Provide default validation rules.
 */
function field_validation_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass;
  $rule->api_version = 1;
  $rule->name = 'min_words_comment_for_comment_body';
  $rule->rulename = 'Min words for comment body';
  $rule->field_name = 'comment_body';
  $rule->col = 'value';
  $rule->entity_type = 'comment';
  $rule->bundle = 'comment_node_article';
  $rule->validator = 'min_words';
  $rule->data = '2';
  $rule->error_message = t('You should enter at least two words.');
  $rule->status = 1;
  $export['min-words-comment'] = $rule;
	
  return $export;
}
