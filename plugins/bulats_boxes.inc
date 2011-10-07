<?php

/**
 * Custom Bulats Multi-language Box
 */
class boxes_bulats extends boxes_box {
	
  /**
   * Implementation of boxes_box::options_defaults().
   */
  public function options_defaults() {
    return array(
      'body' => array(
        'value' => '',
        'format' => filter_default_format(),
      ),
    );
  }

  /**
   * Implementation of boxes_box::options_form().
   */
  public function options_form(&$form_state) {
    $format = filter_format_load($this->options['english']['format']);

    if (filter_access($format)) {
      $form = array();
      $form['english'] = array(
        '#type' => 'text_format',
        '#base_type' => 'textarea',
        '#title' => t('English Body Text'),
        '#default_value' => $this->options['english']['value'],
        '#rows' => 6,
        '#format' => $this->options['english']['format'] ? $this->options['english']['format'] : NULL,
        '#description' => t('The English Version.'),
      );
	  $form['french'] = array(
        '#type' => 'text_format',
        '#base_type' => 'textarea',
        '#title' => t('French Body Text'),
        '#default_value' => $this->options['french']['value'],
        '#rows' => 6,
        '#format' => $this->options['french']['format'] ? $this->options['french']['format'] : NULL,
        '#description' => t('The French Version.'),
      );
	  $form['spanish'] = array(
        '#type' => 'text_format',
        '#base_type' => 'textarea',
        '#title' => t('Spanish Body Text'),
        '#default_value' => $this->options['spanish']['value'],
        '#rows' => 6,
        '#format' => $this->options['spanish']['format'] ? $this->options['spanish']['format'] : NULL,
        '#description' => t('The Spanish Version.'),
      );
	  $form['german'] = array(
        '#type' => 'text_format',
        '#base_type' => 'textarea',
        '#title' => t('English Body Text'),
        '#default_value' => $this->options['german']['value'],
        '#rows' => 6,
        '#format' => $this->options['german']['format'] ? $this->options['german']['format'] : NULL,
        '#description' => t('The German Version.'),
      );
      return $form;
    }
  }

  /**
   * Implementation of boxes_box::render().
   */
  public function render() {
    $content = '';
    if (!empty($this->options['english']['value'])) {
       if (isset($this->options['french']['format']) && !$this->options['french']['format'] && $language = 'fr') {
         $content = check_markup($this->options['french']['value'], $this->options['french']['format'], $langcode = '' /* TODO Set this variable. */, FALSE);
       }
	   elseif (isset($this->options['spanish']['format']) && !$this->options['spanish']['format'] && $language = 'es') {
         $content = check_markup($this->options['spanish']['value'], $this->options['spanish']['format'], $langcode = '' /* TODO Set this variable. */, FALSE);
       }
	   elseif (isset($this->options['german']['format']) && !$this->options['german']['format'] && $language = 'de') {
         $content = check_markup($this->options['german']['value'], $this->options['german']['format'], $langcode = '' /* TODO Set this variable. */, FALSE);
       }
	   if (isset($this->options['english']['format']) && !$this->options['english']['format']) {
         $content = check_markup($this->options['english']['value'], $this->options['english']['format'], $langcode = '' /* TODO Set this variable. */, FALSE);
       }
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
