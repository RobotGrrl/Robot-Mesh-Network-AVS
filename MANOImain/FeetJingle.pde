int feetJingleArmsOut = 500;
int feetJingleHipsApart = 10;
int feetJingleFeetFlat = 100;
int feetJingleFeetFlat2 = -100;
  
  int feetJingle_keyframe1[17] = {
        HOME0,
        HOME1,
        HOME2+feetJingleArmsOut,
        HOME3,
        HOME4,
        HOME5+feetJingleArmsOut,
        HOME6,
        HOME16+feetJingleHipsApart,
        HOME17,
        HOME18,
        HOME19,
        HOME20+feetJingleFeetFlat,
        HOME21+feetJingleHipsApart,
        HOME22,
        HOME23,
        HOME24,
        HOME25+feetJingleFeetFlat
};

  int feetJingle_keyframe1_frame1[17] = {
        HOME0,
        HOME1,
        HOME2+feetJingleArmsOut+200,
        HOME3,
        HOME4,
        HOME5+feetJingleArmsOut-200,
        HOME6,
        HOME16+feetJingleHipsApart,
        HOME17,
        HOME18,
        HOME19,
        HOME20+feetJingleFeetFlat2,
        HOME21+feetJingleHipsApart,
        HOME22,
        HOME23,
        HOME24,
        HOME25+feetJingleFeetFlat2
};
  
  int feetJingle_keyframe2[17] = {
      HOME0,
      HOME1,
      HOME2+feetJingleArmsOut,
      HOME3,
      HOME4,
      HOME5+feetJingleArmsOut,
      HOME6,
      HOME16+feetJingleHipsApart,
      HOME17,
      HOME18,
      HOME19,
      HOME20+feetJingleFeetFlat,
      HOME21+feetJingleHipsApart,
      HOME22,
      HOME23,
      HOME24,
      HOME25+feetJingleFeetFlat
};

  int feetJingle_keyframe2_frame1[17] = {
      HOME0,
      HOME1,
      HOME2+feetJingleArmsOut-200,
      HOME3,
      HOME4,
      HOME5+feetJingleArmsOut+200,
      HOME6,
      HOME16+feetJingleHipsApart,
      HOME17,
      HOME18,
      HOME19,
      HOME20+feetJingleFeetFlat2,
      HOME21+feetJingleHipsApart,
      HOME22,
      HOME23,
      HOME24,
      HOME25+feetJingleFeetFlat2
};

void feetJingle(int repeat) {
  
  for(int i=0; i<repeat; i++) {
  ssc.setFrame(feetJingle_keyframe1, 200, 0); 
  ssc.setFrame(feetJingle_keyframe1_frame1, 200, 0);
  ssc.setFrame(feetJingle_keyframe2, 200, 0);  
  ssc.setFrame(feetJingle_keyframe2_frame1, 200, 0); 
  }  
  
}


