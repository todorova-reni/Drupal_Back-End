<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function cinema_preprocess_page(&$variables) {
  // Gather node classes.
   if (theme_get_setting('cinema_width') == 'fluid') {
    $variables['classes_array'][] = 'page-fluid';  
   } 
   if (theme_get_setting('cinema_width') == 'fixed') {
    $variables['classes_array'][] = 'fixed';  
   } 
   if (theme_get_setting('cinema_width') == 'small') {
    $variables['classes_array'][] = 'page-width-768';  
   }
   if (theme_get_setting('cinema_width') == 'medium') {
    $variables['classes_array'][] = 'page-width-992';  
   }
   if (theme_get_setting('cinema_width') == 'large') {
    $variables['classes_array'][] = 'page-width-1200';  
   }   
 }
