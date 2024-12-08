/*
 * global.h
 *
 *  Created on: Oct 24, 2024
 *      Author: Tupo_1310
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "button.h"
#include "main.h"
#include <stdio.h>

#define INIT	1
#define RED_GREEN		2
#define RED_YELLOW	3
#define GREEN_RED 	4
#define YELLOW_RED	5

#define MODE2_BUFF 10
#define MODE2 	11
#define MODE3	12
#define MODE4	13

extern int status;

extern int green_dur;
extern int yellow_dur;
extern int red_dur;

#endif /* INC_GLOBAL_H_ */
