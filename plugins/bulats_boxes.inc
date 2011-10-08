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
    $this->language_default = language_default();
    
    $options = array();
    
    foreach ($this->languages as $lang)
    {
      $options[$lang->language] = array(
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
    $query = db_select('languages', '')
      ->condition('languages.enabled', 1, '=')
      ->fields('languages', array('language', 'name', 'native', 'direction', 'prefix'));

    $languages = array();
    $results = $query->execute();
    foreach ($results as $result) {
      $languages[$result->language] = $result;
    }

    return $languages;
  }

  /**
   * Implementation of boxes_box::options_form().
   */
  public function options_form(&$form_state) {
    $format = filter_format_load($this->options[$this->language_default->language]['format']);

    if (filter_access($format)) {
      
      $form = array();
      $languages = $this->languages;
      unset($languages[$this->language_default->language]);

      $form[$this->language_default->language] = array(
        '#type' => 'text_format',
        '#base_type' => 'textarea',
        '#title' => t($this->language_default->name.' body text'),
        '#default_value' => $this->options[$this->language_default->language]['value'],
        '#rows' => 6,
        '#format' => $this->options[$this->language_default->language]['format'] ? $this->options[$this->language_default->language]['format'] : NULL,
        '#description' => t('The content of the block as shown to the user.'),
      );
      
      
      foreach ($languages as $lang) {
        $form[$lang->language] = array(
          '#type' => 'text_format',
          '#base_type' => 'textarea',
          '#title' => t($lang->name.' body text'),
          '#default_value' => $this->options[$lang->language]['value'],
          '#rows' => 6,
          '#format' => $this->options[$lang->language]['format'] ? $this->options[$lang->language]['format'] : NULL,
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
    $content = '';
    if (!empty($this->options[$this->language_default->language]['value']) && isset($this->options[$this->language_default->language]['format'])) {
      $content = check_markup($this->options[$this->language_default->language]['value'], $this->options[$this->language_default->language]['format'], $langcode = '' /* TODO Set this variable. */, FALSE);
    }
    $title = isset($this->title) ? $this->title : NULL;
    return array(
      'delta' => $this->delta, // Crucial.
      'title' => $title,
      'subject' => $title,
      'content' => $content,
    );
  }
}
