<?php
/**
 * @file
 * Theme setting callbacks for the garland theme.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
function cinema_form_system_theme_settings_alter(&$form, &$form_state) {

  $form['cinema_width'] = array(
    '#type' => 'radios',
    '#title' => t('Content width'),
    '#options' => array(
      'fluid' => t('Fluid width'),
      'fixed' => t('Fixed width'),
      'small' => t('Small devices (768 px)'),
      'medium' => t('Medium devices (992 px)'),
      'large' => t('Large devices (1200 px)'),
    ),
    '#default_value' => theme_get_setting('cinema_width'),
    '#description' => t('Specify whether the content will wrap to a fixed width or will fluidly expand to the width of the browser window.'),
    // Place this above the color scheme options.
    '#weight' => -2,
  );
}
