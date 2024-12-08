/*
 * fsm_auto.c
 *
 *  Created on: Oct 24, 2024
 *      Author: Tupo_1310
 */

#include "fsm_auto.h"
#include "i2c-lcd.h"

int red_main, red_cross=0;
int yellow_main, yellow_cross=0;
int green_main, green_cross=0;
int ind=0;
int num_buf=0;

void fsm_auto_mode1_run(){
	switch(status){
	case INIT:

		HAL_GPIO_WritePin(led2_1_GPIO_Port, led2_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led2_2_GPIO_Port, led2_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led1_1_GPIO_Port, led1_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led1_2_GPIO_Port, led1_2_Pin, GPIO_PIN_RESET);

		red_main = red_dur/1000;
		red_cross = red_dur/1000;
		yellow_main = yellow_dur/1000;
		yellow_cross = yellow_dur/1000;
		green_main = green_dur/1000;
		green_cross = green_dur/1000;

		status = RED_GREEN;
		ind=0;
		setTimer1(green_dur);
		setTimer3(1000);
		setTimer4(1000);

		break;

	case RED_GREEN:
		HAL_GPIO_WritePin(led1_1_GPIO_Port, led1_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(led1_2_GPIO_Port, led1_2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(led2_1_GPIO_Port, led2_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(led2_2_GPIO_Port, led2_2_Pin, GPIO_PIN_RESET);

		if(timer1_flag ==1){
			status = RED_YELLOW;
			setTimer1(yellow_dur);
			ind = 0;
		}
		if(timer3_flag==1){
			char buffer_1[16];
			char buffer_2[16];

			lcd_goto_XY(1, 0);
			sprintf(buffer_1, "RED1:       %02d", red_main);
			lcd_send_string(buffer_1);

			 lcd_goto_XY(2, 0);
			sprintf(buffer_2, "GREEN2:     %02d", green_cross);
			lcd_send_string(buffer_2);
			setTimer3(1000);
		}
		if(timer4_flag==1){
			red_main--;
			green_cross--;
			setTimer4(1000);
		}
		if(isButton1Press() == 1) status = MODE2_BUFF;
		break;
	case RED_YELLOW:
		HAL_GPIO_WritePin(led1_1_GPIO_Port, led1_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(led1_2_GPIO_Port, led1_2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(led2_1_GPIO_Port, led2_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led2_2_GPIO_Port, led2_2_Pin, GPIO_PIN_SET);

		if(timer1_flag ==1){
			status = GREEN_RED;
			ind = 0;
			setTimer1(green_dur);
		}
		if(timer3_flag==1){
			char buffer_1[16];
			char buffer_2[16];

			lcd_goto_XY(1, 0);
			sprintf(buffer_1, "RED1:       %02d", red_main);
			lcd_send_string(buffer_1);

			 lcd_goto_XY(2, 0);
			sprintf(buffer_2, "YELLOW2:    %02d", yellow_cross);
			lcd_send_string(buffer_2);
			setTimer3(1000);
		}
		if(timer4_flag==1){
			red_main--;
			yellow_cross--;
			setTimer4(1000);
		}
		if(isButton1Press() == 1) status = MODE2_BUFF;
		break;

	case GREEN_RED:
		HAL_GPIO_WritePin(led1_1_GPIO_Port, led1_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(led1_2_GPIO_Port, led1_2_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(led2_1_GPIO_Port, led2_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(led2_2_GPIO_Port, led2_2_Pin, GPIO_PIN_SET);

		if(timer1_flag ==1){
			status = YELLOW_RED;
			ind = 0;
			setTimer1(yellow_dur);
			/*setTimer3(25);
			setTimer4(100);*/
		}
		if(timer3_flag==1){
			char buffer_1[16];
			char buffer_2[16];

			lcd_goto_XY(1, 0);
			sprintf(buffer_1, "GREEN1:     %02d", green_main);
			lcd_send_string(buffer_1);
			 lcd_goto_XY(2, 0);
			sprintf(buffer_2, "RED2:       %02d", red_cross);
			lcd_send_string(buffer_2);
			setTimer3(1000);
		}
		if(timer4_flag==1){
			green_main--;
			red_cross--;
			setTimer4(1000);
		}
		if(isButton1Press() == 1) status = MODE2_BUFF;
		break;
	case YELLOW_RED:
		HAL_GPIO_WritePin(led1_1_GPIO_Port, led1_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(led1_2_GPIO_Port, led1_2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(led2_1_GPIO_Port, led2_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(led2_2_GPIO_Port, led2_2_Pin, GPIO_PIN_SET);

		if(timer1_flag ==1){
			status = RED_GREEN;
			red_main = red_dur/1000;
			red_cross = red_dur/1000;
			yellow_main = yellow_dur/1000;
			yellow_cross = yellow_dur/1000;
			green_main = green_dur/1000;
			green_cross = green_dur/1000;
			setTimer1(green_dur);
			ind = 0;
		}
		if(timer3_flag==1){
			char buffer_1[16];
			char buffer_2[16];

			lcd_goto_XY(1, 0);
			sprintf(buffer_1, "YELLOW1:    %02d", yellow_main);
			lcd_send_string(buffer_1);
			 lcd_goto_XY(2, 0);
			sprintf(buffer_2, "RED2:       %02d", red_cross);
			lcd_send_string(buffer_2);
			setTimer3(1000);
		}
		if(timer4_flag==1){
			yellow_main--;
			red_cross--;
			setTimer4(1000);
		}
		if(isButton1Press() == 1) status = MODE2_BUFF;
	default:
		break;
	}
}
