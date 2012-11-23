<?php

class BibdkOpenorderPolicyResponse {

  public $agencyCatalogueUrl;
  public $lookUpUrls;
  public $orderPossible;
  public $orderPossibleReason;
  public $orderCondition;
  public $response;
  public $checkOrderPolicyError;
  public $agencyId;

  public function getAgencyCatalogueUrl() {
    return isset($this->response->checkOrderPolicyResponse->agencyCatalogueUrl) ? $this->response->checkOrderPolicyResponse->agencyCatalogueUrl->{'$'} : NULL;
  }

  public function getLookUpUrl() {
    if (!isset($this->lookUpUrl) && isset($this->response->checkOrderPolicyResponse->lookUpUrl)) {
      $result = $this->parseFields($this->response->checkOrderPolicyResponse, array('lookUpUrl'));
      $this->lookUpUrls = (is_array($result)) ? reset($result) : $result;
    }
    return (is_array($this->lookUpUrls)) ? reset($this->lookUpUrls) : $this->lookUpUrls;
  }

  public function getLookUpUrls($id = 0) {
    return $this->lookUpUrls[$id];
  }

  public function getOrderPossible() {
    $bool = isset($this->response->checkOrderPolicyResponse->orderPossible) ? $this->response->checkOrderPolicyResponse->orderPossible->{'$'} : FALSE;
    return ($bool === 'TRUE');
  }

  public function getOrderPossibleReason() {
    return isset($this->response->checkOrderPolicyResponse->orderPossibleReason) ? $this->response->checkOrderPolicyResponse->orderPossibleReason->{'$'} : NULL;
  }

  public function getOrderCondition() {
    return $this->orderCondition;
  }

  public function getOrderConditionForLanguage() {
    return $this->orderCondition;
  }

  public function getCheckOrderPolicyError() {
    return isset($this->response->checkOrderPolicyError) ? $this->response->checkOrderPolicyError{'$'} : NULL;
  }

  public function setResponse($response) {
    $this->response = $response;
  }

  public function getAgencyId() {
    return $this->agencyId;
  }

  public function setAgencyId($agencyId) {
    $this->agencyId = $agencyId;
  }

  public function getUrls() {
    $urls = array();
    //TODO (mmj) theoretically several urls can be available but currently only one is delivered - should possibly be moved elsewhere
    if ($this->getLookUpUrl()) {
      $url = drupal_parse_url('reservations/catalogue_url/0');
      $urls['lookUpUrl'] = array(
        '#theme' => 'link',
        '#text' => t('link_to_local_library_lookup_url', array(), array('context' => 'bibdk_reservation')),
        '#path' => $url['path'],
        '#options' => array(
          'attributes' => array(),
          'html' => FALSE,
        ),
      );
    }
    if ($this->getAgencyCatalogueUrl()) {
      $urls['lookUpUrl'] = array(
        '#theme' => 'link',
        '#text' => t('link_to_local_library_catalogue_url', array(), array('context' => 'bibdk_reservation')),
        '#path' => $this->getAgencyCatalogueUrl(),
        '#options' => array(
          'attributes' => array(),
          'html' => FALSE,
        ),
      );
    }
    return $urls;
  }

  /**
   * @return BibdkOpenorderPolicyResponse
   */
  public static function SetObject() {
    $_SESSION['orderpolicy'] = new BibdkOpenorderPolicyResponse();
    return $_SESSION['orderpolicy'];
  }

  /**
   * @return BibdkOpenorderPolicyResponse
   */
  public static function GetObject() {
    return $_SESSION['orderpolicy'];
  }

  private function parseFields($object, array $fields) {
    $ret = null;
    if (!isset($object)) {
      return NULL;
    }
    if (is_array($object)) {
      foreach ($object as $o) {
        if (isset($o)) {
          $ret[] = self::parseFields($o, $fields);
        }
      }
      return $ret;
    }

    foreach ($fields as $field => $value) {
      if (is_array($value) && isset($object->$field)) {
        $ret[$field][] = self::parseFields($object->$field, $value);
      }
      elseif ($value == 'searchCode' && isset($object->$field)) {
        $ret[$field][] = self::_parseSearchCode($object->$field);
      }
      elseif ($value == 'header' && isset($object->$field)) {
        $ret[$value] = $object->$field->{'$'};
      }
      elseif (!is_array($value) && isset($object->$value) && is_array($object->$value)) {

        foreach ($object->$value as $val) {
          $ret[$value][] = $val->{'$'};
        }
      }
      elseif (!is_array($value) && isset($object->$value) && is_object($object->$value)) {
        $ret[$value] = $object->$value->{'$'};
      }
    }
    return $ret;
  }
}
