/* 
 * RoboBrrdMain.c
 * For the RoboBrrd robot!
 * Utilizing the Robot Mesh Network AVS
 *
 * July 27, 2011
 * RobotGrrl.com 
 */

#include <Time.h>
#include <Servo.h> 
#include <Streaming.h>

boolean debug = true;

// Servos
Servo mouth, leftwing, rightwing, leftright, updown;

// Sensor pins
int pir(0), tiltFB(1), tiltLR(2), ldrL(3), ldrR(4);

// Servo pins
int mouthPin(8), leftwingPin(7), rightwingPin(6);
int leftrightPin(5), updownPin(4);

// LED pins
int redR(3), greenR(9), blueR(10);
int redL(11), greenL(12), blueL(13);

// Other pins
int interruptIncomming = 0; // on pin 2
int interruptOutgoing = 22;
int flagPin = 24;
int spkr = 26;

// LED Values
int L1R = 255;
int L1G = 255;
int L1B = 255;
int R1R = 255;
int R1G = 255;
int R1B = 255;
int L2R = 255;
int L2G = 255;
int L2B = 255;
int R2R = 255;
int R2G = 255;
int R2B = 255;
int preL1R = 0;
int preL1G = 0;
int preL1B = 255;
int preR1R = 0;
int preR1G = 0;
int preR1B = 255;
int preL2R = 0;
int preL2G = 0;
int preL2B = 255;
int preR2R = 0;
int preR2G = 0;
int preR2B = 255;

// Misc.
boolean alternate = true;
int pirCount = 1;
int thresh = 200;
int ldrStable = 0;
int currentDir = 1;
int ldrLprev = 0;
int ldrRprev = 0;
int pos = 0;
boolean passive = false;

// Counters
int triggerAttemptCount = 0;
int commAttemptCount = 0;

// Trigger flag
volatile boolean triggerFlag = false;

int rxBuffer[128];
int rxIndex = 0;

int action = 0;

boolean direction = true;

int sendFirst = 0;

// Initialize
void setup() {
    
	// Communication
	Serial.begin(9600);  // Console
    Serial1.begin(9600); // Comm
	Serial2.begin(9600); // iPad
    Serial3.begin(9600); // Xbee plug
    
	// Interrupts
	pinMode(interruptOutgoing, OUTPUT);
    digitalWrite(interruptOutgoing, LOW);
    
	attachInterrupt(interruptIncomming, trigger, RISING);
	digitalWrite(2, LOW);
    
    pinMode(flagPin, OUTPUT);
    digitalWrite(flagPin, LOW);
    
    pinMode(spkr, OUTPUT);
    
    // LEDs
    pinMode(redR, OUTPUT);
    pinMode(greenR, OUTPUT);
    pinMode(blueR, OUTPUT);
    pinMode(redL, OUTPUT);
    pinMode(greenL, OUTPUT);
    pinMode(blueL, OUTPUT);
    
    // Sensors
    pinMode(pir, INPUT);
    pinMode(tiltFB, INPUT);
    pinMode(tiltLR, INPUT);
    pinMode(ldrL, INPUT);
    pinMode(ldrR, INPUT);
    
    // Servos
    leftwing.attach(leftwingPin);
    rightwing.attach(rightwingPin);
    leftright.attach(leftrightPin);
    updown.attach(updownPin);
    
    // Home positions
    leftwing.write(90);
    rightwing.write(20);
    
    /*
    for(int i=0; i<180; i++) {
        leftright.write(i);
        delay(10);
    }
    */
     
    leftright.write(90);
    updown.write(95);
    moveBeak(180, 2, 10);
    
    boolean alt = false;
    for(int i=0; i<2; i++) {
        moveRightWing(alt);
        alt = !alt;
        delay(100);
    }
    
    if(debug) Serial << "woo!" << endl;
    
}

void loop() {
    //adkProgram();
    //dancePartyProgram();
    cosmicSoapProgram();
}

void cosmicSoapProgram() {
    
    if(Serial3.available() > 0) {
        
        char c = (char)Serial3.read();
        if(c == 'B') {
            direction = !direction;
        }
        
        if(direction) { // go to left
            leftright.write(leftright.read()-10);
        } else { // go to right
            leftright.write(leftright.read()+10);
        }
        
        Serial3.flush();
        updateLights(false);
        
    }

    int ldrL_t = analogRead(ldrL);
    int ldrR_t = analogRead(ldrR);
    int pir_t = analogRead(pir);
    
    if(sendFirst%3 == 0) {
    
        sendldrL(ldrL_t);
        sendldrR(ldrR_t);
    
    } else if(sendFirst%3 == 1) {
    
        sendldrR(ldrR_t);
        sendpir(pir_t);
        
    } else if(sendFirst%3 == 2) {
        
        sendpir(pir_t);
        sendldrL(ldrL_t);
        
    }
    
    sendFirst++;
        
}

void sendldrL(int ldrL_t) {
    if(ldrL_t >= 1000) {
        Serial3 << "#L" << ldrL_t << "!";
    } else if(ldrL_t >= 100) {
        Serial3 << "#L0" << ldrL_t << "!";
    } else if(ldrL_t >= 10) {
        Serial3 << "#L00" << ldrL_t << "!";
    } else if(ldrL_t >= 0) {
        Serial3 << "#L000" << ldrL_t << "!";
    }
}

void sendldrR(int ldrR_t) {
    if(ldrR_t >= 1000) {
        Serial3 << "#R" << ldrR_t << "!";
    } else if(ldrR_t >= 100) {
        Serial3 << "#R0" << ldrR_t << "!";
    } else if(ldrR_t >= 10) {
        Serial3 << "#R00" << ldrR_t << "!";
    } else if(ldrR_t >= 0) {
        Serial3 << "#R000" << ldrR_t << "!";
    }
}

void sendpir(int pir_t) {
    if(pir_t >= 1000) {
        Serial3 << "#P" << pir_t << "!";
    } else if(pir_t >= 100) {
        Serial3 << "#P0" << pir_t << "!";
    } else if(pir_t >= 10) {
        Serial3 << "#P00" << pir_t << "!";
    } else if(pir_t >= 0) {
        Serial3 << "#P000" << pir_t << "!";
    }
}


void dancePartyProgram() {
    
    if(Serial1.available() > 0) {
        char c = (char)Serial1.read();
        if(c == 'B') {
            direction = !direction;
        }
        
        if(direction) { // go to left
            leftright.write(leftright.read()-10);
        } else { // go to right
            leftright.write(leftright.read()+10);
        }
        
        Serial1.flush();
        updateLights(false);
        
    }
    
}

void adkProgram() {
    
    if(Serial1.available() > 0) {
        char c = (char)Serial1.read();
        Serial.println(c);
        if(c == 'A') {
            // big spell
            for(int i=0; i<10; i++) {
                randomBeak();
            }
            
        } else if(c == 'B') {
            // small spell
            boolean alt = false;
            for(int i=0; i<10; i++) {
                moveRightWing(alt);
                moveLeftWing(alt);
                alt = !alt;
                delay(10);
            }
        } else if(c == 'C') {
            updateLights(true);
        }
        Serial1.flush();
    }
    
}

void fftProgram() {
    
    if(Serial1.available() > 0) {
        char c = (char)Serial1.read();
        if(c == 'K') {
            
            boolean alt = false;
            for(int i=0; i<2; i++) {
                moveRightWing(alt);
                alt = !alt;
                delay(100);
            }
            
            if(debug) Serial << "r" << endl;
        }
        Serial1.flush();
    }
    
    if(debug) Serial << "a";
    
    /*
    while(!triggerFlag) {
        if(debug) Serial << "Trigger flag is false..." << endl;
        updateLights(false);
    }
    
    if(triggerFlag) {
        
        Serial << "The trigger flag!" << endl;
        
        
        // Send the flag to receive the message
        digitalWrite(interruptOutgoing, HIGH);
        delay(5);
        digitalWrite(interruptOutgoing, LOW);
        
        if(Serial1.available() > 0) {
            char c = (char)Serial1.read();
            
            if(debug) Serial << "Received: " << c << endl;
            
            if(c == 'K') {
                boolean alt = false;
                for(int i=0; i<5; i++) {
                    moveRightWing(alt);
                    alt = !alt;
                    delay(50);
                }
            }
            
        }
        
        Serial1.flush();
        triggerFlag = false;
        
    }
     */
    
}

/*
void readComm() {
    
    
    while(!triggerFlag) {
        if(debug) Serial << "Trigger flag is false..." << endl;
        updateLights(false);
    }
    
    if(triggerFlag) {
        
        Serial << "The trigger flag!" << endl;
        
        
        // Send the flag to receive the message
        digitalWrite(interruptOutgoing, HIGH);
        delay(5);
        digitalWrite(interruptOutgoing, LOW);
        
        int action = 0;
        
        while(rxIndex < LENGTH) {
            rxBuffer[rxIndex] = nextByte();
            rxIndex++;
        }
        
        //if(rxIndex == LENGTH) {
        
        if(debug) Serial << "Got the data!" << endl;
        
        char delim_start = (char)rxBuffer[0];
        action = (int)rxBuffer[2]-'0';
        char delim_end = (char)rxBuffer[3];
        
        Serial << "Action: " << action << endl;
        
        if(delim_start == '~' && delim_end == '!') {
            
            if(action == 1) {
                
                if(debug) Serial << "Worked!" << endl;
                
                boolean alt = false;
                for(int i=0; i<5; i++) {
                    moveRightWing(alt);
                    alt = !alt;
                    delay(50);
                }
                
            } else {
                if(debug) Serial << "The action was not 1!" << endl;
            }
            
        }
        
        action = 0;
        rxIndex = 0;
        Serial1.flush();
        
        //}
        
        triggerFlag = false;
        
    }
    
}
*/
 
void trigger() {
	triggerFlag = true;
}

byte nextByte() {
	while(1) {
		if(Serial1.available() > 0) {
			byte b = Serial1.read();
			if(debug) Serial << "Received byte: " << b << endl;
            commAttemptCount = 0;
			return b;
		}
        
        
        if(commAttemptCount >= 100) {
			commAttemptCount = 0;
			break;
		}
		
		commAttemptCount++;
        
		if(debug) Serial << "Waiting for next byte" << endl;
	}
	
}


// Example of sending data to the comm. board
// Originally used in MANOI
void periodicSend() {
        
    // Send some data to the communication board
    if(second()%30 == 0 || second()%60 == 0) {
        
        //digitalWrite(STATUS, LOW);
        
        //digitalWrite(LED, HIGH);
        delay(500);
        //digitalWrite(LED, LOW);
        
        // Signal that we want to send data
        digitalWrite(interruptOutgoing, HIGH);
        
        while(!triggerFlag) {
            // Waiting for trigger to send the data
            if(debug) Serial << "Waiting for the trigger" << endl;
            //digitalWrite(LED, HIGH);
            delay(50);
            //digitalWrite(LED, LOW);
            delay(50);
            // TODO: Make it give up at some point
            
            if(triggerAttemptCount >= 100) {
                triggerAttemptCount = 0;
                break;
            }
            
            triggerAttemptCount++;
            
        }
        
        // Ready to send data
        if(triggerFlag) {
            
            if(debug) Serial << "Going to send the message now" << endl;
            
            Serial1 << "E*";
            
            //digitalWrite(LED, HIGH);
            delay(1000);
            //digitalWrite(LED, LOW);
            
        }
        
        digitalWrite(interruptOutgoing, LOW);
        triggerFlag = false;
        triggerAttemptCount = 0;
        
    }
    
}


void sendToComm(char c) {
        
    digitalWrite(interruptOutgoing, HIGH);
    
    while(!triggerFlag) {
        // Waiting for trigger to send the data
        if(debug) Serial << "Waiting for the trigger" << endl;
        //digitalWrite(LED, HIGH);
        //delay(50);
        //digitalWrite(LED, LOW);
        //delay(50);
        
        if(triggerAttemptCount >= 100) {
            triggerAttemptCount = 0;
            break;
        }
        
        triggerAttemptCount++;
        
    }
    
    // Ready to send data
    if(triggerFlag) {
        
        if(debug) Serial << "Going to send the message now" << endl;
        
        Serial1 << c << "*";
        
        //digitalWrite(LED, HIGH);
        //delay(1000);
        //digitalWrite(LED, LOW);
        
    }
    
    digitalWrite(interruptOutgoing, LOW);
    triggerFlag = false;
    triggerAttemptCount = 0;
    
}

void sendPToComm() {
        
    digitalWrite(interruptOutgoing, HIGH);
    
    while(!triggerFlag) {
        // Waiting for trigger to send the data
        if(debug) Serial << "Waiting for the trigger" << endl;
        //digitalWrite(LED, HIGH);
        delay(50);
        //digitalWrite(LED, LOW);
        delay(50);
        // TODO: Make it give up at some point
        
        if(triggerAttemptCount >= 100) {
            triggerAttemptCount = 0;
            break;
        }
        
        triggerAttemptCount++;
        
    }
    
    // Ready to send data
    if(triggerFlag) {
        
        if(debug) Serial << "Going to send the message now" << endl;
        
        Serial1 << "P*";
        
        //digitalWrite(LED, HIGH);
        delay(1000);
        //digitalWrite(LED, LOW);
        
    }
    
    digitalWrite(interruptOutgoing, LOW);
    triggerFlag = false;
    triggerAttemptCount = 0;
    
}

/*
void sendET() {

    digitalWrite(interruptOutgoing, HIGH);
    
    // Waiting for trigger to send the data
    while(!triggerFlag) {
        
        if(debug) Serial << "Waiting for the trigger" << endl;
        //digitalWrite(LED, !digitalRead(LED));
        delay(50);
        
        if(triggerAttemptCount >= 100) {
            triggerAttemptCount = 0;
            break;
        }
        
        triggerAttemptCount++;
        
    }
    
    // Ready to send data
    if(triggerFlag) {
        
        if(debug) Serial << "Going to send the message now" << endl;
        
        CommTX.sendData();
        
    }
    
    digitalWrite(interruptOutgoing, LOW);
    triggerFlag = false;
    triggerAttemptCount = 0;
    
}
*/


void passiveRoutine() {
    
    if(passive) {
        
        updateLights(true);
        
        int randomBehaviour = (int)random(0, 7);
        
        switch(randomBehaviour) {
            case 0:
                passiveWingsBehaviour();
                break;
            case 1:
                passiveLeftWingWave();
                break;
            case 2:
                passiveRightWingWave();
                break;
            case 3:
                passiveDownLook();
                break;
            case 4:
                passiveUpLook();
                break;
            case 5:
                passiveLeftLook();
                break;
            case 6:
                passiveRightLook();
                break;
            default:
                break;
        }
        
    }
    
}


