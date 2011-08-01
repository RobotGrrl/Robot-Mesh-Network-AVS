#pragma mark - Just some notes about everything!
July 27, 2011
robotgrrl.com

TODO:
check the manoi comm board functions to make sure 
they are the same updated version as in robobrrd

when asking if the ET received data, we should
probably try asking a few times... (but, doesnt
the library stick it in a while loop?)


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
