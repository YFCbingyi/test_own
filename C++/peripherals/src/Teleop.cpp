#include "ros/ros.h"
#include "std_msgs/String.h"

#include <iostream>
#include <cstdio>
#include <termio.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <sys/types.h>  
#include <fcntl.h>  
#include <errno.h>  
#include <time.h>  
#include <linux/input.h> 
#include <signal.h>

ros::Publisher teleop_pub;
struct input_event event;
struct sigaction act;
//int fd;

void pub_msg(int event_code) {
	event_code &= 0xff;
    
	std::string cmd;	
	if(event_code == 0x30)
		cmd = "ack";
	else if(event_code == 0x01)
		cmd = "ack";
	else if(event_code == 0x67)
		cmd = "up";
	else if(event_code == 0x6c)
		cmd = "down";
	else if(event_code == 0x69)
		cmd = "left";
	else if(event_code == 0x6a)
		cmd = "right";
	else if(event_code == 0x68)
		cmd = "pgup";
	else if(event_code == 0x6d)
		cmd = "pgdn";
	else 
		return;

	std_msgs::String msg;
	msg.data = cmd;
	ROS_INFO("%s", msg.data.c_str());
	teleop_pub.publish(msg);
}

void handler(int signo,siginfo_t *resdata,void *unknowp)
{
	printf("signo=%d\n",signo);
	printf("return data :%d\n",resdata->si_value.sival_int);

	//if(fd > 0 )
	//	close(fd);
	
	ros::shutdown();
}

void register_signal() {
	//初始化sa_mask
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handler;
	//一旦使用了sa_sigaction属性，那么必须设置sa_flags属性的值为SA_SIGINFO
	act.sa_flags = SA_SIGINFO;

	//注册信号
	sigaction(2,&act,NULL);
	sigaction(34,&act,NULL);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "teleop_node");
	ros::NodeHandle n;
	ros::NodeHandle pnh("~");

	std::string dev;
	pnh.getParam("/dev", dev);

	int fd = 0;
	if ((fd = open(dev.c_str(), O_RDWR, 0)) >= 0) {
		printf("%s: open, fd = %d\n", dev.c_str(), fd);
		for (int i = 0; i < LED_MAX; i++) {
			event.time.tv_sec = time(0);
			event.time.tv_usec = 0;
			event.type = EV_LED;
			event.code = i;
			event.value = 0;
			write(fd, &event, sizeof(event));
		} 
	} else {
		printf("dev %s: (%s)\n", dev.c_str(), strerror(errno));
		return 1;
	}

	register_signal();
	teleop_pub = pnh.advertise<std_msgs::String>("cmd", 1000);
	//ros::Rate loop_rate(10);

	unsigned char mask[EV_MAX / 8 + 1]; /* RATS: Use ok */
	int           rc;
	std::string tmp;

	while ((rc = read(fd, &event, sizeof(event))) > 0) {
		printf("%-24.24s.%06lu type 0x%04x; code 0x%04x;"
				" value 0x%08x; ",
				ctime(&event.time.tv_sec),
				event.time.tv_usec,
				event.type, event.code, event.value);
		switch (event.type) {
			case EV_KEY:
				if (event.code > BTN_MISC) {
					printf("Button %d %s",
							event.code & 0xff,
							event.value ? "press" : "release");
				}
				else {
					printf("Key %d (0x%x) %s",
							event.code & 0xff,
							event.code & 0xff,
							event.value ? "press" : "release");

					if(event.value == 1)
						pub_msg(event.code);
				}
				break;
			case EV_REL:
				switch (event.code) {
					case REL_X:      tmp = "X";       break;
					case REL_Y:      tmp = "Y";       break;
					case REL_HWHEEL: tmp = "HWHEEL";  break;
					case REL_DIAL:   tmp = "DIAL";    break;
					case REL_WHEEL:  tmp = "WHEEL";   break;
					case REL_MISC:   tmp = "MISC";    break;
					default:         tmp = "UNKNOWN"; break;
				}
				printf("Relative %s %d", tmp.c_str(), event.value);
				break;
			case EV_ABS:
				switch (event.code) {
					case ABS_X:        tmp = "X";        break;
					case ABS_Y:        tmp = "Y";        break;
					case ABS_Z:        tmp = "Z";        break;
					case ABS_RX:       tmp = "RX";       break;
					case ABS_RY:       tmp = "RY";       break;
					case ABS_RZ:       tmp = "RZ";       break;
					case ABS_THROTTLE: tmp = "THROTTLE"; break;
					case ABS_RUDDER:   tmp = "RUDDER";   break;
					case ABS_WHEEL:    tmp = "WHEEL";    break;
					case ABS_GAS:      tmp = "GAS";      break;
					case ABS_BRAKE:    tmp = "BRAKE";    break;
					case ABS_HAT0X:    tmp = "HAT0X";    break;
					case ABS_HAT0Y:    tmp = "HAT0Y";    break;
					case ABS_HAT1X:    tmp = "HAT1X";    break;
					case ABS_HAT1Y:    tmp = "HAT1Y";    break;
					case ABS_HAT2X:    tmp = "HAT2X";    break;
					case ABS_HAT2Y:    tmp = "HAT2Y";    break;
					case ABS_HAT3X:    tmp = "HAT3X";    break;
					case ABS_HAT3Y:    tmp = "HAT3Y";    break;
					case ABS_PRESSURE: tmp = "PRESSURE"; break;
					case ABS_DISTANCE: tmp = "DISTANCE"; break;
					case ABS_TILT_X:   tmp = "TILT_X";   break;
					case ABS_TILT_Y:   tmp = "TILT_Y";   break;
					case ABS_MISC:     tmp = "MISC";     break;
					default:           tmp = "UNKNOWN";  break;
				}
				printf("Absolute %s %d", tmp.c_str(), event.value);
				break;
			case EV_MSC: printf("Misc"); break;
			case EV_LED: printf("Led");  break;
			case EV_SND: printf("Snd");  break;
			case EV_REP: printf("Rep");  break;
			case EV_FF:  printf("FF");   break;
						 break;
		}
		printf("\n");
	}

	close(fd);
	return 0;
}



