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

int a(0);

// Initialize
void setup() {
	
	// Communication
	Serial.begin(9600);      // XB
    if(debug) Serial << "Beginning setup" << endl;
	nssROBOBRRD.begin(9600); // RB
    //RBrx_ET.begin(details(RBdata_rx), &nssROBOBRRD);
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
    
    if(debug) Serial << "Done setup" << endl;
    
}

void loop() {    
    adkProgram();
}

void adkProgram() {
    if(Serial.available() > 0) {
        char c = (char)Serial.read();
        nssROBOBRRD.print(c);
        Serial.flush();
    }
}

void fftProgram() {
    
    if(Serial.available() > 0) {
        char c = (char)Serial.read();
        if(c == 'K') nssROBOBRRD.print(c); //sendRB(c);
        Serial.flush();
    }
    
}

// Trigger flag for the interrupt
// sent from RB's main board
void trigger() {
	triggerFlag = true;
}


// Sending data back to RoboBrrd
// For now, just using custom protocol
void sendRB(char c) {
    
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
        nssROBOBRRD.print(c);
        
        if(debug) Serial << "Sending the message now" << endl;
        
        //digitalWrite(LED, HIGH);
        //delay(1000);
        //digitalWrite(LED, LOW);
        
        triggerFlag = false;
        
    }
    
    if(debug) Serial << "waiting..." << endl;
    //delay(3000);
}

/*
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
*/
