int tangoHeadTilt = 400;
int tangoHandTilt = 200;
int tangoHandIn = 120;
int tangoHandUp = 500;
int tangoArmUp = 500;
int tangoArmTilt = 600;
int tangoHipTilt = 200;
int leanBack = -25;

int tango_keyframe1[17] = {
      HOME0-tangoHeadTilt,
      HOME1+tangoHandTilt,
      HOME2-tangoHandIn,
      HOME3-tangoHandUp,
      HOME4,
      HOME5+tangoArmUp,
      HOME6+tangoArmTilt,
      HOME16+tangoHipTilt,
      HOME17+leanBack,
      HOME18,
      HOME19,
      HOME20,
      HOME21-tangoHipTilt,
      HOME22+leanBack,
      HOME23,
      HOME24,
      HOME25
};

int tango_keyframe2[17] = {
      HOME0+tangoHeadTilt,
      HOME1,
      HOME2+tangoArmUp,
      HOME3+tangoArmTilt,
      HOME4+tangoHandTilt,
      HOME5-tangoHandIn,
      HOME6+tangoHandUp,
      HOME16-tangoHipTilt,
      HOME17+leanBack,
      HOME18,
      HOME19,
      HOME20,
      HOME21+tangoHipTilt,
      HOME22+leanBack,
      HOME23,
      HOME24,
      HOME25
};

void tango(int repeat) {
  
  for(int i=0; i<repeat; i++) {
  ssc.setFrame(tango_keyframe1, 800, 50);
  ssc.setFrame(tango_keyframe2, 800, 50);
  }
  
}
