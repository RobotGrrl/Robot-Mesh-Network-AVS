int bothArmJingle_frame1[17] = {
      HOME0+200,
      HOME1,
      HOME2+leftArmOut,
      HOME3+leftArmForward,
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
    
int bothArmJingle_frame2[17] = {
      HOME0+200,
      HOME1-leftWristMovement,
      HOME2+leftArmOut,
      HOME3+leftArmForward+50,
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

int bothArmJingle_frame3[17] = {
      HOME0+200,
      HOME1+leftWristMovement,
      HOME2+leftArmOut,
      HOME3+leftArmForward,
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

int bothArmJingle_frame4[17] = {
      HOME0-200,
      HOME1,
      HOME2+leftArmOut,
      HOME3-leftArmForward,
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

int bothArmJingle_frame5[17] = {
      HOME0-200,
      HOME1-leftWristMovement,
      HOME2+leftArmOut,
      HOME3-(leftArmForward+50),
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

int bothArmJingle_frame6[17] = {
      HOME0-200,
      HOME1+leftWristMovement,
      HOME2+leftArmOut,
      HOME3-leftArmForward,
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


void bothArmJingle(int repeat) {
  
  for(int i=0; i<repeat; i++) {
  
  ssc.setFrame(bothArmJingle_frame1, 500, 0);
  
  for(int i=0; i<5; i++) {
  ssc.setFrame(bothArmJingle_frame2, 20, 0);
  ssc.setFrame(bothArmJingle_frame3, 20, 0);
  }
  
  ssc.setFrame(bothArmJingle_frame4, 500, 0);
  
  for(int i=0; i<5; i++) {
  ssc.setFrame(bothArmJingle_frame5, 20, 0);
  ssc.setFrame(bothArmJingle_frame6, 20, 0); 
  } 
  
  }
  
}

