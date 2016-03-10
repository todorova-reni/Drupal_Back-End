<?php
/**
  * @file
 * Administration functions and forms for the Latest content modyle
 */

/*
 * Form constructor for the latest_content settings form.
 * 
 * @ingroup forms
 * @see system_settings_form()
 */
function latest_content_admin_settings($form, &$form_state){
  $form['latest_content_default_count'] = array(
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#title' => t('How many latest content to show by default'),
    '#default_value' => variable_get('latest_content_default_count',10),
    '#size' => 5,
    '#maxlength' => 5,
  );
  return system_settings_form($form);
}
