#include"RP6RobotBaseLib.h"

#define NORMAL 0
#define ESCAPE 1

uint8_t state = NORMAL;
uint8_t after_bumper_way = 0;

void bumpers_state_change(void)
{
	if(bumper_left || bumper_right)
	{
		state = ESCAPE;
		after_bumper_way = bumper_left ? RIGHT : LEFT;
		moveAtSpeedDirection(-100,-100);
		startStopwatch1();
	}
}

void turn_after_bumper()
{
	if(state == ESCAPE && getStopwatch1() > 3000)
	{
		state = NORMAL;
		moveAtSpeedDirection(0,0);
		rotate(50,after_bumper_way,45,1);
		setStopwatch1(0);
		stopStopwatch1();
	}
}

void go_forward()
{
	if(state == NORMAL)
		moveAtSpeedDirection(100,100);
}

int main(void)
{
	initRobotBase();
	setLEDs(0b111111);
	mSleep(1500);
	setLEDs(0b100001);
	BUMPERS_setStateChangedHandler(bumpers_state_change);
	powerON();
	
	while(1)
	{
		if(state == NORMAL)
			go_forward();
		else if(state == ESCAPE)
			turn_after_bumper();
		task_RP6System();
	}
	
	return 0;
}