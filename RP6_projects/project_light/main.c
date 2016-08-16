#include"RP6RobotBaseLib.h"

uint8_t state = 0;
uint8_t after_bumper_way = 0;

void bumpers_state_change(void)
{
	if(bumper_left || bumper_right)
	{
		state = 1;
		after_bumper_way = bumper_left;
		// 		moveAtSpeedDirection(0,0);
		// 		mSleep(50);
		moveAtSpeedDirection(-100,-100);
		startStopwatch1();
		stopStopwatch2();
	}
}

void follow_light(void)
{
	uint16_t light_l = adcLSL, light_r = adcLSR;
	uint16_t diff = light_l < light_r ? light_r - light_l : light_l - light_r;
// 	writeIntegerLength(light_l,DEC,4);
// 	writeChar('\n');
// 	writeIntegerLength(light_r,DEC,4);
// 	writeChar('\n');
// 	writeChar('\n');
	if(getStopwatch2() > 100)
	{
		if(diff > 100)
			moveAtSpeedDirection(50 + 70*(light_l < light_r),50 + 70*(light_l > light_r));
		else
			moveAtSpeedDirection(100,100);
		setStopwatch2(0);
	}
}

void turn_after_bumper(void)
{
	if(state == 1 && getStopwatch1() > 3000)
	{
		state = 2;
		moveAtSpeedDirection(0,0);
		mSleep(50);
		if(after_bumper_way)
			moveAtSpeedDirection(120,30);
		else
			moveAtSpeedDirection(30,120);
		setStopwatch1(0);
	}
}

void go_forward(void)
{
	if(state == 2 && getStopwatch1() > 2000)
	{
		state = 0;
		moveAtSpeedDirection(0,0);
		mSleep(50);
		moveAtSpeedDirection(60,60);
		stopStopwatch1();
		setStopwatch1(0);
		setStopwatch2(0);
		startStopwatch2();
	}
}

int main(void)
{
	initRobotBase();
	setLEDs(0b111111);
	mSleep(1500);
	setLEDs(0b100001);
	BUMPERS_setStateChangedHandler(bumpers_state_change);
	powerON(); 	
	changeDirection(FWD);
	moveAtSpeedDirection(100,100);
	startStopwatch2();
	
	while(1)
	{
		if(state == 0)
			follow_light();
		else if(state == 1)
			turn_after_bumper();
		else if(state == 2)
			go_forward();
		task_RP6System();
	}
	
	return 0;
}