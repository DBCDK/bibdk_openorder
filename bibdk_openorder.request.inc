<?php
class bibdk_openorder extends TingClientRequest{
  // attributes for checkOrderPolicyRequest
  protected $serviceRequester;
  protected $authentication;
  protected $pickUpAgencyId;
  protected $pid;
  protected $action;
  protected $outputType;
  // extra attributes for placeOrderRequest
  protected $needBeforeDate;
  protected $orderSystem;
  protected $userId;
  protected $verificationReferenceSource;
  protected $copy;
  protected $exactEdition;
  protected $userIdAuthenticated;

  public function setUserIdAuthenticated($value=NULL){
    $this->userIdAuthenticated = $value;
  }

  public function getUserIdAuthenticated(){
    return $this->userIdAuthenticated;
  }

  public function setExactEdition($value=NULL){
    $this->exactEdition=$value;
  }

  public function getExactEdition(){
    return $this->exactEdition;
  }

  public function setCopy($value=NULL){
    $this->copy = $value;
  }

  public function getCopy(){
    return $this->copy;
  }

  public function setNeedBeforeDate($value=NULL){
    $this->needBeforeDate = $value;
  }

  public function getNeedBeforeDate(){
    return $this->needBeforeDate;
  }

  public function setOrderSystem($value=NULL){
    $this->orderSystem = $value;
  }

  public function getOrderSystem(){
    return $this->orderSystem;
  }

  public function setUserId($value=NULL){
    $this->userId = $value;
  }

  public function getUserId(){
    return $this->userId;
  }

  public function setVerificationReferenceSource($value=NULL){
    $this->verificationReferenceSource = $value;
  }

  public function getVerificationReferenceSource() {
    return $this->verificationReferenceSource;
  }

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

    $params = array('action','pickUpAgencyId','serviceRequester','authentication','pid', 'needBeforeDate',
              'orderSystem','userId','verificationReferenceSource','copy','exactEdition','userIdAuthenticated');
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
