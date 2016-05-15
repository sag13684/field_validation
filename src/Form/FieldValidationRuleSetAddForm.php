<?php

/**
 * @file
 * Contains \Drupal\field_validation\Form\FieldValidationRuleSetAddForm.
 */

namespace Drupal\field_validation\Form;

use Drupal\Core\Form\FormStateInterface;

/**
 * Controller for FieldValidationRuleSet addition forms.
 */
class FieldValidationRuleSetAddForm extends FieldValidationRuleSetFormBase {

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    parent::submitForm($form, $form_state);
    drupal_set_message($this->t('Field validation rule set %name was created.', array('%name' => $this->entity->label())));
  }

  /**
   * {@inheritdoc}
   */
  public function actions(array $form, FormStateInterface $form_state) {
    $actions = parent::actions($form, $form_state);
    $actions['submit']['#value'] = $this->t('Create new field validation rule set');

    return $actions;
  }

}
