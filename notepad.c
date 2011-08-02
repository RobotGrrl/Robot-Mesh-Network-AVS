#pragma mark - Just some notes about everything!
July 27, 2011
robotgrrl.com

TODO:

tomorrow add in the xbee communication

instead of Serial.available() > 0, try == 4?



#pragma mark - Connections

::RoboBrrd::

Main<->Comm: 
Serial1 (with switches (cause it used to be a standard arduino))
<->
NSS (RX: 7, TX: 8)

Comm<->XB: Serial (with switches)

::MANOI::
Main<->Comm:
Serial1 (no switches)
<->
NSS (RX: 5, TX: 4)

Comm<->XB: Serial (with big black switches)


#pragma mark - EasyTransfer Universal Message Packet

struct INTER_DATA {
    
    int action;
    int param_1;
    int param_2;
    int param_3;
    int param_4;
    int param_5;
    
};

action- whatever
parameters- whatever (maybe sync the LEDs? lolz)

attention int [-1, 1]
valence int [-1, 1]
stance int [-1, 1]

action_t int [1, x)
action_t0 int [1, x)

robot int [1, x)

sense_1 int [1, x)
sense_2 int [1, x)
sense_3 int [1, x)
sense_4 int [1, x)
sense_5 int [1, x)

world_L int [1, x)
world_R int [1, x)
world_F int [1, x)

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



