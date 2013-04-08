<?php

/**
 * Admin page; Menu callback.
 */
function annotator_admin() {
  $form = $plugin_options = array();
  
  $form['plugins'] = array(
    '#type' => 'fieldset',
    '#title' => t('Plugins'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  ctools_include('plugins');
  $plugins = ctools_get_plugins('annotator', 'annotator');
  foreach ($plugins as $plugin) {
    $class = ctools_plugin_get_class($plugin, 'handler');
    $instance = new $class($plugin);
    if ($instance_settings = $instance->settingsForm()) {
      $settings['annotator_' . $plugin['name']] = array(
        '#tree' => TRUE,
        '#type' => 'fieldset',
        '#title' => $plugin['label'],
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $settings['annotator_' . $plugin['name']] += (array) $instance->settingsForm();
    }
    $plugin_options[ucfirst($plugin['name'])] = $plugin['label'];
  }

  $annotator_plugins = variable_get('annotator_plugins', array());
  
  $form['plugins']['annotator_plugins'] = array(
    '#type' => 'checkboxes',
    '#description' => t('Enable the desired annotator plugins'),
    '#options' => $plugin_options,
    '#default_value' => $annotator_plugins,
  );
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Plugin settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['settings'] += (array) $settings;
  return system_settings_form($form);
}

function annotator_admin_general() {
  $type_options = annotator_get_available_node_types();
  $enabled_node_types = variable_get('annotator_enabled_node_types');
  $dom_selector = variable_get('annotator_dom_selector');

  $form['base_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Annotator Settings'),
    '#description' => '',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['base_settings']['annotator_enabled_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Allowed Node Types'),
    '#options' => $type_options,
    '#default_value' => $enabled_node_types,
    '#description' => t('Select the node types that you would like to'
      . ' include the annotator on.'),
  );
  $form['base_settings']['annotator_dom_selector'] = array(
    '#type' => 'textfield',
    '#title' => t('Selector'),
    '#default_value' => $dom_selector,
    '#description' => t('The dom element class or id to attach the annotator'
      . ' to.  This should be a valid css/javascript selector. eg "#content" or'
      . ' ".content".  Any values following a comma will be stripped out.'),
  );
  return system_settings_form($form);
}