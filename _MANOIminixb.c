/*
 * MANOIminixb.c
 * For the best hockey playing humanoid robot!
 * Utilizing the Robot Mesh Network AVS
 *
 * July 29, 2011
 * RobotGrrl.com
 */

//#include <Time.h>
#include <NewSoftSerial.h>
#include <Streaming.h>
#include <SoftEasyTransfer.h>
#include <EasyTransfer.h>

boolean debug = false;

// All the pins
int interruptOutgoing = 7;
int interruptIncoming = 2;
int MANOIrx = 5;
int MANOItx = 4;
int LED = 3; // led is the blue one
int STATUS = 6; // status is the green one

// NewSoftSerial
NewSoftSerial nssMANOI(MANOIrx, MANOItx);

// Trigger flag
volatile boolean triggerFlag = false;

// EasyTransfer
SoftEasyTransfer MNrx_ET;
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
MESH_DATA MNdata_rx;
MESH_DATA XBdata;

// Initialize
void setup() {
    
	if(debug) Serial << "MANOI Comm. beginning initialization" << endl;
    
	// Communication
	Serial.begin(9600);
    
	nssMANOI.begin(9600);
    MNrx_ET.begin(details(MNdata_rx), &nssMANOI);
    //XB_ET.begin(details(XBdata), &Serial);
	
	// Interrupts
	pinMode(interruptOutgoing, OUTPUT);
	attachInterrupt(0, trigger, RISING);
    
    // Outputs
	pinMode(LED, OUTPUT);
	pinMode(STATUS, OUTPUT);
    
    digitalWrite(LED, HIGH);
    digitalWrite(STATUS, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    digitalWrite(STATUS, LOW);
    
    delay(2000);
    
	if(debug) Serial << "Done init" << endl;
    
}

void loop() {
    
    digitalWrite(LED, HIGH);
    //XB_ET.sendData();
    Serial.print("~R2!");
    delay(5000);
    digitalWrite(LED, LOW);
    
    delay(100);
    
    //digitalWrite(STATUS, !digitalRead(STATUS));
    
    //sendMN();
    
    //readMN();
        
    //}
    
    
}

void trigger() {
	triggerFlag = true;
}


void sendMN() {
    
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
            triggerAttemptsCount = 0;
            break;
        }
        
        triggerAttemptsCount++;
        
    }
    
    if(triggerFlag) {
        
        digitalWrite(LED, LOW);
        delay(5);
        
        // Sending the message now
        nssMANOI.print("~A1!");
        
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

void readMN() {
    
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
                
            }
            // else {
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
    
}
