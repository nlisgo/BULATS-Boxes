<?php

/**
 * Simple custom text box.
 */
class boxes_bulats extends boxes_box {
  /**
   * Implementation of boxes_box::options_defaults().
   */
   
  public $plugin;
  
  public $language_default;
  public $languages;
   
  public function options_defaults() {
    $this->languages = $this->enabled_languages();
    
    $options = array();
    
    foreach ($this->languages as $lang)
    {
      $options[$lang->language.'_title'] = array(
        'value' => '',
      );
      $options[$lang->language.'_body'] = array(
        'value' => '',
        'format' => filter_default_format(),
      );
    }
    
    return $options;
  }
  
  /**
   * Get enabled languages
   */
  public function enabled_languages() {
    $this->language_default = language_default();
    $query = db_select('languages', '')
      ->condition('languages.enabled', 1, '=')
      ->fields('languages', array('language', 'name', 'native', 'direction', 'prefix'));

    $languages = array();
    $results = $query->execute();
    foreach ($results as $result) {
      $languages[$result->language] = $result;
    }

    $language_default[$this->language_default->language] = $languages[$this->language_default->language];
    unset($languages[$this->language_default->language]);
    $languages = array_merge($language_default, $languages);

    return $languages;
  }

  /**
   * Implementation of boxes_box::options_form().
   */
  public function options_form(&$form_state) {
    $format = filter_format_load($this->options[$this->language_default->language.'_body']['format']);

    if (filter_access($format)) {
      $form = array();
      $languages = $this->languages;
      
      foreach ($languages as $lang) {
        $form[$lang->language] = array(
          '#type' => 'fieldset',
          '#title' => t($lang->name),
          '#collapsible' => TRUE,
          '#collapsed' => FALSE,
        );
	      $form[$lang->language][$lang->language.'_title'] = array(
          '#type' => 'textfield',
          '#title' => t('BOX TITLE'),
          '#default_value' => $this->options[$lang->language.'_title'],
          '#description' => t('The title of the box as shown to the user.'),
        );
        $form[$lang->language][$lang->language.'_body'] = array(
          '#type' => 'text_format',
          '#base_type' => 'textarea',
          '#title' => t('BOX BODY'),
          '#default_value' => $this->options[$lang->language.'_body']['value'],
          '#rows' => 6,
          '#format' => $this->options[$lang->language.'_body']['format'] ? $this->options[$lang->language.'_body']['format'] : NULL,
          '#description' => t('The content of the block as shown to the user.'),
        );
      }
      return $form;
    }
  }

  /**
   * Implementation of boxes_box::render().
   */
  public function render() {
    $title = NULL;
    $content = '';
    if (!empty($this->options[$this->language_default->language.'_body']['value']) && isset($this->options[$this->language_default->language.'_body']['format'])) {
      $title = isset($this->options[$this->language_default->language.'_title']) ? $this->options[$this->language_default->language.'_title'] : NULL;
      $content = check_markup($this->options[$this->language_default->language.'_body']['value'], $this->options[$this->language_default->language.'_body']['format'], $this->language_default->language, FALSE);
    }
    return array(
      'delta' => $this->delta, // Crucial.
      'title' => $title,
      'subject' => $title,
      'content' => $content,
    );
  }
}

