/*
 * timers.h
 *
 * Created: 21/10/2020 14:18:41
 *  Author: vemun
 */ 


#ifndef SERVO_H_
#define SERVO_H_

void servo_init_pwm();
void servo_set_position(uint8_t postition);
void servo_joystick_command(int8_t position);



#endif /* SERVO_H_ */