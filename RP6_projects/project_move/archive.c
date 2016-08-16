#include"RP6RobotBaseLib.h"

#define CRUISE_SPEED_FWD 110
#define CRUISE_SPEED_BCKWD -100
#define NORMAL 0
#define ESCAPE 1
#define DODGE 2
#define TURNING_BACK 3

uint8_t state = NORMAL;
uint8_t escape_way = 0;

void bumpersStateChange(void)
{
	if(bumper_left || bumper_right)
	{
		state = ESCAPE;
		escape_way = bumper_left ? RIGHT : LEFT;
		moveAtSpeedDirection(CRUISE_SPEED_BCKWD,CRUISE_SPEED_BCKWD);
		startStopwatch1();
	}
}

void turn_after_bumper(void)
{
	if(state == ESCAPE && getStopwatch1() > 2500)
	{
		state = NORMAL;
		moveAtSpeedDirection(0,0);
		rotate(70,escape_way,180,1);
		setStopwatch1(0);
		stopStopwatch1();
	}
}

void go_forward(void)
{
	if(state == NORMAL)
		moveAtSpeedDirection(CRUISE_SPEED_FWD,CRUISE_SPEED_FWD);
}

void ACSStateChanged(void)
{
	if(state == ESCAPE || state == TURNING_BACK)
		return;
	// 	writeString("Left detector : ");
	// 	writeInteger(obstacle_left,2);
	// 	writeChar('\n');
	// 	writeString("Right detector : ");
	// 	writeInteger(obstacle_right,2);
	// 	writeChar('\n');
	// 	writeChar('\n');
	
	if(obstacle_left ^ obstacle_right)
	{
		state = DODGE;
		moveAtSpeedDirection(CRUISE_SPEED_FWD - 40*obstacle_right,CRUISE_SPEED_FWD - 40*obstacle_left);
	}
	else if(obstacle_left && obstacle_right)
	{
		state = TURNING_BACK;
		uint8_t rotate_dir = rand()%2 ? LEFT : RIGHT;
		moveAtSpeedDirection(0,0);
		rotate(90,rotate_dir,90,1);
	}
	else
		state = NORMAL;
}

void change_state()
{
	switch(state)
	{
		case NORMAL:
			
			break;
	}
}

void state_machine()
{
	switch(state)
	{
		case NORMAL:
			moveAtSpeedDirection(CRUISE_SPEED_FWD,CRUISE_SPEED_FWD);
			break;
			
		case ESCAPE:
			bumperStateChange();
			break;
			
		case DODGE:
			moveAtSpeedDirection(CRUISE_SPEED_FWD - 40*obstacle_right,CRUISE_SPEED_FWD - 40*obstacle_left);
			break;
			
		case TURNING_BACK:
			uint8_t rotate_dir = rand()%2 ? LEFT : RIGHT;
			moveAtSpeedDirection(0,0);
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
	BUMPERS_setStateChangedHandler(bumpersStateChange);
	ACS_setStateChangedHandler(ACSStateChanged);
	powerON();
	setACSPwrHigh();
	srand(0);
	
	while(1)
	{
		change_state();
		state_machine();
		
		// 		if(state == NORMAL)
		// 			go_forward();
		// 		else if(state == ESCAPE)
		// 			turn_after_bumper();
		
		task_RP6System();
	}
	
	return 0;
}