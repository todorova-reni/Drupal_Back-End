<?php

/**
 * @file
 * Administration functions and forms for the Current Date module.
 */

/**
 * Form constructor for the current_date_form.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function current_date_from($form, &$form_state){
  $form['enable_current_date'] = array(
      '#type' => 'checkbox', 
      '#title' => t('Enable current date message'),
      '#default_value' => variable_get('enable_current_date', false),
  );
  
  $type = array(
      0 => t('Status'),
      1 => t('Warning'), 
      2 => t('Error'),
  );
   $form['message_type'] = array(
      '#type' => 'radios',
      '#title' => t('Message Type'),
      '#options' => $type,      
      '#default_value' => variable_get('message_type', false),      
  );
   
  return system_settings_form($form);
}
/**
 * Form constructor for the current_date_advanced_form.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function current_date_advanced_form($form, &$form_state){
    $form['show_for_anonymous'] = array(
      '#type' => 'checkbox', 
      '#title' => t('Show for anonymous users.'),
      '#default_value' => variable_get('show_for_anonymous', false),
  );
    return system_settings_form($form);
}

/*
 * Function that check if user is logged in or not
 */
function user_is_logged_in() {
  return (bool) $GLOBALS['user']->uid;
}