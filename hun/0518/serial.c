#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringSerial.h>

char device[] = "/dev/ttyACM0";	//Uno
//char device[] = "/dev/ttyUSB0";	//ESP32
int fd;
unsigned long baud = 115200;
int main()
{
	printf("%s \n", "Raspberry Startup");
	fflush(stdout);
	if((fd = serialOpen(device, baud)) <  0 ) {
		fprintf(stderr, "Unable %s\n", strerror(errno));
		exit(1);
	}
	if(wiringPiSetup() == -1){
		return 1;
	}
	while (1)
	{
		if(serialDataAvail(fd))
		{
			char newChar = serialGetchar(fd);
			printf("%c", newChar);
			fflush(stdout);
		}
//		printf("\n");
	}
	return 0;
}
