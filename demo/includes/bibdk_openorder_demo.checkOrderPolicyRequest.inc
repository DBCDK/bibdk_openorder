<?php

/**
 * OpenOrder Demo helper form.
 */
function _bibdk_openorder_demo_form_checkOrderPolicyRequest(&$form) {

  $form['wrapper']['form']['lead']['header'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'h3',
    '#value' => 'checkOrderPolicyRequest',
  );

  $form['wrapper']['form']['lead']['text'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'p',
    '#value' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.',
  );

  $form['wrapper']['form']['lead']['pid'] = array(
    '#type' => 'textfield', 
    '#title' => t('PID'), 
    '#default_value' => '870970-basis:28373988', 
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
  );

  $form['wrapper']['form']['lead']['pickupAgencyId'] = array(
    '#type' => 'textfield', 
    '#title' => t('pickupAgencyId'), 
    '#default_value' => 'DK-100400', 
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
  );

  $form['wrapper']['form']['result']['header'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'h3',
    '#value' => 'OrderPolicy',
    '#weight'   => '-10',
  );

  return $form;

}


/**
 * Ajax submit helper function.
 */
function _bibdk_openorder_ajax_submit_checkOrderPolicy(&$form, $form_state) {

  $orderpolicy = bibdk_openorder_do_checkOrderPolicy($form_state['values']['pickupAgencyId'], $form_state['values']['pid']);

  $form['wrapper']['form']['result']['text'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'p',
    '#value' => 'orderPossible: ' . (($orderpolicy->getOrderPossible()) ? 'true' : 'false'),
  );

  $form['wrapper']['object']['text'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'pre',
    '#value' => htmlentities(print_r($orderpolicy, 1)),
  );

  return $form;
}


/*
<soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:open="http://oss.dbc.dk/ns/openorder">
   <soapenv:Header/>
   <soapenv:Body>
      <open:checkOrderPolicyRequest>
         <open:authentication>
            <open:groupIdAut>****</open:groupIdAut>
            <open:passwordAut>****</open:passwordAut>
            <open:userIdAut>****</open:userIdAut>
         </open:authentication>
         <open:bibliographicRecordId>28373988</open:bibliographicRecordId>
         <open:bibliographicRecordAgencyId>870970-basis</open:bibliographicRecordAgencyId>
         <open:pickUpAgencyId>715100</open:pickUpAgencyId>
         <open:serviceRequester>190101</open:serviceRequester>
         <open:outputType>json</open:outputType>
      </open:checkOrderPolicyRequest>
   </soapenv:Body>
</soapenv:Envelope>
*/