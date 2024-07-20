#include <Arduino.h>
#include "gyro.h"


void setup() {
  Serial.begin(9600);
  gyro_setup();
}

void loop() {
  Serial.println("loop");
  if(gyro_ready()){
    Serial.println(get_angle());
    Serial.println(get_angular_velocity());
  }
}

