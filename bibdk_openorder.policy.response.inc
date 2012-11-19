<?php

class OrderPolicy {
  public $agencyCatalogueUrl, $lookUpUrl, $orderPossible, $orderPossibleReason, $orderCondition, $response, $checkOrderPolicyError;
  
  public function __construct($response){
    $this->response = $response;
  }
  
  public function getAgencyCatalogueUrl() {
    return isset($this->response->checkOrderPolicyResponse->agencyCatalogueUrl) ?  $this->response->checkOrderPolicyResponse->agencyCatalogueUrl->{'$'} : NULL;
  }

  public function getLookUpUrl() {
    return isset($this->response->checkOrderPolicyResponse->lookUpUrl) ?  $this->response->checkOrderPolicyResponse->lookUpUrl->{'$'} : NULL;
  }

  public function getOrderPossible() {
    $bool =  isset($this->response->checkOrderPolicyResponse->orderPossible) ? $this->response->checkOrderPolicyResponse->orderPossible->{'$'} : FALSE;
    return ($bool === 'TRUE');
  }

  public function getOrderPossibleReason() {
    return isset($this->response->checkOrderPolicyResponse->orderPossibleReason) ?  $this->response->checkOrderPolicyResponse->orderPossibleReason->{'$'} : NULL;
  }

  public function getOrderCondition() {
    return $this->orderCondition;
    return isset($this->response->checkOrderPolicyResponse->orderCondition) ?  $this->response->checkOrderPolicyResponse->orderCondition->{'$'} : NULL;
  }
  
  public function getOrderConditionForLanguage() {
    return $this->orderCondition;
    return isset($this->response->checkOrderPolicyResponse->orderCondition) ?  $this->response->checkOrderPolicyResponse->orderCondition->{'$'} : NULL;
  }
  
  //$res->checkOrderPolicyResponse->checkOrderPolicyError
  public function getCheckOrderPolicyError() {
    return isset($this->response->checkOrderPolicyError) ?  $this->response->checkOrderPolicyError{'$'} : NULL;
  }
  
  public function getMessages(){
    $messages = array();
    if ($this->getLookUpUrl()){
      $messages['lookUpUrl'] = array(
        '#theme' => 'link',
        '#text' => $this->getLookUpUrl(),
        '#path' => $this->getLookUpUrl(),        
        '#options' => array(
           'attributes' => array(),
        ),
      );
      }
    if ($this->getAgencyCatalogueUrl()){
      $messages['lookUpUrl'] = array(
        '#theme' => 'link',
        '#text' => $this->getAgencyCatalogueUrl(),
        '#path' => $this->getAgencyCatalogueUrl(),
        '#options' => array(
          'attributes' => array(),
        ),
      );
      }
      return $messages;
  }
  /*private function getOrderReasonText(){
    $reason = $this->getOrderPossibleReason();
    $reason_place_holder = NULL;
    switch ($reason) {
    case 'not_owned_ILL_loc': //Example 1
      $reason_place_holder = t('not_owned_ILL_loc');
      break;
    case 'owned_wrong_mediumType': //Example 2
      $reason_place_holder = t('owned_wrong_mediumType');
      break;
    case 'owned_accepted': //Example 3
      $reason_place_holder = t('owned_accepted');
      break;
    default: //TODO Implement exaample 5 when openOrder/openSearch is ready - US
      $reason_place_holder = $reason;
      drupal_set_message('Unknown response: \'' . $reason . '\' Watchdog\'ed', 'error');
      watchdog('bibdk_reservation_form_step_3', 'Unknown response from openOrder: ' . $reason, NULL, WATCHDOG_ERROR);
      break;
  }
  return $reason_place_holder;
    
  }*/
  
}