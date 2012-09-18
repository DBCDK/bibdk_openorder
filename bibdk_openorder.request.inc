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
  protected $userAddress;
  protected $userName;
  protected $userMail;
  protected $userTelephone;
  protected $verificationReferenceSource;
  protected $copy;
  protected $exactEdition;
  protected $userIdAuthenticated;
  protected $userIdType;

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
  
  public function setUserAddress($userAddress){
    $this->userAddress = $userAddress; 
  }
  
  public function getUserAddress(){
    return $this->userAddress; 
  }
  
  public function setUserName($userName){
    $this->userName = $userName; 
  }
  
  public function getUserName(){
    return $this->userName;
  }
  
  public function setUserMail($userMail){
    $this->userMail = $userMail; 
  }
  
  public function getUserMail(){
    return $this->userMail;
  }
  
  public function setUserTelephone($userTelephone){
    $this->userTelephone = $userTelephone; 
  }
  
  public function getUserTelephone(){
    return $this->userTelephone;
  }
  
  public function setVerificationReferenceSource($value=NULL){
    $this->verificationReferenceSource = $value;
  }

  public function getVerificationReferenceSource() {
    return $this->verificationReferenceSource;
  }
  
  public function setCopy($value=NULL){
    $this->copy = $value;
  }

  public function getCopy(){
    return $this->copy;
  }
  
  public function setExactEdition($value=NULL){
    $this->exactEdition=$value;
  }

  public function getExactEdition(){
    return $this->exactEdition;
  }
  
  public function setUserIdAuthenticated($value=NULL){
    $this->userIdAuthenticated = $value;
  }

  public function getUserIdAuthenticated(){
    return $this->userIdAuthenticated;
  }
  
  public function setUserIdType($userIdType) {
    $this->userIdType = $userIdType;
  }
  
  public function getUserIdType() {
    return $this->userIdType;
  }

  
  // setters/getters for checkOrderPolicyRequest
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
              'orderSystem','verificationReferenceSource','copy','exactEdition','userIdAuthenticated', 'userAddress', 'userId', 'userName', 'userMail', 'userTelephone');
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
