
int accel_x_axis_home = 120;
int accel_y_axis_home = 115;
int accel_z_axis_home = 200;

int joy_x_axis_home = 125;
int joy_y_axis_home = 135;
int joy_x_axis_2_0 = 126;
int joy_y_axis_2_0 = 225;
int joy_x_axis_3_1 = 200;
int joy_y_axis_3_1 = 200;
int joy_x_axis_4_2 = 227;
int joy_y_axis_4_2 = 130;
int joy_x_axis_3_3 = 197;
int joy_y_axis_3_3 = 61;
int joy_x_axis_2_4 = 128;
int joy_y_axis_2_4 = 36;
int joy_x_axis_1_3 = 59;
int joy_y_axis_1_3 = 59;
int joy_x_axis_0_2 = 33;
int joy_y_axis_0_2 = 133;
int joy_x_axis_1_1 = 59;
int joy_y_axis_1_1 = 200;
int joy_threshold = 5;

void robotNunchuck() {
  
  if(z_button == 1) {
    slapShot(1, 80, 0);
  }
 
  if(joy_x_axis >= (joy_x_axis_home - 10) && joy_x_axis <= (joy_x_axis_home + 10) && 
     joy_y_axis >=  (joy_y_axis_home -10) && joy_y_axis <= (joy_y_axis_home + 10) &&
     c_button == 0 && z_button == 0) {
       // Home! (2,2)
       Serial << "Home (2,2) C:0 Z:0" << endl;
       ssc.setFrame(homeFrame, 500, 0);
  }
  
  if(joy_x_axis >= (joy_x_axis_2_0 - 10) && joy_x_axis <= (joy_x_axis_2_0 + 10) &&
     joy_y_axis >=  (joy_y_axis_2_0 -10) && joy_y_axis <= (joy_y_axis_2_0 + 10) &&
     c_button == 0 && z_button == 0) {
       // Top Middle (2,0)
       Serial << "Top Middle (2,0) C:0 Z:0" << endl;
       forward(1, 100, 10);
  }

  if(joy_x_axis >= (joy_x_axis_3_1 - 10) && joy_x_axis <= (joy_x_axis_3_1 + 10) &&
     joy_y_axis >=  (joy_y_axis_3_1 -10) && joy_y_axis <= (joy_y_axis_3_1 + 10) &&
     c_button == 0 && z_button == 0) {
     // Top Right (3,1)
      Serial << "Top Right (3,1) C:0 Z:0" << endl;
     
  }

  if(joy_x_axis >= (joy_x_axis_4_2 - 10) && joy_x_axis <= (joy_x_axis_4_2 + 10) && 
     joy_y_axis >=  (joy_y_axis_4_2 -10) && joy_y_axis <= (joy_y_axis_4_2 + 10) &&
     c_button == 0 && z_button == 0) {
     // Middle Right (4,2)
     Serial << "Middle Right (4,2) C:0 Z:0" << endl;
     right(1, 100, 10);
  }

  if(joy_x_axis >= (joy_x_axis_3_3 - 10) && joy_x_axis <= (joy_x_axis_3_3 + 10) && 
     joy_y_axis >=  (joy_y_axis_3_3 -10) && joy_y_axis <= (joy_y_axis_3_3 + 10) &&
     c_button == 0 && z_button == 0) {
     // Bottom Right (3,3)
     Serial << "Bottom Right (3,3) C:0 Z:0" << endl;
     
  }

  if(joy_x_axis >= (joy_x_axis_2_4 - 10) && joy_x_axis <= (joy_x_axis_2_4 + 10) && 
     joy_y_axis >=  (joy_y_axis_2_4 -10) && joy_y_axis <= (joy_y_axis_2_4 + 10) &&
     c_button == 0 && z_button == 0) {
     // Bottom Middle (2,4)
     Serial << "Bottom Middle (2,4) C:0 Z:0" << endl;
     backward(1, 100, 10);
  }

  if(joy_x_axis >= (joy_x_axis_1_3 - 10) && joy_x_axis <= (joy_x_axis_1_3 + 10) && 
     joy_y_axis >=  (joy_y_axis_1_3 -10) && joy_y_axis <= (joy_y_axis_1_3 + 10) &&
     c_button == 0 && z_button == 0) {
     // Bottom Left (1,3)
     Serial << "Bottom Left (1,3) C:0 Z:0" << endl; 
  }

  if(joy_x_axis >= (joy_x_axis_0_2 - 10) && joy_x_axis <= (joy_x_axis_0_2 + 10) && 
     joy_y_axis >=  (joy_y_axis_0_2 -10) && joy_y_axis <= (joy_y_axis_0_2 + 10) &&
     c_button == 0 && z_button == 0) {
     // Middle Left (0,2)
     Serial << "Middle Left (0,2) C:0 Z:0" << endl;
     left(1, 100, 10);
  }

  if(joy_x_axis >= (joy_x_axis_1_1 - 10) && joy_x_axis <= (joy_x_axis_1_1 + 10) && 
     joy_y_axis >=  (joy_y_axis_1_1 -10) && joy_y_axis <= (joy_y_axis_1_1 + 10) &&
     c_button == 0 && z_button == 0) {
     // Top Left (1,1)
     Serial << "Top Left (1,1) C:0 Z:0" << endl;
     
  }
  
  
  

 if(accel_x_axis >= (accel_x_axis_home - 10) && accel_x_axis <= (accel_x_axis_home + 10)) {
   if(accel_y_axis >= (accel_y_axis_home - 10) && accel_y_axis <= (accel_y_axis_home + 10)) {
    if(accel_z_axis >= (accel_z_axis_home - 10) && accel_z_axis <= (accel_z_axis_home + 10)) {
      if(c_button == 1) {
        // Home!
        Serial << "Home (2,2) C:1" << endl;
        ssc.setFrame(homeFrame, 500, 0);
     }
    }
   }
  }
  
  if(accel_x_axis >= (accel_x_axis_home - 55) && accel_x_axis <= (accel_x_axis_home - 35)) {
   if(accel_y_axis >= (accel_y_axis_home - 5) && accel_y_axis <= (accel_y_axis_home + 15)) {
    if(accel_z_axis >= (accel_z_axis_home - 40) && accel_z_axis <= (accel_z_axis_home - 20)) {
      if(c_button == 1) {
        // Left!
        //left();
     }
    }
   }
  }
  
  if(accel_x_axis >= (accel_x_axis_home + 45) && accel_x_axis <= (accel_x_axis_home + 65)) {
   if(accel_y_axis >= (accel_y_axis_home - 5) && accel_y_axis <= (accel_y_axis_home + 15)) {
    if(accel_z_axis >= (accel_z_axis_home + 20) && accel_z_axis <= (accel_z_axis_home + 40)) {
      if(c_button == 1) {
        // Right!
        //right();
     }
    }
   }
  }
  
  if(accel_x_axis >= (accel_x_axis_home + 5) && accel_x_axis <= (accel_x_axis_home + 25)) {
   if(accel_y_axis >= (accel_y_axis_home - 55) && accel_y_axis <= (accel_y_axis_home - 35)) {
    if(accel_z_axis >= (accel_z_axis_home - 25) && accel_z_axis <= (accel_z_axis_home - 5)) {
     if(c_button == 1) {
        // Front!
        //forward(1, 200);
     }
    }
   }
  }
  
  if(accel_x_axis >= (accel_x_axis_home - 5) && accel_x_axis <= (accel_x_axis_home + 15)) {
   if(accel_y_axis >= (accel_y_axis_home + 20) && accel_y_axis <= (accel_y_axis_home + 40)) {
    if(accel_z_axis >= (accel_z_axis_home - 15) && accel_z_axis <= (accel_z_axis_home - 5)) {
      if(c_button == 1) {
        // Back!
        //backward(1, 200);
     }
    }
   }
  }
  
}
