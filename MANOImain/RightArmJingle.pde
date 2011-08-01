

// Starts off going to the front

int rightArmJingle_frame1[17] = {
      HOME0,
      HOME1,
      HOME2,
      HOME3,
      HOME4,
      HOME5+rightArmOut,
      HOME6+rightArmForward,
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
    
int rightArmJingle_frame2[17] = {
      HOME0,
      HOME1,
      HOME2,
      HOME3,
      HOME4-rightWristMovement,
      HOME5+rightArmOut,
      HOME6+(rightArmForward-170),
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

int rightArmJingle_frame3[17] = {
      HOME0,
      HOME1,
      HOME2,
      HOME3,
      HOME4+rightWristMovement,
      HOME5+rightArmOut,
      HOME6+rightArmForward,
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

int rightArmJingle_frame4[17] = {
      HOME0,
      HOME1,
      HOME2,
      HOME3,
      HOME4,
      HOME5+rightArmOut,
      HOME6-rightArmForward,
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

int rightArmJingle_frame5[17] = {
      HOME0,
      HOME1,
      HOME2,
      HOME3,
      HOME4-rightWristMovement,
      HOME5+rightArmOut,
      HOME6-(rightArmForward+50),
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

int rightArmJingle_frame6[17] = {
      HOME0,
      HOME1,
      HOME2,
      HOME3,
      HOME4+rightWristMovement,
      HOME5+rightArmOut,
      HOME6-rightArmForward,
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


void rightArmJingle(int repeat) {
  
  for(int i=0; i<repeat; i++) {
    
  ssc.setFrame(rightArmJingle_frame1, 500, 0);
  
  for(int i=0; i<5; i++) {
  ssc.setFrame(rightArmJingle_frame2, 20, 0);
  ssc.setFrame(rightArmJingle_frame3, 20, 0);
  }
  
  ssc.setFrame(rightArmJingle_frame4, 500, 0);
  
  for(int i=0; i<5; i++) {
  ssc.setFrame(rightArmJingle_frame5, 20, 0);
  ssc.setFrame(rightArmJingle_frame6, 20, 0); 
  } 
  
  }
  
}

