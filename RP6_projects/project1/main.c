#include "RP6RobotBaseLib.h"

void loop(void)
{
	if(getStopwatch1() > 2000)
	{
		if(getStopwatch1() < 3000)
			setLEDs(0b000001);
		else if(getStopwatch1() < 3500)
			setLEDs(0b000011);
		else if(getStopwatch1() < 3750)
			setLEDs(0b000111);
		else if(getStopwatch1() < 3825)
			setLEDs(0b001111);
		else if(getStopwatch1() < 3912)
			setLEDs(0b011111);
		else if(getStopwatch1() < 4000)
			setLEDs(0b111111);
		else
		{
			setLEDs(0b000000);
			setStopwatch1(0);
		}
	}
}

int main(void)
{
	initRobotBase();
	writeString_P("Hello, world!");
	
	setLEDs(0b000000);
	startStopwatch1();
	
	while(1)
	{
		loop();
	}
	
	return 0;
}