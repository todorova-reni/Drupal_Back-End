<?php
/**
 * @file
 * Administration functions and forms for the Modulea module.
 */

/**
 * Form constructor for the modulea settings form.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function modulea_admin_settings($form, &$form_state){
  $text = '<table  style="width:40%; padding:10px; margin-top:20px;">'
      . '<tr><th>Module Name</th><th>Value</th></tr>';
  
  foreach (module_implements('modulea_config') as $module) {
   $args = func_get_args();
   $name = $module.'_'.'modulea_config';
    $text .= "<tr><td>".$module." </td><td>"
        
    . call_user_func_array($name, $args). "</td></tr>"
    . module_invoke($module, 'modulea_config');
  }
  $text .= "</table>";
  
  $form['modulea_config_text'] = array(
    '#markup' => $text,
  );
  return system_settings_form($form);
}
/*
 * function modulea_admin_settings($form, &$form_state){
  
  $text = '<table  style="width:40%; padding:10px; margin-top:20px;">';
  
  foreach (module_implements('modulea_config') as $module) {
    $text .= "<tr><th>Module name: </th><td>"
    . $module . "</td></tr>"
    . module_invoke($module, 'modulea_config');
  }
  $text .= "</table>";
  
  $form['modulea_config_text'] = array(
    '#markup' => $text,
  );
  return system_settings_form($form);
}
 */