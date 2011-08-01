int frame1_leftHandShake[17] = {
      HOME0+10,
      HOME1+200,
      HOME2+100,
      HOME3-300,
      HOME4,
      HOME5,
      HOME6,
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
    
int frame2_leftHandShake[17] = {
      HOME0-10,
      HOME1-200,
      HOME2+100,
      HOME3-300,
      HOME4,
      HOME5,
      HOME6,
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
    
int frame1_rightHandShake[17] = {
      HOME0+10,
      HOME1,
      HOME2,
      HOME3,
      HOME4+200,
      HOME5+100,
      HOME6+300,
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
    
int frame2_rightHandShake[17] = {
      HOME0-10,
      HOME1,
      HOME2,
      HOME3,
      HOME4-200,
      HOME5+100,
      HOME6+300,
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
    
    
    
void leftHandShake(int repeat) {
 for(int i=0; i<repeat; i++) {
  ssc.setFrame(frame1_leftHandShake, 100, 10);
  ssc.setFrame(frame2_leftHandShake, 100, 10);
 } 
 ssc.setFrame(homeFrame, 200, 10);
}

void rightHandShake(int repeat) {
 for(int i=0; i<repeat; i++) {
  ssc.setFrame(frame1_rightHandShake, 100, 10);
  ssc.setFrame(frame2_rightHandShake, 100, 10);
 } 
 ssc.setFrame(homeFrame, 200, 10);
}

