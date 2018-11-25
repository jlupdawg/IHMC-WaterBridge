void pulseSonar(){

  float perceivedDuration; //This is a float to hold the signal transmitted by the dock
  
  sendRadioToDock();
  //Open boat sonars to recieve pulse

    if(perceivedDuration != 0){
      verifiedBoat = true;
      }
  
  }

void sendRadioToDock(){
  
  //Send signal to dock telling it that boat sonars are ready to recieve a signal
  
  }
