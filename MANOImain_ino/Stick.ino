


void slapShot(int repeat, int moveTime, int delayTime) {
  
  int slapShot_f2[17] = {
      HOME0-100,
      HOME1,
      HOME2+400,
      HOME3,
      HOME4,
      HOME5,
      HOME6+150,
      HOME16,
      HOME17,
      HOME18,
      HOME19,
      HOME20,
      HOME21,
      HOME22,
      HOME23,
      HOME24,
      HOME25
    };
    
  int slapShot_f3[17] = {
      HOME0+100,
      HOME1,
      HOME2+200,
      HOME3,
      HOME4,
      HOME5,
      HOME6-50,
      HOME16,
      HOME17,
      HOME18,
      HOME19,
      HOME20,
      HOME21,
      HOME22,
      HOME23,
      HOME24,
      HOME25
    };  
  
  
  // Frame 1
  ssc.setFrame(homeFrame, moveTime, delayTime);
  
  
  
  for(int i=0; i<repeat; i++) {
   
   // Frame 2
   ssc.setFrame(slapShot_f2, moveTime, delayTime);
   
   // Frame 3
   ssc.setFrame(slapShot_f3, moveTime, delayTime);
   
   // Frame 4
   ssc.setFrame(homeFrame, moveTime, delayTime);
    
  }
  
  
  
}



void otherShot(int repeat, int moveTime, int delayTime) {
  
  int otherShot_f2[17] = {
      HOME0-100,
      HOME1,
      HOME2+400,
      HOME3,
      HOME4,
      HOME5,
      HOME6+150,
      HOME16,
      HOME17,
      HOME18,
      HOME19,
      HOME20,
      HOME21,
      HOME22,
      HOME23,
      HOME24,
      HOME25
    };
    
  int otherShot_f3[17] = {
      HOME0+100,
      HOME1,
      HOME2+200,
      HOME3,
      HOME4,
      HOME5,
      HOME6-50,
      HOME16,
      HOME17,
      HOME18,
      HOME19,
      HOME20,
      HOME21,
      HOME22,
      HOME23,
      HOME24,
      HOME25
    };  
  
  
  // Frame 1
  ssc.setFrame(homeFrame, moveTime, delayTime);
  
  
  
  for(int i=0; i<repeat; i++) {
   
   // Frame 2
   ssc.setFrame(otherShot_f2, moveTime, delayTime);
   
   // Frame 3
   ssc.setFrame(otherShot_f3, moveTime, delayTime);
   
   // Frame 4
   ssc.setFrame(homeFrame, moveTime, delayTime);
    
  }
  
  
  
}


void initializeStick() {

  pinMode(stickLEDs, OUTPUT);
  digitalWrite(stickLEDs, HIGH);
  
  for(int i=0; i<=2; i++) {
    digitalWrite(stickLEDs, LOW);
    delay(100);
    digitalWrite(stickLEDs, HIGH);
    delay(100);
  }
  
Serial.println("Evaluating");
  
  delay(500);
  
  for(int i=0; i<=4; i++) {
   rightLDRevaluation += analogRead(rightLDR);
   leftLDRevaluation += analogRead(leftLDR);
   delay(500); 
  }
  
  rightLDRhome = (rightLDRevaluation / 5);
  leftLDRhome = (leftLDRevaluation / 5);

}

