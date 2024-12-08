/*
 * fsm_auto_set_run.c
 *
 *  Created on: Oct 26, 2024
 *      Author: Tupo_1310
 */

#include "fsm_auto_set_run.h"

int set_buff=0;
int num_buffer=0;
int red_set, gre_set, yel_set=0;
int index=0;

void fsm_auto_set_run(){
	switch(status){
	case MODE2_BUFF:
//		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);


		HAL_GPIO_WritePin(led1_1_GPIO_Port, led1_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led1_2_GPIO_Port, led1_2_Pin, GPIO_PIN_RESET);


		HAL_GPIO_WritePin(led2_1_GPIO_Port, led2_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led2_2_GPIO_Port, led2_2_Pin, GPIO_PIN_RESET);

		status = MODE2;
		setTimer2(500);
		setTimer3(1000);
		setTimer5(250);
		lcd_clear_display();
	case MODE2:
		if(timer2_flag==1){
			HAL_GPIO_TogglePin(led1_1_GPIO_Port, led1_1_Pin);
			HAL_GPIO_TogglePin(led1_2_GPIO_Port, led1_2_Pin);
			HAL_GPIO_TogglePin(led2_1_GPIO_Port, led2_1_Pin);
			HAL_GPIO_TogglePin(led2_2_GPIO_Port, led2_2_Pin);
			setTimer2(500);
		}
		if(timer5_flag==1){
			char buffer_1[16];

			lcd_goto_XY(1, 0);
			lcd_send_string("MODE2:    RED");
			 lcd_goto_XY(2, 0);
			sprintf(buffer_1, "DURATION: %02d", set_buff);
			lcd_send_string(buffer_1);
			setTimer5(100);
		}
		if(isButton1Press() == 1){
			HAL_GPIO_WritePin(led1_1_GPIO_Port, led1_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led1_2_GPIO_Port, led1_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led2_1_GPIO_Port, led2_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led2_2_GPIO_Port, led2_2_Pin, GPIO_PIN_RESET);
			set_buff=0;
			index=0;
			status = MODE3;
			lcd_clear_display();
		}
		if(isButton2Press() ==1){
			set_buff+=1;
		}
		if(isButton3Press() ==1){
			red_set = set_buff;
			set_buff = 0;
			lcd_clear_display();
		}
		break;
	case MODE3:
		if(timer2_flag==1){
			HAL_GPIO_TogglePin(led1_2_GPIO_Port, led1_2_Pin);
			HAL_GPIO_TogglePin(led2_2_GPIO_Port, led2_2_Pin);
			setTimer2(500);
		}
		if(timer5_flag==1){
			char buffer_1[16];

			lcd_goto_XY(1, 0);
			lcd_send_string("MODE2:    YELLOW");
			 lcd_goto_XY(2, 0);
			sprintf(buffer_1, "DURATION: %02d", set_buff);
			lcd_send_string(buffer_1);
			setTimer5(100);
		}
		if(isButton1Press() == 1){
			HAL_GPIO_WritePin(led1_1_GPIO_Port, led1_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led1_2_GPIO_Port, led1_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led2_1_GPIO_Port, led2_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led2_2_GPIO_Port, led2_2_Pin, GPIO_PIN_RESET);
			status = MODE4;
			set_buff=0;
			index=0;
			lcd_clear_display();
		}
		if(isButton2Press() ==1){
			set_buff+=1;
		}
		if(isButton3Press() ==1){
			yel_set = set_buff;
			set_buff = 0;
			lcd_clear_display();
		}
		break;
	case MODE4:
		if(timer2_flag==1){
			HAL_GPIO_TogglePin(led1_1_GPIO_Port, led1_1_Pin);
			HAL_GPIO_TogglePin(led2_1_GPIO_Port, led2_1_Pin);
			setTimer2(500);
		}
		if(timer5_flag==1){
			char buffer_1[16];

			lcd_goto_XY(1, 0);
			lcd_send_string("MODE2:    GREEN");
			 lcd_goto_XY(2, 0);
			sprintf(buffer_1, "DURATION: %02d", set_buff);
			lcd_send_string(buffer_1);
			setTimer5(100);
		}
		if(isButton1Press() == 1){
			if(red_set == gre_set + yel_set){
				red_dur = red_set*1000;
				yellow_dur = yel_set*1000;
				green_dur = gre_set * 1000;
			}
			HAL_GPIO_WritePin(led1_1_GPIO_Port, led1_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led1_1_GPIO_Port, led1_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led1_1_GPIO_Port, led2_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led1_1_GPIO_Port, led2_2_Pin, GPIO_PIN_RESET);
			status = INIT;
			set_buff=0;
			index=0;
			lcd_clear_display();
		}
		if(isButton2Press() ==1){
			set_buff+=1;
		}
		if(isButton3Press() ==1){
			gre_set = set_buff;
			set_buff = 0;
			lcd_clear_display();
		}
		break;
	default:
		break;
	}
}
