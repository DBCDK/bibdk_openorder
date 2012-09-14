<?php
class bibdk_openorder extends TingClientRequest{
  // for now only handle checkOrderPolicyRequest
  protected $serviceRequester;
  protected $authentication;
  protected $pickUpAgencyId;
  protected $pid;
  protected $action;
  protected $outputType;

  public function setOutputType($value=NULL){
    $this->outputType = $value;
  }

  public function getOutputType(){
    return $this->outputType;
  }

  public function setAction($value=NULL){
    $this->action = $value;
  }

  public function getAction(){
    return $this->action;
  }

  public function setServiceRequester($value=NULL) {
    $this->serviceRequester = $value;
  }

  public function getServiceRequester() {
    return $this->serviceRequester;
  }

  public function getAuthentication(){
    return $this->authentication;
  }

  public function setAuthentication(array $value=array()){
    $this->authentication=$value;
  }

  public function setPickupAgencyId($value=NULL){
    $this->pickUpAgencyId = $value;
  }

  public function getPickupAgencyId(){
    return $this->pickUpAgencyId;
  }

  public function setPid($value=NULL){
    $this->pid = $value;
  }

  public function getPid(){
    return $this->pid;
  }


  protected function getRequest() {
    $this->setParameter('action', 'borrowerCheckRequest');

    $params = array('action','pickUpAgencyId','serviceRequester','authentication','pid');
    foreach ($params as $parameter) {
      $getter = 'get' . ucfirst($parameter);
      if ($value = $this->$getter()) {
        $this->setParameter($parameter, $value);
      }
    }
    return $this;
  }
  // empty;
  public function processResponse(stdClass $result) {
    return $result;
  }
}
?>