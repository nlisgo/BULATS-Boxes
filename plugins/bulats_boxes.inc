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
    $format = filter_format_load($this->options['body']['format']);

    if (filter_access($format)) {
      $form = array();
      $form['body'] = array(
        '#type' => 'text_format',
        '#base_type' => 'textarea',
        '#title' => t('English body'),
        '#default_value' => $this->options['body']['value'],
        '#rows' => 6,
        '#format' => $this->options['body']['format'] ? $this->options['body']['format'] : NULL,
        '#description' => t('The content of the block as shown to the user.'),
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
    if (!empty($this->options['body']['value']) && isset($this->options['body']['format'])) {
      $content = check_markup($this->options['body']['value'], $this->options['body']['format'], $langcode = '' /* TODO Set this variable. */, FALSE);
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
