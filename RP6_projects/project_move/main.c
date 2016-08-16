#include"RP6RobotBaseLib.h"

#define CRUISE_SPEED_FWD 160
#define CRUISE_SPEED_BWD -100
#define NORMAL 0
#define ESCAPE 1
#define DODGE 2
#define TURNING_BACK 3

uint8_t state = NORMAL;
uint8_t escape_way = 0;
uint8_t last_rotation = 0;

void escapeState(void)
{
	move(CRUISE_SPEED_BWD,BWD,DIST_MM(100),1);
	rotate(90,LEFT,180,1);
}

void change_state(void)
{
	if(bumper_left || bumper_right)
	{
		state = ESCAPE;
		escape_way = bumper_left ? RIGHT : LEFT;
	}
	else if(obstacle_left && obstacle_right)
		state = TURNING_BACK;
	else if(obstacle_left || obstacle_right)
		state = DODGE;
	else
		state = NORMAL;
}

void state_machine(void)
{
	switch(state)
	{
		case NORMAL:
			moveAtSpeedDirection(CRUISE_SPEED_FWD,CRUISE_SPEED_FWD);
		break;
		
		case ESCAPE:
			escapeState();
		break;
		
		case DODGE:
			moveAtSpeedDirection(CRUISE_SPEED_FWD - 40*obstacle_right,CRUISE_SPEED_FWD - 40*obstacle_left);
		break;
		
		case TURNING_BACK:
			moveAtSpeedDirection(0,0);
			uint8_t rotate_dir;
			if(getStopwatch1() > 4000)
				rotate_dir = rand()%2 ? LEFT : RIGHT;
			else
				rotate_dir = last_rotation;
			last_rotation = rotate_dir;
			stopStopwatch1();
			setStopwatch1(0);
			startStopwatch1();
			rotate(90,rotate_dir,90,1);
		break;
	}
}

int main(void)
{
	initRobotBase();
	setLEDs(0b111111);
	mSleep(1500);
	setLEDs(0b100001);
	powerON();
	setACSPwrHigh();
// 	setACSPwrMed();
	setStopwatch1(0);
	srand(0);
	
	while(1)
	{
		change_state();
		state_machine();
		task_RP6System();
	}
	
	return 0;
}