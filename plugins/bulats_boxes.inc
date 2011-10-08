<?php

/**
 * Simple custom text box.
 */
class boxes_bulats extends boxes_box {
  /**
   * Implementation of boxes_box::options_defaults().
   */
   
  public $plugin;
   
  public function options_defaults() {
    return array(
      'english_title' => array(
        'value' => '',
        'format' => filter_default_format(),
      ),
	  'english_body' => array(
        'value' => '',
        'format' => filter_default_format(),
      ),
	  'french_title' => array(
        'value' => '',
        'format' => filter_default_format(),
      ),
      'french_body' => array(
        'value' => '',
        'format' => filter_default_format(),
      ),
	  'spanish_title' => array(
        'value' => '',
        'format' => filter_default_format(),
      ),
      'spanish_body' => array(
        'value' => '',
        'format' => filter_default_format(),
      ),
	  'german_title' => array(
        'value' => '',
        'format' => filter_default_format(),
      ),
      'german_body' => array(
        'value' => '',
        'format' => filter_default_format(),
      ),
    );
  }

  /**
   * Implementation of boxes_box::options_form().
   */
  public function options_form(&$form_state) {
    $format = filter_format_load($this->options['english_body']['format']);

    if (filter_access($format)) {
      $form = array();
	  $form['english_title'] = array(
        '#type' => 'textfield',
        '#title' => t('English Title'),
        '#default_value' => $this->options['english_title'],
        '#description' => t('English Block Title.'),
      );
      $form['english_body'] = array(
        '#type' => 'text_format',
        '#base_type' => 'textarea',
        '#title' => t('English Body Text'),
        '#default_value' => $this->options['english_body']['value'],
        '#rows' => 6,
        '#format' => $this->options['english_body']['format'] ? $this->options['english_body']['format'] : NULL,
        '#description' => t('The English version of the block as shown to the user.'),
      );
	  $form['french_title'] = array(
        '#type' => 'textfield',
        '#title' => t('French Title'),
        '#default_value' => $this->options['french_title'],
        '#description' => t('French Block Title.'),
      );
	  $form['french_body'] = array(
        '#type' => 'text_format',
        '#base_type' => 'textarea',
        '#title' => t('French Body Text'),
        '#default_value' => $this->options['french_body']['value'],
        '#rows' => 6,
        '#format' => $this->options['french_body']['format'] ? $this->options['french_body']['format'] : NULL,
        '#description' => t('The French version of the block as shown to the user.'),
      );
	  $form['spanish_title'] = array(
        '#type' => 'textfield',
        '#title' => t('Spanish Title'),
        '#default_value' => $this->options['spanish_title'],
        '#description' => t('Spanish Block Title.'),
      );
	  $form['spanish_body'] = array(
        '#type' => 'text_format',
        '#base_type' => 'textarea',
        '#title' => t('Spanish Body Text'),
        '#default_value' => $this->options['spanish_body']['value'],
        '#rows' => 6,
        '#format' => $this->options['spanish_body']['format'] ? $this->options['spanish_body']['format'] : NULL,
        '#description' => t('The Spanish version of the block as shown to the user.'),
      );
	  $form['german_title'] = array(
        '#type' => 'textfield',
        '#title' => t('German Title'),
        '#default_value' => $this->options['german_title'],
        '#description' => t('German Block Title.'),
      );
	  $form['german_body'] = array(
        '#type' => 'text_format',
        '#base_type' => 'textarea',
        '#title' => t('German Body Text'),
        '#default_value' => $this->options['german_body']['value'],
        '#rows' => 6,
        '#format' => $this->options['german_body']['format'] ? $this->options['german_body']['format'] : NULL,
        '#description' => t('The German version of the block as shown to the user.'),
      );
      return $form;
    }
  }

  /**
   * Implementation of boxes_box::render().
   */
   

  public function render() {
	
	global $language;
    $content = '';
	
    if (!empty($this->options['french_body']['value']) && isset($this->options['french_body']['format']) && $language->language == 'fr') {
      $title = isset($this->options['french_title']) ? $this->options['french_title'] : NULL;
	  $content = check_markup($this->options['french_body']['value'], $this->options['french_body']['format'], $langcode = 'fr' /* TODO Set this variable. */, FALSE);
    }
	elseif (!empty($this->options['spanish_body']['value']) && isset($this->options['spanish_body']['format']) && $language->language == 'es') {
	  $title = isset($this->options['spanish_title']) ? $this->options['spanish_title'] : NULL;
      $content = check_markup($this->options['spanish_body']['value'], $this->options['spanish_body']['format'], $langcode = 'es' /* TODO Set this variable. */, FALSE);
    }
	elseif (!empty($this->options['german_body']['value']) && isset($this->options['german_body']['format']) && $language->language == 'de') {
	  $title = isset($this->options['german_title']) ? $this->options['german_title'] : NULL;
      $content = check_markup($this->options['german_body']['value'], $this->options['german_body']['format'], $langcode = 'de' /* TODO Set this variable. */, FALSE);
    }
	elseif (!empty($this->options['english_body']['value']) && isset($this->options['english_body']['format']) && $language->language == 'en') {
	  $title = isset($this->options['english_title']) ? $this->options['english_title'] : NULL;
      $content = check_markup($this->options['english_body']['value'], $this->options['english_body']['format'], $langcode = 'en' /* TODO Set this variable. */, FALSE);
    }
	
    
    return array(
      'delta' => $this->delta, // Crucial.
      'title' => $title,
      'subject' => $title,
      'content' => $content,
    );
  }
}

