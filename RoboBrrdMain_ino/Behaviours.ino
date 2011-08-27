
void sensorReadings() {
    int pirReading = analogRead(pir);
    int tiltFBReading = analogRead(tiltFB);
    int tiltLRReading = analogRead(tiltLR);
    int ldrLReading = analogRead(ldrL);
    int ldrRReading = analogRead(ldrR);
    
    if(false) {
        Serial << " PIR: " << pirReading;
        Serial << " TiltFB: " << tiltFBReading;
        Serial << " TiltLR: " << tiltLRReading;
        Serial << " LDR L: " << ldrLReading;
        Serial << " LDR R: " << ldrRReading;
        Serial << endl;
    }
}

void passiveWingsBehaviour() {
    
    int curL = leftwing.read();
    int curR = rightwing.read();
    
    for(int i=0; i<5; i++) {
        leftwing.write(leftwing.read()+1);
        rightwing.write(rightwing.read()+1);
        delay(50);
    }
    
    for(int i=0; i<5; i++) {
        leftwing.write(leftwing.read()-1);
        rightwing.write(rightwing.read()-1);
        delay(50);
    }
    
    leftwing.write(curL);
    rightwing.write(curR);
    
}

void passiveLeftWingWave() {
    
    int curL = leftwing.read();
    
    for(int j=0; j<2; j++) {
        for(int i=60; i<80; i++) {
            leftwing.write(i);
            delay(20);
        }
        for(int i=80; i>60; i--) {
            leftwing.write(i);
            delay(20);
        }
    }
	
    //leftwing.write(curL);
    
}

void passiveRightWingWave() {
    
    int curR = rightwing.read();
    
    for(int j=0; j<2; j++) {
        for(int i=0; i<20; i++) {
            rightwing.write(i);
            delay(20);
        }
        for(int i=20; i>0; i--) {
            rightwing.write(i);
            delay(20);
        }
    }
    
    //rightwing.write(curR);
    
}

void passiveDownLook() {
    
    int curU = updown.read();
    
    if(curU >= 100) return; 
    
    for(int i=curU; i<100; i++) {
        updown.write(i);
        delay(30);
    }
    
    /*
	 for(int i=110; i>curU; i--) {
	 updown.write(i);
	 delay(5);
	 }
     */
    
}

void passiveUpLook() {
    
    int curU = updown.read();
    
    if(curU <= 90) return;
    
    for(int i=curU; i>90; i--) {
        updown.write(i);
        delay(30);
    }
    
    /*
	 for(int i=90; i<curU; i++) {
	 updown.write(i);
	 delay(10);
	 }
     */
    
}

void passiveLeftLook() {
    
    int curL = leftright.read();
    
    if(curL < 70) return;
    
    for(int i=curL; i>70; i--) {
        leftright.write(i);
        delay(10);
    }
    
}

void passiveRightLook() {
    
    int curR = leftright.read();
    
    if(curR > 110) return;
    
    for(int i=curR; i<110; i++) {
        leftright.write(i);
        delay(10);
    }
    
}

void partyBehaviour() {
    
    playTone((int)random(20,175), (int)random(70, 150));
    updateLights(true);
    updateLights(false);
    
}

void ldrBehaviour(int ldrL, int ldrR) {
    
	int current = leftright.read();
	
	if(ldrL < (ldrR+thresh) && ldrL > (ldrR-thresh)) {
        // neutral
		
		if(current < 90) {
			leftright.write(current+1);
		} else if(current > 90) {
			leftright.write(current-1);
		}
        
    } else if(ldrL > (ldrR+thresh)) {
        // left (but go to the right)
		sendToComm('R');
		
		if(current < 180) {
			leftright.write(current+1); // going towards 180
		} else {
			for(int i=0; i<6; i++) {
				moveRightWing(!alternate);
				alternate = !alternate;
				delay(80);
			}
			rightwing.write(20);
		}
        
    } else if(ldrL < (ldrR-thresh)) {
        // right
		sendToComm('L');
		
		if(current > 0) {
			leftright.write(current-1); // going towards 0
		} else {
			for(int i=0; i<6; i++) {
				moveLeftWing(!alternate);
				alternate = !alternate;
				delay(80);
			}
			leftwing.write(90);
		}
        
    }
	
	current = leftright.read();
    
	
	if(current < 90) {
		int c0 = 90-current;
		int c1 = (20*c0)/90;
		int c2 = 100-c1;
		updown.write(c2);
	} else if(current > 90) {
		int c0 = 90-(180-current);
		int c1 = (20*c0)/90;
		int c2 = 100-c1;
		updown.write(c2);
	} else {
		updown.write(100);
	}
	
	delay(10);
	
	/*
     if(ldrL < (ldrR+thresh) && ldrL > (ldrR-thresh)) {
     
     // neutral
     
     if(ldrStable >= 5000) {
     moveUpDown(100, 50);
     goMiddle();
     ldrStable = 0;
     }
     
     ldrStable++;
     
     } else if(ldrL > (ldrR+thresh)) {
     // left (but go to the right)
     updown.write(80);
     if(currentDir != 1) goMiddle(); 
     sendToComm('R');
     moveUpDown(80, 50);
     goRight();
     for(int i=0; i<6; i++) {
     moveRightWing(!alternate);
     alternate = !alternate;
     delay(80);
     }
     rightwing.write(20);
     ldrStable = 0;
     } else if(ldrL < (ldrR-thresh)) {
     // right
     if(currentDir != 1) goMiddle(); 
     sendToComm('L');
     moveUpDown(80, 50);
     goLeft();
     for(int i=0; i<6; i++) {
     moveLeftWing(!alternate);
     alternate = !alternate;
     delay(80);
     }
     leftwing.write(90);
     ldrStable = 0;
     
     }
	 */
    
}

void peekABooBehaviour(int ldrL, int ldrR) {
    
    if(ldrL <= (ldrLprev-50) || ldrR <= (ldrRprev-50)) {
        
        // dim the lights
        L1R = 255;//int(random(50, 255));
        L1G = 255;//int(random(50, 255));
        L1B = 255;//int(random(50, 255));
        R1R = L1R;//int(random(50, 255));
        R1G = L1G;//int(random(50, 255));
        R1B = L1B;//int(random(50, 255));
        L2R = int(random(50, 255));
        L2G = int(random(50, 255));
        L2B = int(random(50, 255));
        R2R = int(random(50, 255));
        R2G = int(random(50, 255));
        R2B = int(random(50, 255));
		
        fade( preL1R,    preL1G,      preL1B,  // L1 Start
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
        
        
        // wiggle the wings
        for(int i=0; i<6; i++) {
            moveLeftWing(alternate);
            moveRightWing(!alternate);
            alternate = !alternate;
            delay(150);
        }
        
        // bright lights
        L1R = 0;//int(random(50, 255));
        L1G = 0;//int(random(50, 255));
        L1B = 0;//int(random(50, 255));
        R1R = L1R;//int(random(50, 255));
        R1G = L1G;//int(random(50, 255));
        R1B = L1B;//int(random(50, 255));
        L2R = int(random(50, 255));
        L2G = int(random(50, 255));
        L2B = int(random(50, 255));
        R2R = int(random(50, 255));
        R2G = int(random(50, 255));
        R2B = int(random(50, 255));
        
        fade( preL1R,    preL1G,      preL1B,  // L1 Start
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
        
        // play music
        for(int i=0; i<3; i++) {
            playTone((int)random(100,200), (int)random(50, 200));
            delay(50);
        }
		
        // home
        updateLights(true);
        rightwing.write(20);
        leftwing.write(90);
        
    }
    
    ldrLprev = ldrL;
    ldrRprev = ldrR;
    
}

void pirBehaviour(int pirR) {
    
    if(pirR >= 500) {
        
        sendToComm('P');
        
        if(pirCount % 5 == 0) {
            
            //digitalWrite(flagPin, HIGH);
            openBeak();
            delay(100);
            randomChirp();
            //delay(1500);
            underbiteCloseBeak();
            delay(100);
            //digitalWrite(flagPin, LOW);
            
        } else {
            
            for(int i=0; i<6; i++) {
				moveLeftWing(alternate);
				moveRightWing(!alternate);
				alternate = !alternate;
				delay(150);
            }
            rightwing.write(20);
            leftwing.write(90);
            
        }
		
        pirCount++;
        
    }/* else {
	  pirCount = 1; 
	  }
	  */
    //Serial << "PIR Count: " << pirCount << endl;
    
}

