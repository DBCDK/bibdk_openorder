<?php

/**
 * OpenOrder Demo helper form.
 */
function _bibdk_openorder_demo_form_placeOrderRequest(&$form) {

  $form['wrapper']['form']['lead']['header'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'h3',
    '#value' => 'placeOrderRequest',
  );

  $form['wrapper']['form']['lead']['text'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'p',
    '#value' => 'Make a reservation for user nn in ',
  );

  $form['wrapper']['form']['lead']['copy'] = array(
    '#type' => 'textfield', 
    '#title' => t('copy'), 
    '#default_value' => 'false', 
    '#required' => TRUE,
    '#description' => '',
  );

  $form['wrapper']['form']['lead']['exactEdition'] = array(
    '#type' => 'textfield', 
    '#title' => t('exactEdition'), 
    '#default_value' => 'true', 
    '#required' => TRUE,
    '#description' => '',
  );

  $form['wrapper']['form']['lead']['needBeforeDate'] = array(
    '#type' => 'textfield', 
    '#title' => t('needBeforeDate'), 
    '#default_value' => date('Y-m-d\TH:i:s', strtotime('now+3 months')), 
    '#required' => TRUE,
    '#description' => 'f. ex.: 2016-11-25T00:00:00',
  );

  $form['wrapper']['form']['lead']['orderSystem'] = array(
    '#type' => 'textfield', 
    '#title' => t('orderSystem'), 
    // '#default_value' => 'bibliotekdk', 
    '#default_value' => 'netpunkt', 
    '#required' => TRUE,
    '#description' => '',
  );

  $form['wrapper']['form']['lead']['pickUpAgencyId'] = array(
    '#type' => 'textfield', 
    '#title' => t('pickUpAgencyId'), 
    '#default_value' => 'DK-100400', 
    '#required' => TRUE,
    '#description' => '',
  );

  $form['wrapper']['form']['lead']['pid'] = array(
    '#type' => 'textfield', 
    '#title' => t('pid'), 
    '#default_value' => '870970-basis:28211481', 
    '#required' => TRUE,
    '#description' => '',
  );

  $form['wrapper']['form']['lead']['serviceRequester'] = array(
    '#type' => 'textfield', 
    '#title' => t('serviceRequester'), 
    '#default_value' => '190101', 
    '#required' => TRUE,
    '#description' => '',
  );

  $form['wrapper']['form']['lead']['userIdAuthenticated'] = array(
    '#type' => 'textfield', 
    '#title' => t('userIdAuthenticated'), 
    '#default_value' => 'false', 
    '#required' => TRUE,
    '#description' => 'Get userIdAuthenticated value from borcheck. Default "false"',
  );

  $form['wrapper']['form']['lead']['userId'] = array(
    '#type' => 'textfield', 
    '#title' => t('userId'), 
    '#default_value' => '1234567890', 
    '#required' => TRUE,
    '#description' => '',
  );

  $form['wrapper']['form']['lead']['userName'] = array(
    '#type' => 'textfield', 
    '#title' => t('userName'), 
    '#default_value' => 'Fubar Testesen', 
    '#required' => TRUE,
    '#description' => '',
  );

  $form['wrapper']['form']['lead']['userMail'] = array(
    '#type' => 'textfield', 
    '#title' => t('userMail'), 
    '#default_value' => 'fubar@dbc.dk', 
    '#required' => TRUE,
    '#description' => '',
  );

  $form['wrapper']['form']['lead']['verificationReferenceSource'] = array(
    '#type' => 'textfield', 
    '#title' => t('verificationReferenceSource'), 
    '#default_value' => 'dbcdatawell', 
    '#required' => TRUE,
    '#description' => '',
  );

  $form['wrapper']['form']['lead']['action'] = array(
    '#type' => 'textfield', 
    '#title' => t('action'), 
    '#default_value' => 'action', 
    '#required' => TRUE,
    '#description' => '',
  );

  $form['wrapper']['form']['result']['header'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'h3',
    '#value' => 'placeOrder',
    '#weight'   => '-10',
  );

  return $form;

}


/**
 * Ajax submit helper function.
 */
function _bibdk_openorder_ajax_submit_placeOrderRequest(&$form, $form_state) {

  $keys = array(
    'copy', 'exactEdition', 'needBeforeDate',
    'orderSystem', 'pickUpAgencyId', 'pid', 
    'serviceRequester', 'userId', 'userIdAuthenticated',
    'userMail', 'userName', 'verificationReferenceSource'
  );

  foreach ($keys as $key){
    if (!array_key_exists($form_state['values'], $key)) {
      $params[$key] = $form_state['values'][$key];
    }
  }
  
  $response = bibdk_openorder_do_placeOrder($params);

  // orderId may be NULL in case of a timeout or a 404
  $orderId = NULL;
  if ( isset($response->placeOrderResponse->orderPlaced) ) {
    $orderId = $response->placeOrderResponse->orderPlaced->orderId->{'$'};
  }

  $result = 'The order has been placed';
  if ( isset($response->placeOrderResponse->orderNotPlaced) || empty($orderId) ) {
    $result = ( isset($response->placeOrderResponse->orderNotPlaced->placeOrderError->{'$'}) ) 
      ? $response->placeOrderResponse->orderNotPlaced->placeOrderError->{'$'} 
      : 'Order timed out or returned a 404';
  }

  $form['wrapper']['form']['result']['text'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'p',
    '#value' => 'placeOrderRequest: ' . $result,
  );

  $form['wrapper']['object']['text'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'pre',
    '#value' => print_r($response, 1),
  );

  return $form;
}


/*
<placeOrderRequest>
<authentication><groupIdAut>010100</groupIdAut><passwordAut>20Koster</passwordAut><userIdAut>netpunkt</userIdAut></authentication>
<copy>false</copy>
<exactEdition>true</exactEdition>
<needBeforeDate>2016-11-25T00:00:00</needBeforeDate>
<orderSystem>bibliotekdk</orderSystem>
<pickUpAgencyId>DK-100400</pickUpAgencyId>
<pid>870970-basis:28211481</pid>
<serviceRequester>190101</serviceRequester>
<userId>1234567890</userId>
<userIdAuthenticated>false</userIdAuthenticated>
<userMail>jgn@dbc.dk</userMail>
<userName>test jgn test</userName>
<verificationReferenceSource>dbcdatawell</verificationReferenceSource>
<outputType>json</outputType>
</placeOrderRequest>

<soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:open="http://oss.dbc.dk/ns/openorder">
   <soapenv:Header/>
   <soapenv:Body>
      <open:placeOrderRequest>
         <open:authentication>
            <open:groupIdAut>?</open:groupIdAut>
            <open:passwordAut>?</open:passwordAut>
            <open:userIdAut>?</open:userIdAut>
         </open:authentication>
         <open:agencyId>100400</open:agencyId>
         <open:outputType>json</open:outputType>
      </open:placeOrderRequest>
   </soapenv:Body>
</soapenv:Envelope>
*/