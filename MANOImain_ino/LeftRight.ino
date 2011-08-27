
void left(int repeat, int moveTime, int delayTime) {
  
 int left_f2[17] = {
      HOME0+150,
      HOME1,
      HOME2+400,
      HOME3-300,
      HOME4,
      HOME5,
      HOME6,
      HOME16,
      HOME17-50,
      HOME18,
      HOME19-25,
      HOME20,
      HOME21,
      HOME22,
      HOME23,
      HOME24,
      HOME25
    };
    
 int left_f4[17] = {
      HOME0-150,
      HOME1,
      HOME2+200,
      HOME3-300,
      HOME4,
      HOME5,
      HOME6,
      HOME16,
      HOME17+25,
      HOME18,
      HOME19+50,
      HOME20,
      HOME21,
      HOME22,
      HOME23,
      HOME24,
      HOME25
    };
  
  
  
 for(int i=0; i<=repeat; i++) {
  
  // Frame 1
  ssc.setFrame(homeFrame, moveTime, delayTime);
  
  // Frame 2
  ssc.setFrame(left_f2, moveTime, delayTime);
  
  // Frame 3
  ssc.setFrame(homeFrame, moveTime, delayTime);
  
  // Frame 4
  ssc.setFrame(left_f4, moveTime, delayTime);
  
 }
 
 
 
 lastMove = 4;
 
}




void right(int repeat, int moveTime, int delayTime) {
  
 int right_f2[17] = {
      HOME0+150,
      HOME1,
      HOME2+400,
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
      HOME22+25,
      HOME23,
      HOME24+50,
      HOME25
    };
    
 int right_f4[17] = {
      HOME0-150,
      HOME1,
      HOME2+200,
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
      HOME22-50,
      HOME23,
      HOME24-25,
      HOME25
    }; 
  
  
  
 for(int i=0; i<repeat; i++) {
  
  // Frame 1
  ssc.setFrame(homeFrame, moveTime, delayTime);
 
  // Frame 2
  ssc.setFrame(right_f2, moveTime, delayTime);
  
  // Frame 3
  ssc.setFrame(homeFrame, moveTime, delayTime);
  
  // Frame 4
  ssc.setFrame(right_f4, moveTime, delayTime);
  
 }
 
 
 
 lastMove = 5;
 
}
