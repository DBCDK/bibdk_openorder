<?php

class BibdkOpenorderPolicyResponse {

  private $agencyCatalogueUrl;
  private $lookUpUrls;
  private $orderPossible;
  private $orderPossibleReason;
  private $orderCondition;
  private $response;
  private $checkOrderPolicyError;
  private $agencyId;

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
    return isset($this->response->checkOrderPolicyResponse->checkOrderPolicyError) ? $this->response->checkOrderPolicyResponse->checkOrderPolicyError->{'$'} : NULL;
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

  /* \brief parse searchCode,display elements
   * @param array of stdObjects
   * return array of form []['display','searchCode']
   */
  private static function _parseSearchCode($stdObjects) {
    if (!is_array($stdObjects)) {
      $stdObjects = array($stdObjects);
    }

    foreach ($stdObjects as $object) {
      $subject['searchCode'] = self::_getSearchCodeElement($object->searchCode);
      $subject['display'] = isset($object->display) ? $object->display->{'$'} : NULL;
      $ret[] = $subject;
    }

    return $ret;
  }

  private static function _getSearchCodeElement($stdObject) {
    $value = (isset($stdObject->{'$'})) ? $stdObject->{'$'} : NULL;

    if (isset($stdObject->{'@phrase'})) {
      $term = $stdObject->{'@phrase'}->{'$'};
    }
    elseif (isset($stdObject->{'@word'})) {
      $term = $stdObject->{'@word'}->{'$'};
    }

    if (isset($value) && isset($term)) {
      return $term . "=" . $value;
    }
    else {
      return;
    }
  }
}
