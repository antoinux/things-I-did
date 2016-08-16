#include"RP6RobotBaseLib.h"

int main(void)
{
	initRobotBase();
	setLEDs(0b111111);
	mSleep(1500);
	setLEDs(0b100001);
	powerON();
	
	while(1)
	{
// 		moveAtSpeedDirection(50,-50);
		rotate(40,LEFT,90,1);
		task_RP6System();
	}
	return 0;
}