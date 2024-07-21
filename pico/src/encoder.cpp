#include <Arduino.h>

int left_encoder_pin = 15;
int right_encoder_pin = 14;
volatile int left_encoder_count = 0;
volatile int right_encoder_count = 0;

void encoder_left_isr(){
    left_encoder_count++;
    delay(3);
}

void encoder_right_isr(){
    right_encoder_count++;
    delay(3);
}

void encoder_reset(){
    left_encoder_count = 0;
    right_encoder_count = 0;
}

int get_left_encoder_count(){
    return left_encoder_count;
}

int get_right_encoder_count(){
    return right_encoder_count;
}

void encoder_setup(){
    pinMode(left_encoder_pin, INPUT);
    pinMode(right_encoder_pin, INPUT);

    attachInterrupt(digitalPinToInterrupt(left_encoder_pin), encoder_left_isr, RISING);
    attachInterrupt(digitalPinToInterrupt(right_encoder_pin), encoder_right_isr, RISING);
}
