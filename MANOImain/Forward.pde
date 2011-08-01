void forward(int repeat, int moveTime, int delayTime) {
  
 int forward_f2[17] = {
      HOME0+150,
      HOME1,
      HOME2+400,
      HOME3-300,
      HOME4,
      HOME5,
      HOME6,
      HOME16,
      HOME17-55,
      HOME18,
      HOME19-50,
      HOME20,
      HOME21,
      HOME22+45,
      HOME23,
      HOME24+50,
      HOME25
    };
    
  int forward_f4[17] = {
      HOME0-150,
      HOME1,
      HOME2+200,
      HOME3+300,
      HOME4,
      HOME5,
      HOME6,
      HOME16,
      HOME17+55,
      HOME18,
      HOME19+50,
      HOME20,
      HOME21,
      HOME22-45,
      HOME23,
      HOME24-50,
      HOME25
    }; 
  
  
  
 for(int i=0; i<repeat; i++) {
   
   // Frame 1
   ssc.setFrame(homeFrame, moveTime, delayTime);
    
   // Frame 2
   ssc.setFrame(forward_f2, moveTime, delayTime);
  
   // Frame 3
   ssc.setFrame(homeFrame, moveTime, delayTime);
    
   // Frame 4
   ssc.setFrame(forward_f4, moveTime, delayTime);
  
  } 
  
  
  
  lastMove = 3;
  
}

