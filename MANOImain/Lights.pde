
  
  void updateLights() {
    
  L1R = int(random(50, 255));
  L1G = int(random(50, 255));
  L1B = int(random(50, 255));
  R1R = int(random(50, 255));
  R1G = int(random(50, 255));
  R1B = int(random(50, 255));
  L2R = int(random(50, 255));
  L2G = int(random(50, 255));
  L2B = int(random(50, 255));
  R2R = int(random(50, 255));
  R2G = int(random(50, 255));
  R2B = int(random(50, 255));
  
  fade2( preL1R,    preL1G,      preL1B,  // L1 Start
         L1R,       L1G,         L1B,     // L1 Finish
         preR1R,    preR1G,      preR1B,  // R1 Start
         R1R,       R1G,         R1B,     // R1 Finish
         preL2R,    preL2G,      preL2B,  // L2 Start
         L2R,       L2G,         L2B,     // L2 Finish
         preR2R,    preR2G,      preR2B,  // R2 Start
         R2R,       R2G,         R2B,     // R2 Finish
         1);
         
  preL1R = L1R;
  preL1G = L1G;
  preL1B = L1B;
  preR1R = R1R;
  preR1G = R1G;
  preR1B = R1B;
  preL2R = L2R;
  preL2G = L2G;
  preL2B = L2B;
  preR2R = R2R;
  preR2G = R2G;
  preR2B = R2B;
  
  
    
  }
  
  
  
  void fade2 ( int startL1_R,  int startL1_G,  int startL1_B, 
             int finishL1_R, int finishL1_G, int finishL1_B,
             int startR1_R,  int startR1_G,  int startR1_B,
             int finishR1_R, int finishR1_G, int finishR1_B,
             int startL2_R,  int startL2_G,  int startL2_B, 
             int finishL2_R, int finishL2_G, int finishL2_B,
             int startR2_R,  int startR2_G,  int startR2_B,
             int finishR2_R, int finishR2_G, int finishR2_B,
             int stepTime ) {
            
  int skipEveryL1_R = 256/abs(startL1_R-finishL1_R); 
  int skipEveryL1_G = 256/abs(startL1_G-finishL1_G);
  int skipEveryL1_B = 256/abs(startL1_B-finishL1_B); 
  int skipEveryR1_R = 256/abs(startR1_R-finishR1_R); 
  int skipEveryR1_G = 256/abs(startR1_G-finishR1_G);
  int skipEveryR1_B = 256/abs(startR1_B-finishR1_B); 
  int skipEveryL2_R = 256/abs(startL2_R-finishL2_R); 
  int skipEveryL2_G = 256/abs(startL2_G-finishL2_G);
  int skipEveryL2_B = 256/abs(startL2_B-finishL2_B); 
  int skipEveryR2_R = 256/abs(startR2_R-finishR2_R); 
  int skipEveryR2_G = 256/abs(startR2_G-finishR2_G);
  int skipEveryR2_B = 256/abs(startR2_B-finishR2_B); 
  
  for(int i=0; i<256; i++) {
    
    if(startL1_R<finishL1_R) {
      if(i<=finishL1_R) {
        if(i%skipEveryL1_R == 0) {
          analogWrite(redL1, i);
        } 
      }
    } else if(startL1_R>finishL1_R) {
      if(i>=(256-startL1_R)) {
        if(i%skipEveryL1_R == 0) {
          analogWrite(redL1, 256-i); 
        }
      } 
    }
    
    if(startL1_G<finishL1_G) {
      if(i<=finishL1_G) {
        if(i%skipEveryL1_G == 0) {
          analogWrite(greenL1, i);
        } 
      }
    } else if(startL1_G>finishL1_G) {
      if(i>=(256-startL1_G)) {
        if(i%skipEveryL1_G == 0) {
          analogWrite(greenL1, 256-i); 
        }
      } 
    }
          
    if(startL1_B<finishL1_B) {
      if(i<=finishL1_B) {
        if(i%skipEveryL1_B == 0) {
          analogWrite(blueL1, i);
        } 
      }
    } else if(startL1_B>finishL1_B) {
      if(i>=(256-startL1_B)) {
        if(i%skipEveryL1_B == 0) {
          analogWrite(blueL1, 256-i); 
        }
      } 
    }
    
    if(startR1_R<finishR1_R) {
      if(i<=finishR1_R) {
        if(i%skipEveryR1_R == 0) {
          analogWrite(redR1, i);
        } 
      }
    } else if(startR1_R>finishR1_R) {
      if(i>=(256-startR1_R)) {
        if(i%skipEveryR1_R == 0) {
          analogWrite(redR1, 256-i); 
        }
      } 
    }
    
    if(startR1_G<finishR1_G) {
      if(i<=finishR1_G) {
        if(i%skipEveryR1_G == 0) {
          analogWrite(greenR1, i);
        } 
      }
    } else if(startR1_G>finishR1_G) {
      if(i>=(256-startR1_G)) {
        if(i%skipEveryR1_G == 0) {
          analogWrite(greenR1, 256-i); 
        }
      } 
    }
          
    if(startR1_B<finishR1_B) {
      if(i<=finishR1_B) {
        if(i%skipEveryR1_B == 0) {
          analogWrite(blueR1, i);
        } 
      }
    } else if(startR1_B>finishR1_B) {
      if(i>=(256-startR1_B)) {
        if(i%skipEveryR1_B == 0) {
          analogWrite(blueR1, 256-i); 
        }
      } 
    }
    
    // ---------
    
    if(startL2_R<finishL2_R) {
      if(i<=finishL2_R) {
        if(i%skipEveryL2_R == 0) {
          analogWrite(redL2, i);
        } 
      }
    } else if(startL2_R>finishL2_R) {
      if(i>=(256-startL2_R)) {
        if(i%skipEveryL2_R == 0) {
          analogWrite(redL2, 256-i); 
        }
      } 
    }
    
    if(startL2_G<finishL2_G) {
      if(i<=finishL2_G) {
        if(i%skipEveryL2_G == 0) {
          analogWrite(greenL2, i);
        } 
      }
    } else if(startL2_G>finishL2_G) {
      if(i>=(256-startL2_G)) {
        if(i%skipEveryL2_G == 0) {
          analogWrite(greenL2, 256-i); 
        }
      } 
    }
          
    if(startL2_B<finishL2_B) {
      if(i<=finishL2_B) {
        if(i%skipEveryL2_B == 0) {
          analogWrite(blueL2, i);
        } 
      }
    } else if(startL2_B>finishL2_B) {
      if(i>=(256-startL2_B)) {
        if(i%skipEveryL2_B == 0) {
          analogWrite(blueL2, 256-i); 
        }
      } 
    }
    
    if(startR2_R<finishR2_R) {
      if(i<=finishR2_R) {
        if(i%skipEveryR2_R == 0) {
          analogWrite(redR2, i);
        } 
      }
    } else if(startR2_R>finishR2_R) {
      if(i>=(256-startR2_R)) {
        if(i%skipEveryR2_R == 0) {
          analogWrite(redR2, 256-i); 
        }
      } 
    }
    
    if(startR2_G<finishR2_G) {
      if(i<=finishR2_G) {
        if(i%skipEveryR2_G == 0) {
          analogWrite(greenR2, i);
        } 
      }
    } else if(startR2_G>finishR2_G) {
      if(i>=(256-startR2_G)) {
        if(i%skipEveryR2_G == 0) {
          analogWrite(greenR2, 256-i); 
        }
      } 
    }
          
    if(startR2_B<finishR2_B) {
      if(i<=finishR2_B) {
        if(i%skipEveryR2_B == 0) {
          analogWrite(blueR2, i);
        } 
      }
    } else if(startR2_B>finishR2_B) {
      if(i>=(256-startR2_B)) {
        if(i%skipEveryR2_B == 0) {
          analogWrite(blueR2, 256-i); 
        }
      } 
    }

    delay(stepTime);
      
  }

  }
