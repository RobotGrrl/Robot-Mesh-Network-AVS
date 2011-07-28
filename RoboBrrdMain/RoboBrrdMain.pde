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
#include <EasyTransfer.h>

boolean debug = false;

// Servos
Servo mouth, leftwing, rightwing, leftright, updown;

// Sensor pins
int pir(A0), tiltFB(1), tiltLR(2), ldrL(3), ldrR(4);

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

// Counters
int triggerAttemptCount = 0;
int commAttemptCount = 0;

// Trigger flag
volatile boolean triggerFlag = false;

// EasyTransfer
EasyTransfer ET;

struct MESH_DATA {
    //put your variable definitions here for the data you want to send
    //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
    int attention;
    int valence;
    int stance;
    
    int action_t;
    int action_t0;
    
    int robot;
    
    int sense_1;
    int sense_2;
    int sense_3;
    int sense_4;
    int sense_5;
    
    int world_L;
    int world_R;
    int world_F;
};

MESH_DATA RBdata_tx;

// Initialize
void setup() {
    
	// Communication
	Serial.begin(9600);  // Console
    Serial1.begin(9600); // Comm
	Serial2.begin(9600); // iPad
    ET.begin(details(RBdata_tx), &Serial1); // Comm
    
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
    leftright.write(90);
    updown.write(95);
    moveBeak(180, 2, 10);
    
    // ET Data
    RBdata_tx.attention = 1;
    RBdata_tx.valence = 0;
    RBdata_tx.stance = 0;
    
    RBdata_tx.action_t = 0;
    RBdata_tx.action_t0 = 0;
    
    RBdata_tx.robot = 0;
    
    RBdata_tx.sense_1 = 0;
	RBdata_tx.sense_2 = 0;
    RBdata_tx.sense_3 = 0;
    RBdata_tx.sense_4 = 0;
    RBdata_tx.sense_5 = 0;
    
    RBdata_tx.world_L = 0;
    RBdata_tx.world_R = 0;
    RBdata_tx.world_F = 0;
    
    delay(3000);
    sendET();
    
}

void loop() {
    
    updateLights(false);
    delay(1000);
    
    /*
     while(!triggerFlag) {
     if(debug) Serial << "Trigger flag is false..." << endl;
     
     
     // * * * * * * * * * * * * *
     // Do whatever activity here
     // * * * * * * * * * * * * *
     
     //sensorReadings();
     
     //ldrBehaviour(ldrLReading, ldrRReading);
     //pirBehaviour(pirReading);
     //exerciseBehaviour(100);
     
     //        leftwing.write(60);
     //        delay(2000);
     //        
     //        leftwing.write(90);
     //        delay(2000);
     //        
     //        leftwing.write(120);
     //        delay(2000);
     
     //moveLeftWing(alternate);
     
     //moveRightWing(!alternate);
     //moveLeftWing(!alternate);
     //alternate = !alternate;
     //delay(1000);
     
     }
     */
    
    /*
	if(triggerFlag) {
        
        
		if(debug) Serial << "Trigger flag is set, sending outgoing interrupt" << endl;
		//digitalWrite(STATUS, LOW);
		
		//digitalWrite(LED, HIGH);
		
		// Send the flag to receive the message
		digitalWrite(interruptOutgoing, HIGH);
		delay(10);
		
        
        // * * * * * * * * * * * * * *
        // Check for the right messages
        // * * * * * * * * * * * * * *
        
		// Check if it's getting the message
		if(nextByte() == 'E') {
			// Show that we received the message
			
			if(debug) Serial << "Received the message" << endl;
			
            boolean alt = false;
            for(int i=0; i<5; i++) {
                moveRightWing(alt);
                alt = !alt;
                delay(50);
            }
			
		}
        
		
		delay(50);
		//digitalWrite(LED, LOW);
		digitalWrite(interruptOutgoing, LOW);
		triggerFlag = false;
        
		
	}
    
    boolean passive = false;
    
    //periodicSend();
    
    
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
        
    } else {
        if(millis()%500 == 0) {
            updateLights(true);
        }
    }
    
    //pirBehaviour(analogRead(pir));
    //ldrBehaviour(analogRead(ldrL), analogRead(ldrR));
    //peekABooBehaviour(analogRead(ldrL), analogRead(ldrR));
    //partyBehaviour();
     */
    
    
}

void trigger() {
	triggerFlag = true;
}

byte nextByte() {
	while(1) {
		if(Serial.available() > 0) {
			byte b = Serial1.read();
			//if(debug) Serial << "Received byte: " << b << endl;
            commAttemptCount = 0;
			return b;
		}
        
        
        if(commAttemptCount >= 100) {
			commAttemptCount = 0;
			break;
		}
		
		commAttemptCount++;
        
		//if(debug) Serial << "Waiting for next byte" << endl;
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
        
        ET.sendData();
        
    }
    
    digitalWrite(interruptOutgoing, LOW);
    triggerFlag = false;
    triggerAttemptCount = 0;
    
}

