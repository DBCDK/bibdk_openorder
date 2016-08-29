<?php

/**
 * OpenOrder Demo helper form.
 */
function _bibdk_openorder_demo_form_incrementRedirectStatRequest(&$form) {

  $form['wrapper']['form']['lead']['header'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'h3',
    '#value' => 'incrementRedirectStatRequest',
  );

  $form['wrapper']['form']['lead']['text'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'p',
    '#value' => 'Update statistics on redirects to [agencyId] local catalog.',
  );

  $form['wrapper']['form']['lead']['agencyId'] = array(
    '#type' => 'textfield', 
    '#title' => t('agencyId'), 
    '#default_value' => '100400', 
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
  );

  $form['wrapper']['form']['result']['header'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'h3',
    '#value' => 'incrementRedirectStat',
    '#weight'   => '-10',
  );

  return $form;

}


/**
 * Ajax submit helper function.
 */
function _bibdk_openorder_ajax_submit_incrementRedirectStat(&$form, $form_state) {

  $increment = bibdk_openorder_do_incrementRedirectStat($form_state['values']['agencyId']);

  $form['wrapper']['form']['result']['text'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'p',
    '#value' => 'incrementRedirectStat: ' . (($increment) ? 'true' : 'false'),
  );

  $form['wrapper']['object']['text'] = array(
    '#type'  => 'html_tag',
    '#tag'   => 'pre',
    '#value' => '',
  );

  return $form;
}


/*
<soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:open="http://oss.dbc.dk/ns/openorder">
   <soapenv:Header/>
   <soapenv:Body>
      <open:incrementRedirectStatRequest>
         <open:authentication>
            <open:groupIdAut>?</open:groupIdAut>
            <open:passwordAut>?</open:passwordAut>
            <open:userIdAut>?</open:userIdAut>
         </open:authentication>
         <open:agencyId>100400</open:agencyId>
         <open:outputType>json</open:outputType>
      </open:incrementRedirectStatRequest>
   </soapenv:Body>
</soapenv:Envelope>
*/