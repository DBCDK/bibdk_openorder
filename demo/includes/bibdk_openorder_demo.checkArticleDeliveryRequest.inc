<?php

/**
 * OpenOrder Demo helper form.
 */
function _bibdk_openorder_demo_form_checkArticleDelivery(&$form) {

  $form['wrapper']['form']['lead']['header'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'h3',
    '#value' => 'checkArticleDeliveryRequest',
  );

  $form['wrapper']['form']['lead']['text'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'p',
    '#value' => 'Foo',
  );

  $form['wrapper']['form']['lead']['pid']['#tree'] = TRUE;

  $form['wrapper']['form']['lead']['pid'][] = array(
    '#type' => 'textfield', 
    '#title' => t('PID'), 
    '#default_value' => '870971-avis:89724244', 
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
  );

  $form['wrapper']['form']['lead']['pid'][] = array(
    '#type' => 'textfield', 
    '#title' => t('PID'), 
    '#default_value' => '870971-tsart:73355842', 
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
  );

  $form['wrapper']['form']['lead']['pid'][] = array(
    '#type' => 'textfield', 
    '#title' => t('PID'), 
    '#default_value' => '870971-tsart:36253215', 
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
  );


  $form['wrapper']['form']['result']['header'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'h3',
    '#value' => 'checkArticleDelivery',
    '#weight'   => '-10',
  );

  return $form;

}


/**
 * Ajax submit helper function.
 */
function _bibdk_openorder_ajax_submit_checkArticleDelivery(&$form, $form_state) {

  $results = array();

  foreach ($form_state['values']['pid'] as $n => $pid){

    $response[$n] = bibdk_openorder_do_checkArticleDeliveryRequest($pid);

    $articleDeliveryPossible = FALSE;
    if ( isset($response[$n]->checkArticleDeliveryResponse->articleDeliveryPossible) ) {
      $articleDeliveryPossible = $response[$n]->checkArticleDeliveryResponse->articleDeliveryPossible->{'$'};
    }
    $results[$n]['articleDeliveryPossible'] = 'articleDeliveryPossible: ' . (($articleDeliveryPossible) ? 'true' : 'false');

    $articleDeliveryPossibleReason = NULL;
    if ( isset($response[$n]->checkArticleDeliveryResponse->articleDeliveryPossibleReason) ) {
      $articleDeliveryPossibleReason = $response[$n]->checkArticleDeliveryResponse->articleDeliveryPossibleReason->{'$'};
    }
    $results[$n]['articleDeliveryPossibleReason'] = 'articleDeliveryPossibleReason: ' . (($articleDeliveryPossibleReason) ? $articleDeliveryPossibleReason : 'NULL');

    $articleDirect = NULL;
    if ( isset($response[$n]->checkArticleDeliveryResponse->articleDirect) ) {
      $articleDirect = $response[$n]->checkArticleDeliveryResponse->articleDirect->{'$'};
    }
    $results[$n]['articleDirect'] = 'articleDirect: ' . (($articleDirect) ? $articleDirect : 'NULL');

  }

  foreach ($results as $n => $result) {
    $results[$n] = implode('<br>', $results[$n]);
  }

  $form['wrapper']['form']['result']['#attributes']['class'][] = 'article-delivery-response';

  $form['wrapper']['form']['result']['text'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'div',
    '#value' => implode('</div><div>', $results),
  );

  $form['wrapper']['object']['text'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'pre',
    '#value' => print_r($response, 1),
  );

  return $form;

}


/**
 * Notes:
 * bibdk_sbkopi_ajax_parse_response() : move to bibdk_openorder?
 * _bibdk_sbkopi_set_xpath() : move to bibdk_openorder?
 */
