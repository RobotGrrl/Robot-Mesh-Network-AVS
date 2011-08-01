/*
 *  MANOIminixb.c
 *  
 *
 *  Created by Erin Kennedy on 10-11-24.
 *  Copyright 2010 robotgrrl.com. All rights reserved.
 *
 */

#include <Time.h>
#include <NewSoftSerial.h>
#include <Streaming.h>
#include <SoftEasyTransfer.h>
#include <EasyTransfer.h>

boolean debug = true;

// All the pins
int interruptOutgoing = 7;
int interruptIncoming = 2;
int MANOIrx = 5;
int MANOItx = 4;
int LED = 3;
int STATUS = 6;
int manoiNSSAttempts = 0;
int triggerAttemptsCount = 0;

// NewSoftSerial
NewSoftSerial nssMANOI(MANOIrx, MANOItx);

// Trigger flag
volatile boolean triggerFlag = false;

// Outstanding communication flag
boolean outstandingComm = false;

char msg[141];


// EasyTransfer
SoftEasyTransfer MNrx_ET;
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

//give a name to the group of data
MESH_DATA MNdata_rx;
MESH_DATA XBdata;

// Initialize
void setup() {
    
	if(debug) Serial << "MANOI Comm. beginning initialization" << endl;
	
	// Communication
	Serial.begin(9600);
	nssMANOI.begin(9600);
    MNrx_ET.begin(details(MNdata_rx), &nssMANOI);
    XB_ET.begin(details(XBdata), &Serial);
	
	// Outputs
	pinMode(LED, OUTPUT);
	pinMode(STATUS, OUTPUT);
	
	// Interrupts
	pinMode(interruptOutgoing, OUTPUT);
	attachInterrupt(0, trigger, RISING);
	
    // ET Data
    MNdata_rx.attention = 0;
    MNdata_rx.valence = 0;
    MNdata_rx.stance = 0;
    
    MNdata_rx.action_t = 0;
    MNdata_rx.action_t0 = 0;
    
    MNdata_rx.robot = 0;
    
    MNdata_rx.sense_1 = 0;
    MNdata_rx.sense_2 = 0;
    MNdata_rx.sense_3 = 0;
    MNdata_rx.sense_4 = 0;
    MNdata_rx.sense_5 = 0;
    
    MNdata_rx.world_L = 0;
    MNdata_rx.world_R = 0;
    MNdata_rx.world_F = 0;
    
    
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
    
	if(debug) Serial << "Done init" << endl;
	
}

void loop() {
	
    if(debug) Serial << "wee!" << endl;
    
    if(triggerFlag) {
        
        Serial << "trigger flag!" << endl;
        
        // Send out the interrupt
        digitalWrite(LED, HIGH);
        digitalWrite(STATUS, LOW);
		digitalWrite(interruptOutgoing, HIGH);
        delay(100);
        
        if(MNrx_ET.receiveData()) {
        //if(nssMANOI.available() >= 3) {
            
            if(debug) Serial << "it was available!" << endl;
            if(debug) Serial << nssMANOI.read() << endl;
            
            if(MNdata_rx.attention == 1) {
                
                if(debug) Serial << "attention was 1!" << endl;
                
                for(int i=0; i<10; i++) {
                    digitalWrite(LED, !digitalRead(LED));
                    digitalWrite(STATUS, !digitalRead(STATUS));
                    delay(100);
                }
                digitalWrite(LED, HIGH);
                
            }// else {
             //   if(debug) Serial << "attention was not 1!" << endl;
            //} // why does adding an else here make it not work? WTF!
            
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
    
    digitalWrite(STATUS, !digitalRead(STATUS));
	delay(50);
    
    /*
    byte msgXB = nextXB();
    
    // --- E
	if(msgXB == 'E') {
		
		digitalWrite(STATUS, LOW);
		
		if(debug) Serial << "Byte is E" << endl;
		
		// Send out the interrupt
		digitalWrite(interruptOutgoing, HIGH);
		outstandingComm = true;
		delay(50);
		digitalWrite(interruptOutgoing, LOW);
		
		while(!triggerFlag) {
			
			// Waiting for trigger to send the data
			if(debug) Serial << "Waiting for the trigger" << endl;
			digitalWrite(LED, HIGH);
			delay(50);
			digitalWrite(LED, LOW);
			delay(50);
			
			if(triggerAttemptsCount >= 100) {
				triggerAttemptsCount = 0;
				break;
			}
			
			triggerAttemptsCount++;
			
		}
		
		if(triggerFlag) {
			
			// Sending the message now
			nssMANOI.print("E");
			
			if(debug) Serial << "Sending the message now" << endl;
			
			outstandingComm = false;
			
			digitalWrite(LED, HIGH);
			delay(1000);
			digitalWrite(LED, LOW);
			
			triggerFlag = false;
			
		}
		
	}
    
    if(msgXB == 'P') {
        relayMessage('P');
    }
    
    if(msgXB == 'L') {
        relayMessage('L');
    }
    
    if(msgXB == 'R') {
        relayMessage('R');
    }
    */
     
    /*
    byte c = 'P';
	// --- P
    if(msgXB == 'P' || msgXB == 'L' || msgXB == 'R') {
        relayMessage(c);
	}
     */
     
    
}

void relayMessage(byte c) {
    
    digitalWrite(STATUS, LOW);
    
    if(debug) Serial << "Byte is P" << endl;
    
    // Send out the interrupt
    digitalWrite(interruptOutgoing, HIGH);
    outstandingComm = true;
    delay(50);
    digitalWrite(interruptOutgoing, LOW);
    
    while(!triggerFlag) {
        
        // Waiting for trigger to send the data
        if(debug) Serial << "Waiting for the trigger" << endl;
        digitalWrite(LED, HIGH);
        delay(50);
        digitalWrite(LED, LOW);
        delay(50);
        
        if(triggerAttemptsCount >= 100) {
            triggerAttemptsCount = 0;
            break;
        }
        
        triggerAttemptsCount++;
        
    }
    
    if(triggerFlag) {
        
        // Sending the message now
        nssMANOI.print(c);
        
        if(debug) Serial << "Sending the message now" << endl;
        
        outstandingComm = false;
        
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        
        triggerFlag = false;
        
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
			byte b = nextMANOI();
			while(b != '*') {
				msg[letter] = b;
				letter++;
				b = nextMANOI();
			}
			
			// Parse the message
			if(msg[0] == 'E') {
				
				// Do something
				if(debug) Serial << "Received message OK" << endl;
				
				digitalWrite(LED, LOW);
				delay(1000);
				digitalWrite(LED, HIGH);
				delay(1000);
				
			}
			
			digitalWrite(LED, LOW);
			triggerFlag = false;
			
		}
		
		/*
		 For some reaon this doesn't work on the 3.3V Arduino Pro Mini 168
         if(millis()%50 == 0) {
         digitalWrite(STATUS, !digitalRead(STATUS));
         }
		 */
		
		if(millis()%50 == 0) {
			digitalWrite(STATUS, !digitalRead(STATUS));
			delay(5);
		}
        
	}
}

byte nextMANOI() {
	
	if(debug) Serial << "Waiting for a byte from MANOI" << endl;
	
	while(1) {
		
		if(nssMANOI.available()) {
			byte b = nssMANOI.read();
			if(debug) Serial << b << endl;
			return b;
		}
		
		if(manoiNSSAttempts >= 100) {
			manoiNSSAttempts = 0;
			break;
		}
		
		manoiNSSAttempts++;
		
	}
	
}


