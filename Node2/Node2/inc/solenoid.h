/*
 * solenoid.h
 *
 * Created: 01.11.2020 13:31:42
 *  Author: marth
 */ 


#ifndef SOLENOID_H_
#define SOLENOID_H_
 #include "adc.h"
 #include "sam.h"
 
 
 uint8_t solenoid_counter;
 // 0 when free, 1 when busy
 uint8_t solenoid_free_flag;
 
 void solenoid_init();

void solenoid_push();

void solenoid_contract();


#endif /* SOLENOID_H_ */