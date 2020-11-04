//regulator.c

#include "../inc/regulator.h"
#include "../inc/motor.h"
#include "sam3x4c.h"
#include <stdint.h>
#include <stdlib.h>

#define K_i 1
#define K_p 5
//current encoder, 32 bit, global
int16_t current_encoder = 69; // ;)) 

void regulator_set_ref(uint8_t position){
	position_ref = position;
}

void TC0_Handler(){
	uint32_t dummy = REG_TC0_SR0;
	update_motor_input();
}

void update_motor_input(){
		
	int16_t pos_error = position_ref - current_encoder;
	int16_t input = K_p*pos_error + K_i*integrated_error;

	uint8_t dir = 0;
	if (input < 0){
		dir = -1;
	}
	
	uint16_t power = abs(input);
	power = power >> 4; //Er dette t�ys?
	
	motor_set_output(dir, power);

	integrated_error = pos_error/50; //Dette tull?
}