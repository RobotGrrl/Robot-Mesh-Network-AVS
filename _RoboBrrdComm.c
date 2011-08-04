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

boolean debug = false;

// All the pins
int interruptOutgoing = 12;
int interruptIncoming = 0;
int ROBOBRRDrx = 7;
int ROBOBRRDtx = 8;
int LED = 5;
int STATUS = 4;

// NewSoftSerial
NewSoftSerial nssROBOBRRD(ROBOBRRDrx, ROBOBRRDtx);

// Trigger flag
volatile boolean triggerFlag = false;

// EasyTransfer
SoftEasyTransfer RBrx_ET;
//SoftEasyTransfer RBtx_ET;
//EasyTransfer XB_ET;

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
MESH_DATA RBdata_rx;
MESH_DATA XBdata;

int a(0);

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
    //XB_ET.begin(details(XBdata), &Serial);
    
	// Interrupts
	pinMode(interruptOutgoing, OUTPUT);
    digitalWrite(interruptOutgoing, LOW);
    
	attachInterrupt(interruptIncoming, trigger, RISING);
    digitalWrite(2, LOW);
    
    // Outputs
	pinMode(LED, OUTPUT);
	pinMode(STATUS, OUTPUT);
    
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    
    digitalWrite(STATUS, HIGH);
    delay(1000);
    digitalWrite(STATUS, LOW);
    
    delay(2000);
    
    if(debug) Serial << "Done setup" << endl;
    
}

void loop() {    
    
    if(Serial.available() > 0) {
        
        digitalWrite(STATUS, LOW);
        digitalWrite(LED, HIGH);
        
        //for(int i=0; i<4; i++) {
        
        // trollololol
        a = Serial.read();
        a = Serial.read();
        a = Serial.read();
        
        a = (int)a-'0';
        
        if(a == 2) {
            digitalWrite(STATUS, HIGH);
            delay(2000);
        }
        
        //}
        
        //while(rxIndex < 4) {
        //    rxBuffer[rxIndex] = Serial.read();
            
            //if((int)rxBuffer[rxIndex]-'0' == 2) {
            //    digitalWrite(STATUS, HIGH);
            //    delay(2000);
            //}
            
        //    rxIndex++;
        //}
        
        if(Serial.available() > 0) Serial.flush();
        
        delay(100);
        
        digitalWrite(LED, LOW);
        digitalWrite(STATUS, LOW);
        
    }
    
    digitalWrite(STATUS, !digitalRead(STATUS));
    delay(50);
    
    /*
    if(Serial.available() >= 3) {
        digitalWrite(STATUS, HIGH);
        XB_ET.receiveData();
        Serial.flush();
        delay(1000);
        digitalWrite(STATUS, LOW);
    }
    
    if(XBdata.robot == 2) {
        for(int i=0; i<6; i++) {
            digitalWrite(LED, !digitalRead(LED));
            delay(100);
        }
    }
    */
     
    //digitalWrite(STATUS, !digitalRead(STATUS));
    //delay(50);
    
    //sendRB();
	
}


// Trigger flag for the interrupt
// sent from RB's main board
void trigger() {
	triggerFlag = true;
}


// Sending data back to RoboBrrd
// For now, just using custom protocol
void sendRB() {
    
    int triggerAttemptsCount = 0;
    
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
}


// Reading the EasyTransfer data sent
// from RoboBrrd's main board
void readRB() {
    
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
