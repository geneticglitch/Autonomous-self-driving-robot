#include <Arduino.h>
#include "gyro.h"
#include "encoder.h"


void setup() {
  Serial.begin(9600);
  gyro_setup();
  encoder_setup();
}

void loop() {
  // if(gyro_ready()){
  //   Serial.println(get_angle());
  //   Serial.println(get_angular_velocity());
  // }
  // Serial.println(get_left_encoder_count());
  Serial.println(get_right_encoder_count());
}

