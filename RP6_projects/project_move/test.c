#include "RP6RobotBaseLib.h"

int main(void)
{
	initRobotBase();
	setLEDs(0b111111);
	mSleep(1500);
	powerON();
	
	while(true)
	{
		rotate(50,LEFT,45,1);
		writeString_P("Done.\n");
		task_RP6System();
	}
	return 0;
}
