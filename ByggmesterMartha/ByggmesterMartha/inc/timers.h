/*
 * timers.h
 *
 * Created: 23/09/2020 13:04:07
 *  Author: Vemund
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_


// Timer 1 is used for PWM output on PD5. It's the ADC clock
void timer1_init();
void timer0_init();


#endif /* TIMERS_H_ */