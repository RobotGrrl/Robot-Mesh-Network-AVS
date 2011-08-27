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

// Initialize
void setup() {
    
	if(debug) Serial << "MANOI Comm. beginning initialization" << endl;
    
	// Communication
	Serial.begin(9600);
    
	nssMANOI.begin(9600);
    //MNrx_ET.begin(details(MNdata_rx), &nssMANOI);
    //XB_ET.begin(details(XBdata), &Serial);
	
	// Interrupts
	pinMode(interruptOutgoing, OUTPUT);
	attachInterrupt(0, trigger, RISING);
    
    // Outputs
	pinMode(LED, OUTPUT);
	pinMode(STATUS, OUTPUT);
    
	if(debug) Serial << "Done init" << endl;
    
}

void loop() {
    fftProgram();
}

void fftProgram() {
    
    if(Serial.available() > 0) {
        char c = (char)Serial.read();
        if(c == 'S') nssMANOI.print(c); //sendMN(c);
        Serial.flush();
    }
    
    //digitalWrite(STATUS, !digitalRead(STATUS));
	//delay(50);
    
}

void trigger() {
	triggerFlag = true;
}


void sendMN(char c) {
    
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
        nssMANOI.print(c);
        
        if(debug) Serial << "Sending the message now" << endl;
        
        //digitalWrite(LED, HIGH);
        //delay(1000);
        //digitalWrite(LED, LOW);
        
        triggerFlag = false;
        
    }
    
    if(debug) Serial << "waiting..." << endl;
    //delay(3000);
    
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
        
        //if(MNrx_ET.receiveData()) {
        if(nssMANOI.available() >= 3) {
            
            if(debug) Serial << "it was available!" << endl;
            if(debug) Serial << nssMANOI.read() << endl;
            
            if((nssMANOI.read()-'0') == 1) { // TODO: Fix this
                
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
