<?php

/**
 * @file
 * Administration functions and forms for the Students module.
 */

/**
 * list_students
 */
function list_students() {
  $output = "";
  $output .= l('Add student', 'add-students');
  $items = array();
  $query = db_select('students', 'stdnts')
      ->fields('stdnts')
      ->execute();

  $header = array('Name', 'Gender', 'Faculty Number', 'Action');
  if ($query->rowCount() == 0) {
    drupal_set_message("No student data is added yet.");
  }
  else {    
    foreach ($query as $record) {
      $items[] = array(
        check_plain($record->name),
        check_plain($record->gender),
        check_plain($record->faculty_number),
        l(t('Edit'), 'edit/' . $record->sid) . '&nbsp;|&nbsp;' .
        l(t('Delete'), 'delete/' . $record->sid)
      );
    }
  }
  $output .=theme('table', array('header' => $header, 'rows' => $items));
  return $output;
}

/**
 * Form constructor for the student_add_form.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function student_add_form($form, &$form_state) {

  $select = db_select('students', 'stud')
      ->fields('stud')
      ->condition('sid', arg(1), '=');
  $result = $select->execute()->fetchAssoc();

  $gender = 0;
  if ($result['gender'] == 'Female') {
    $gender = 1;
  }

  $type = array(
    '0' => t('Male'),
    '1' => t('Female'),
  );

  $form['fieldset'] = array(
    '#title' => t('Add Student'),
    '#type' => 'fieldset',
  );

  $form['fieldset']['sid'] = array(
    '#type' => 'hidden',
  );

  $form['fieldset']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#size' => 30,
    '#required' => TRUE,
    '#default_value' => isset($result['sid']) ? $result['name'] : '',
    '#maxlength' => 255
  );

  $form['fieldset']['faculty_number'] = array(
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#title' => t('Faculty number'),
    '#size' => 30,
    '#required' => TRUE,
    '#default_value' => isset($result['sid']) ? $result['faculty_number'] : '',
    '#maxlength' => 8
  );

  $form['fieldset']['gender'] = array(
    '#type' => 'radios',
    '#title' => t('Gender'),
    '#options' => $type,
    '#required' => TRUE,
    '#default_value' => isset($result['sid']) ? $gender : ''
  );

  $form['fieldset']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit')
  );
    
  if (isset($result['sid'])) {
    $form['#submit'][] = 'studentUpdate_submit';
  }
  else {
     $form['#validate'][] = 'studentAdd_validate';
    $form['#submit'][] = 'studentAdd_submit';
  }

  return $form;
}

/*
 * validate student_add_form
 */
function studentAdd_validate($form, &$form_state) {
  $result = db_select('students', 'stud')
      ->fields('stud')
      ->execute();
  
  if (strlen(trim($form_state['values']['name'])) <= 2) {
    form_set_error('name', t('Your name should contain at least 3 characters.'));
  }
  if (strlen(trim($form_state['values']['faculty_number'])) != 8) {
    form_set_error('faculty_number', t('Your faculty number should be exact 8 digits.'));
  }  
  foreach($result as $row){
    if($row->faculty_number == $form_state['values']['faculty_number']){
      form_set_error('faculty_number', t('This faculty number already exist.'));
    }
  }
}

/*
 * validate student_add_form on UPDATE
 */
function studentUpdate_validate($form, &$form_state) {
  if (strlen(trim($form_state['values']['name'])) <= 2) {
    form_set_error('name', t('Your name should contain at least 3 characters.'));
  }
  if (strlen(trim($form_state['values']['faculty_number'])) != 8) {
    form_set_error('faculty_number', t('Your faculty number should be exact 8 digits.'));
  }   
}

/*
 * Insert on submit
 */
function studentAdd_submit($form, &$form_state) {
//  //watchdog('sleetmute', "NID  = " . $id);

  $student = new stdClass();
  $student->name = $form_state['input']['name'];
  $student->faculty_number = $form_state['input']['faculty_number'];
  if ($form_state['input']['gender'] == 0) {
    $student->gender = 'Male';
  }
  else {
    $student->gender = 'Female';
  }

  $query = db_insert('students')
      ->fields(array(
        'name' => $student->name,
        'faculty_number' => $student->faculty_number,
        'gender' => $student->gender,
      ))
      ->execute();

  $name = $form_state['values']['name'];
  drupal_set_message(t('Student with name: %name was added successfully to the database', array('%name' => $name)));
  $form_state['redirect'] = 'students';
}

/*
 * Update on submit
 */
function studentUpdate_submit($form, &$form_state) {

  $student = new stdClass();
  $student->name = $form_state['input']['name'];
  $student->faculty_number = $form_state['input']['faculty_number'];
  
  if ($form_state['input']['gender'] == 0) {
    $student->gender = 'Male';
  }
  else {
    $student->gender = 'Female';
  }

  db_update('students')
      ->fields(array(
        'name' => $student->name,
        'faculty_number' => $student->faculty_number,
        'gender' => $student->gender
      ))
      ->condition('sid', arg(1), '=')
      ->execute();
  drupal_set_message('Student was updated successfully');
  drupal_goto('students');
}

function edit_student($id) {
  $edit_form = "";
  $edit_form .= l('Back to Student list', 'students');
  $edit_form .= drupal_render(drupal_get_form('student_add_form'));

  return $edit_form;
}

function delete_student($sid) {
  $query = db_delete('students')
      ->condition('sid', $sid)
      ->execute();

  drupal_goto('students');
}