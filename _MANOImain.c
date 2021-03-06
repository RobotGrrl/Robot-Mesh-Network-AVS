/*
 * MANOImain.c
 * For the best hockey playing humanoid robot!
 * Utilizing the Robot Mesh Network AVS
 *
 * July 29, 2011
 * RobotGrrl.com
 */

#include <NewSoftSerial.h>
#include <Streaming.h>
#include <SSC32.h>
#include <stdio.h>
#include <Wire.h>
#include <Time.h>

boolean debug = true;

// Home positions
int HOME0 = 1800;
int HOME1 = 1500;
int HOME2 = 1100;
int HOME3 = 1300;
int HOME4 = 1300-500;   // 1300 for hockey, 800 for normal
int HOME5 = 1600;
int HOME6 = 1300; //+100;
int HOME16 = 1550;
int HOME17 = 1250;
int HOME18 = 1000;
int HOME19 = 1600+15;//+35;
int HOME20 = 1600;
int HOME21 = 1500;
int HOME22 = 1250;
int HOME23 = 1000;
int HOME24 = 1580+15;//35;
int HOME25 = 1600;

int redL1 = 30;//3;
int redR1 = 6;
int greenL1 = 31;//4;
int greenR1 = 7;
int blueL1 = 32;//2;
int blueR1 = 5;
int redL2 = 9;
int redR2 = 12;
int greenL2 = 10;
int greenR2 = 13;
int blueL2 = 8;
int blueR2 = 11;

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

int z(0), y(1), x(2), gyro(3), fsr(4), ir(5);
int xval(0), yval(0), zval(0), gyroval(0), fsrval(0), irval(0);

int homeFrame[17] = {
	HOME0,
	HOME1,
	HOME2,
	HOME3,
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

int leftArmOut = 100;
int leftArmForward = 500;
int leftWristMovement = 200;
int rightArmOut = 100;
int rightArmForward = 500;
int rightWristMovement = 200;

// Nunchuck
int joy_x_axis;
int joy_y_axis;
int accel_x_axis; 
int accel_y_axis;
int accel_z_axis;
int z_button;
int c_button;

// Hockey stick
int stickLEDs(22), rightLDR(7), leftLDR(8), rightLDRval(0), leftLDRval(0);

// Logics
int lastMove;

int rightLDRevaluation(0);
int leftLDRevaluation(0);

int rightLDRhome(0);
int leftLDRhome(0);

SSC32 ssc(true);

bool receivedMessage = false;
int messageLength = 0;
char fsrCmd[] = {'F', 'S', 'R'};
char irCmd[] = {'I', 'R'};
char ledCmd[] = {'L', 'E', 'D'};
char bothArmJngl[] = {'B', 'A', 'J', 'N', 'G', 'L' };
char ftJngl[] = { 'F', 'T', 'J', 'N', 'G', 'L' };
char shotCmd[] = {'s', 'h', 'o', 't'};
char idnrCmd[] = {'i', 'd', 'n', 'r'};
int it = 0;
byte newByte = 0;
int said = 0;
bool validCmd = true;
int ii = 0;


// All the pins
int interruptIncomming = 2;
int interruptOutgoing = 23;
int LED = 24; // blue
int STATUS = 25; // green

// Counters
int triggerAttemptCount = 0;
int commAttemptCount = 0;

// Trigger flag
volatile boolean triggerFlag = false;

int rxBuffer[128];
int rxIndex = 0;

// Initialize
void setup() {
    
	// Communication
    Serial.begin(9600);  // Console
	Serial1.begin(9600); // Comm
	Serial2.begin(9600); // I forget
    Serial3.begin(9600); // I forget
    
	// Outputs
	pinMode(LED, OUTPUT);
	pinMode(STATUS, OUTPUT);
	
	// Interrupts
	pinMode(interruptOutgoing, OUTPUT);
	attachInterrupt(0, trigger, RISING);
	
	//Serial2.begin(9600); // why is this here? NO IDEA!
	
	for(int i=0; i<7; i++) {
		ssc.servoMode(i, true);
	}
	
	for(int i=16; i<25; i++) {
		ssc.servoMode(i, true); 
	}
	
	ssc.servoMode(31, true);
	
	//ssc.setFrame(homeFrame, 100, 100);
	
	pinMode(z, INPUT);
	pinMode(y, INPUT);
	pinMode(x, INPUT);
	pinMode(gyro, INPUT);
	pinMode(ir, INPUT);
	pinMode(fsr, INPUT);
	
	//pinMode(redL1, OUTPUT);
	//pinMode(greenL1, OUTPUT);
	//pinMode(blueL1, OUTPUT);
	pinMode(redL2, OUTPUT);
	pinMode(greenL2, OUTPUT);
	pinMode(blueL2, OUTPUT);
	pinMode(redR1, OUTPUT);
	pinMode(greenR1, OUTPUT);
	pinMode(blueR1, OUTPUT);
	pinMode(redR2, OUTPUT);
	pinMode(greenR2, OUTPUT);
	pinMode(blueR2, OUTPUT);
	
	//Serial.begin(9600); // why is this down here? NO IDEA!
	//Serial3.begin(9600); // and this one too? NO IDEA!
	
	updateLights();
	
	fade2( preL1R,    preL1G,      preL1B,  // L1 Start
		  12,         0,           255,     // L1 Finish
		  preR1R,    preR1G,      preR1B,   // R1 Start
		  12,         0,           255,     // R1 Finish
		  preL2R,    preL2G,      preL2B,   // L2 Start
		  12,         0,           255,     // L2 Finish
		  preR2R,    preR2G,      preR2B,   // R2 Start
		  12,         0,           255,     // R2 Finish
		  1);
	
	//initializeStick();
	//nunchuck_init();
	
	ssc.setFrame(homeFrame, 100, 100);
    
}

void loop() {
    
    fftProgram();
	
}

void fftProgram() {
    
    if(Serial1.available() > 0) {
        char c = (char)Serial1.read();
        if(c == 'S') {
            rightHandShakeSorta(1);
            if(debug) Serial << "r" << endl;
        }
        Serial.flush();
    }
    
    /*
    while(!triggerFlag) {
        if(debug) Serial << "Trigger flag is false..." << endl;
        updateLights();
    }
    
    if(triggerFlag) {
        
        Serial << "The trigger flag!" << endl;
        
        
        // Send the flag to receive the message
        digitalWrite(interruptOutgoing, HIGH);
        delay(5);
        digitalWrite(interruptOutgoing, LOW);
        
        if(Serial1.available() > 0) {
            char c = (char)Serial1.read();
            
            if(c == 'S') rightHandShake(1);
            
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
        updateLights();
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
                
                bothArmJingle(3);
                
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
        
        //Serial1 << "heeeeeeeeeeeeeeeyyyooooooooooooooo" << endl;
        ET.sendData();
        
    }
    
    digitalWrite(interruptOutgoing, LOW);
    triggerFlag = false;
    triggerAttemptCount = 0;
    
}
*/

