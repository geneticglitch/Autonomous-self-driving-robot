#ifndef gyro_h

void gyro_setup();
bool gyro_ready();
float get_angle(bool skew = false);
float get_angular_velocity();

#endif