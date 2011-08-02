/*
 * RoboBrrdComm.c
 * For the RoboBrrd robot!
 * Utilizing the Robot Mesh Network AVS
 *
 * July 27, 2011
 * RobotGrrl.com 
 */

#include <Time.h>
#include <NewSoftSerial.h>
#include <Streaming.h>
#include <SoftEasyTransfer.h>
#include <EasyTransfer.h>

boolean debug = true;

// All the pins
int interruptOutgoing = 12;
int interruptIncoming = 0;
int ROBOBRRDrx = 7;
int ROBOBRRDtx = 8;
int LED = 5;
int STATUS = 4;
int robobrrdNSSAttempts = 0;
int triggerAttemptsCount = 0;

// NewSoftSerial
NewSoftSerial nssROBOBRRD(ROBOBRRDrx, ROBOBRRDtx);

// Trigger flag
volatile boolean triggerFlag = false;

// Outstanding communication flag
boolean outstandingComm = false;

char msg[141];

// LED Pins
int redL(1), greenL(2), blueL(3);
int redR(4), greenR(5), blueR(6);

// LED Values
int preLR(0), preLG(0), preLB(0), preRR(0), preRG(0), preRB(0);
int LR, LG, LB, RR, RG, RB;

// Speaker
int spkr(3);
int length = 5; // the number of notes
char notes[] = "d d  "; // a space represents a rest
int tempo = 300;
char music[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F' };

int flagPin = 11;


// EasyTransfer
SoftEasyTransfer RBrx_ET;
//SoftEasyTransfer RBtx_ET;
EasyTransfer XB_ET;

struct MESH_DATA {
    //put your variable definitions here for the data you want to receive
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

struct INTER_DATA {
  
    int action;
    int param_1;
    int param_2;
    int param_3;
    int param_4;
    int param_5;
    
};

//give a name to the group of data
MESH_DATA RBdata_rx;
INTER_DATA RBdata_tx;
MESH_DATA XBdata;


// Initialize
void setup() {
	
	// Communication
	Serial.begin(9600);      // XB
    if(debug) Serial << "Beginning setup" << endl;
	nssROBOBRRD.begin(9600); // RB
    RBrx_ET.begin(details(RBdata_rx), &nssROBOBRRD);
    // for some reason it can't do this... 
    // we'll send raw data w/just delims for now
    //RBtx_ET.begin(details(RBdata_tx), &nssROBOBRRD);
    XB_ET.begin(details(XBdata), &Serial);
    
	// Interrupts
	pinMode(interruptOutgoing, OUTPUT);
    digitalWrite(interruptOutgoing, LOW);
    
	attachInterrupt(interruptIncoming, trigger, RISING);
    digitalWrite(2, LOW);
    
    pinMode(flagPin, INPUT);
    
    // Outputs
	pinMode(LED, OUTPUT);
	pinMode(STATUS, OUTPUT);
    
    pinMode(spkr, OUTPUT);
    
    // ET Data
    RBdata_tx.action = 1;
    RBdata_tx.param_1 = 0;
    RBdata_tx.param_2 = 0;
    RBdata_tx.param_3 = 0;
    RBdata_tx.param_4 = 0;
    RBdata_tx.param_5 = 0;
    
    RBdata_rx.attention = 0;
    RBdata_rx.valence = 0;
    RBdata_rx.stance = 0;
    
    RBdata_rx.action_t = 0;
    RBdata_rx.action_t0 = 0;
    
    RBdata_rx.robot = 0;
    
    RBdata_rx.sense_1 = 0;
    RBdata_rx.sense_2 = 0;
    RBdata_rx.sense_3 = 0;
    RBdata_rx.sense_4 = 0;
    RBdata_rx.sense_5 = 0;
    
    RBdata_rx.world_L = 0;
    RBdata_rx.world_R = 0;
    RBdata_rx.world_F = 0;
    
    
    XBdata.attention = 0;
    XBdata.valence = 0;
    XBdata.stance = 0;
    
    XBdata.action_t = 0;
    XBdata.action_t0 = 0;
    
    XBdata.robot = 0;
    
    XBdata.sense_1 = 0;
    XBdata.sense_2 = 0;
    XBdata.sense_3 = 0;
    XBdata.sense_4 = 0;
    XBdata.sense_5 = 0;
    
    XBdata.world_L = 0;
    XBdata.world_R = 0;
    XBdata.world_F = 0;
    
    
    digitalWrite(LED, LOW);
    digitalWrite(STATUS, LOW);
    
    delay(2000);
    
    if(debug) Serial << "Done setup" << endl;
    
}

void loop() {    
    
    // Send out the interrupt
    digitalWrite(interruptOutgoing, HIGH);
    delay(10);
    digitalWrite(interruptOutgoing, LOW);
    
    while(!triggerFlag) {
        
        digitalWrite(LED, !digitalRead(LED));
        delay(50);
        
        // Waiting for trigger to send the data
        if(debug) Serial << "Waiting for the trigger" << endl;
        
        if(triggerAttemptsCount >= 100) {
            triggerAttemptsCount = 0;
            break;
        }
        
        triggerAttemptsCount++;
        
    }
    
    if(triggerFlag) {
        
        digitalWrite(LED, LOW);
        delay(5);
        
        // Sending the message now
        nssROBOBRRD.print("~A1!");
        
        if(debug) Serial << "Sending the message now" << endl;
        
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        
        triggerFlag = false;
        
    }
    
    
    digitalWrite(STATUS, !digitalRead(STATUS));
	delay(50);
    
    if(debug) Serial << "waiting..." << endl;
    if(debug) Serial.println("howdy");
    delay(3000);
    
    /*
    
    // * * * * * * * * * * * * * * *
    // Check for messages from Xbee
    // * * * * * * * * * * * * * * *
    
	if(nextXB() == 'E') {
		
		digitalWrite(STATUS, LOW);
        delay(1000);
		
		if(debug) Serial << "Byte is E" << endl;
        
		// Send out the interrupt
		digitalWrite(interruptOutgoing, HIGH);
		outstandingComm = true;
		delay(500);
		digitalWrite(interruptOutgoing, LOW);
		
		while(!triggerFlag) {
            
            digitalWrite(LED, !digitalRead(LED));
            delay(50);
            
			// Waiting for trigger to send the data
			if(debug) Serial << "Waiting for the trigger" << endl;
			
			if(triggerAttemptsCount >= 100) {
				triggerAttemptsCount = 0;
				break;
			}
			
			triggerAttemptsCount++;
			
		}
		
		if(triggerFlag) {
            
            digitalWrite(LED, LOW);
            delay(50);
			
			// Sending the message now
			nssROBOBRRD.print("E");
			
			if(debug) Serial << "Sending the message now" << endl;
			
			outstandingComm = false;
			
			digitalWrite(LED, HIGH);
			delay(1000);
			digitalWrite(LED, LOW);
			
			triggerFlag = false;
			
		} else {
            digitalWrite(LED, LOW);
        }
		 
         
	}
     
     */
	
}


// Testing
void testReceive() {
    
    if(triggerFlag) {
        
        Serial << "trigger flag!" << endl;
        
        // Send out the interrupt
        digitalWrite(LED, HIGH);
        digitalWrite(STATUS, LOW);
		digitalWrite(interruptOutgoing, HIGH);
        
        if(RBrx_ET.receiveData()) {
            //if(nssROBOBRRD.available() >= 3) {
            
            if(RBdata_rx.attention == 1) {
                
                if(debug) Serial << "it was available" << endl;
                
                for(int i=0; i<10; i++) {
                    digitalWrite(LED, !digitalRead(LED));
                    digitalWrite(STATUS, !digitalRead(STATUS));
                    delay(100);
                }
                digitalWrite(LED, HIGH);
                
            }
            
        } else {
            
            if(debug) Serial << "it was not available" << endl;
            
            delay(2000);
            
            triggerFlag = false;
            digitalWrite(LED, LOW);   
        }
        
        if(debug) Serial << "done" << endl;
        
        triggerFlag = false;
        digitalWrite(LED, LOW); 
		digitalWrite(interruptOutgoing, LOW);
        
    }
    
}



void trigger() {
	triggerFlag = true;
}

byte nextXB() {
	
	if(debug) Serial << "Waiting for a byte from XBee" << endl;
    
	while(1) {
		
		if(Serial.available() > 0) {
			byte b = Serial.read();
			if(debug) Serial << b << endl;
			return b;
		}
		
		if(triggerFlag) {
			
			digitalWrite(STATUS, LOW);
			
			int letter = 0;
			
			// Empty the message buffer
			for(int i=0; i<141; i++) {
				msg[i] = ' ';
			}
			
			// We are ready to receive the message
			digitalWrite(interruptOutgoing, HIGH);
			delay(50);
			digitalWrite(interruptOutgoing, LOW);
			
			digitalWrite(LED, HIGH);
			
			// Reading the message
			byte b = nextROBOBRRD();
			while(b != '*') {
				msg[letter] = b;
				letter++;
				b = nextROBOBRRD();
			}
			
			// Parse the message
			if(msg[0] == 'E') {
				
                // * * * * * * * * * * * * * * * * * * * *
                // Do something when received from RoboBrrd
                // * * * * * * * * * * * * * * * * * * * *
                
				// Do something
				if(debug) Serial << "Received message OK" << endl;
				
                digitalWrite(LED, HIGH);
				delay(1000);
				digitalWrite(LED, LOW);
				delay(1000);
				digitalWrite(LED, HIGH);
				delay(1000);
				
			}
            
            // --- P
            if(msg[0] == 'P') {
                Serial << "P";
                
                if(digitalRead(flagPin) == HIGH) {
                    digitalWrite(LED, HIGH);
                    delay(100);
                    randomChirp();
                    digitalWrite(LED, LOW);
                }
                
            }
            
            // --- L
            if(msg[0] == 'L') {
                Serial << "L";
            }
            
            // --- R
            if(msg[0] == 'R') {
                Serial << "R";
            }
			
			digitalWrite(LED, LOW);
			triggerFlag = false;
			
		} else {
		
		/*
		 For some reaon this doesn't work on the 3.3V Arduino Pro Mini 168
		if(millis()%50 == 0) {
			digitalWrite(STATUS, !digitalRead(STATUS));
		}
		 */
		
		if(millis()%50 == 0) {
			digitalWrite(STATUS, !digitalRead(STATUS));
			delay(1);
         }
            
            
        }
        
		
        // * * * * * * * * * * * * * * 
        // Do something in the meantime
        // * * * * * * * * * * * * * *

        /*
        //if(millis()%500 == 0) {

         LR = int(random(0, 256));
         LG = int(random(0, 256));
         LB = int(random(0, 256));
         RR = int(random(0, 256));
         RG = int(random(0, 256));
         RB = int(random(0, 256));
         
         fade ( preLR, preLG, preLB,
         LR, LG, LB,
         preLR, preLG, preLB,
         LR, LG, LB,
         1 );
         
         //Serial << "From: " << preLR << "," << preLG << "," << preLB << "!" << endl;
         //Serial << "To: " << LR << "," << LG << "," << LB << "!" << endl;
         
         preLR = LR;
         preLG = LG;
         preLB = LB;
         preRR = RR;
         preRG = RG;
         preRB = RB;
            
            delay(500);
            
        //}
         */
        
	}
}

void randomChirp() {
    for(int i=0; i<10; i++) {
        playTone((int)random(100,800), (int)random(50, 200));
    }
}

byte nextROBOBRRD() {
	
	if(debug) Serial << "Waiting for a byte from MANOI" << endl;
	
	while(1) {
		
		if(nssROBOBRRD.available()) {
			byte b = nssROBOBRRD.read();
			if(debug) Serial << b << endl;
			return b;
		}
	
        if(millis()%50 == 0) {
			digitalWrite(LED, !digitalRead(LED));
			delay(1);
        }
        
		if(robobrrdNSSAttempts >= 100) {
			robobrrdNSSAttempts = 0;
			break;
		}
		
		robobrrdNSSAttempts++;
		
	}
	
}

void playTone(int tone, int duration) {
	
	for (long i = 0; i < duration * 1000L; i += tone * 2) {
		digitalWrite(spkr, HIGH);
		delayMicroseconds(tone);
		digitalWrite(spkr, LOW);
		delayMicroseconds(tone);
	}
	
}