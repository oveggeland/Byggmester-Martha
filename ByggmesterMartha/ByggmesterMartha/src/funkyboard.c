/*
 * mmi.c
 *
 * Created: 09/09/2020 16:14:17
 *  Author: vemun
 */ 

#include "../inc/funkyboard.h"
#include "../inc/adc.h"
#include "../inc/can.h"

#define F_CPU	4915200
#include <util/delay.h>
#include <stdlib.h>

void init_joystick(){
	_delay_ms(1000);
	joystick_offset_x = 0;
	joystick_offset_y = 0;
	struct Joystick_pos joystick = get_joystick_pos();
	joystick_offset_x = joystick.x;
	joystick_offset_y = joystick.y;
}

struct Joystick_pos get_joystick_pos(){
	uint8_t adc_values[4];
	adc_get_values(&adc_values[0]);
	struct Joystick_pos joystick;

	joystick.x = (int16_t)(adc_values[0]) - joystick_offset_x;
	joystick.y = (int16_t)(adc_values[1]) - joystick_offset_y;
	return joystick;
}

enum Joystick_dir get_joystick_dir(){
	struct Joystick_pos joystick = get_joystick_pos();
	
	if ((abs(joystick.x) < 50) && (abs(joystick.y) < 50)){
		return NEUTRAL;
	}
	
	if (abs(joystick.y)>abs(joystick.x)){
		if (joystick.y < -35){
			return DOWN;
		}
		return UP;
	}
	
	if (joystick.x < -35){
		return LEFT;
	}
	return RIGHT;
	
	};

struct Slider_pos get_slider_pos(){
	uint8_t adc_values[4];
	rd_adc(&adc_values);
	struct Slider_pos slider;
	slider.right = (int) (((adc_values[2]-128)*100)/128);
	slider.left = (int) (((adc_values[3]-128)*100)/128);
	return slider;
	};
	
	
void send_button_press(){
	if ((PINB &= ( 1 << 3)) == ( 1 << 3)){
		struct can_msg button_msg;
		uint8_t pulse_length = 4;
		button_msg.ID = 52;
		button_msg.data[0] = 1;
		button_msg.data[1] = pulse_length;
		button_msg.len = 2;
		
		can_transmit_message(&button_msg);
	}
}	

int8_t wrap_and_filter(int16_t value){
	if (abs(value)<15){
		return 0;
	}
	else if(value < -128){
		return -128;
	}
	else if(value > 127){
		return 127;
	}
	
	return (int8_t) value;
}

// Sends joystick position over CAN bus
// Returns 0 for successful transmission
// 1 when failed. 
uint8_t joystick_transmit_position(){
	
	struct Joystick_pos js_pos = get_joystick_pos();
	struct can_msg js_msg;
	union Data data;
	
	js_msg.ID = 69;
	js_msg.len = 2;

	data.i = wrap_and_filter(js_pos.x);
	js_msg.data[0] = data.u;
	data.i = wrap_and_filter(js_pos.y);
	js_msg.data[1] = data.u;
	
	
	if(can_transmit_message(&js_msg) != 1){
		return 0;
	}
	return 1;
};	