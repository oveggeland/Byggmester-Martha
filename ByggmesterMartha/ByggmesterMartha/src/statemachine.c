/*
 * statemachine.c
 *
 * Created: 26/09/2020 13:44:03
 *  Author: 
 */ 

#include <stdio.h>

#include "../inc/statemachine.h"
#include "../inc/menu.h"
#include "../inc/game.h"
#include "../inc/can.h"
#include "../inc/funkyboard.h"
#include "../inc/oled.h"


void init_statemachine(){
	current_state = HOME_MENU;
}

void enter_home_menu(){
	current_state = HOME_MENU;
	
	//struct Joystick_pos js_pos_ref = set_joystick_pos(0,0);
	//joystick_transmit_position(js_pos_ref);
	
	//struct Slider_pos slider_pos_ref = set_slider_pos(0, 0);
	//slider_can(slider_pos_ref);
	
	menu_home();
	
	current_selection = 3;
	menu_upper_bound = 3;
	menu_lower_bound = 5;
}

void enter_highscore_menu(){
	current_state = HIGHSCORE;

	menu_highscores();

	current_selection = 5;
	menu_lower_bound = 5;
	menu_upper_bound = 5;
}

void enter_game_over(uint16_t score){
	current_state = GAME_OVER;
	menu_game_over(score);
	
	current_selection = 5;
	menu_lower_bound = 5;
	menu_upper_bound = 5;
}

void enter_play_game(){
	menu_play_game();
	current_state = PLAY_GAME;
	
}

void enter_initializing(){
	current_state = INITIALIZING;
}


void statemachine_handle_menu_execute(){
	switch(current_state){
		case HOME_MENU:
			switch(current_selection){
				case 3: {
					struct can_msg init_regulator_msg;
					init_regulator_msg.ID = 138;
					init_regulator_msg.len = 1;
					init_regulator_msg.data[0] = 1;
				
					can_transmit_message(&init_regulator_msg);
					oled_clear();
					enter_initializing();
					//enter_play_game();
				}
					break;
				case 4:
					enter_highscore_menu();
					break;
			}
			break;

		case HIGHSCORE:
			switch(current_selection){
				default:
					enter_home_menu();
					break;
			}
			break;
		case GAME_OVER:
			switch(current_selection){
				default:
					enter_home_menu();
					break;
			}
			break;
		case PLAY_GAME:
			switch(current_selection){
				default:
				current_selection = 8;
				break;
			}
			break;
		default:
			break;
	}
}


void statemachine_execute_current_state(){
	switch(current_state){
		case HOME_MENU:
			menu_draw((char*)&home_menu[0]);
			menu_navigate();
			break;

		case HIGHSCORE:
			menu_draw((char*)&hs_menu[0]);
			menu_navigate();
			break;
			
		case GAME_OVER:
			menu_draw((char*)&go_menu[0]);
			menu_navigate();
			break;
			
		case PLAY_GAME:
			menu_draw((char*)&pg_menu[0]);
			break;
		
		case INITIALIZING:
			oled_print_string(" INITIALIZING", 4);
			break;
	}
}