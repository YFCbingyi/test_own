#ifndef _TELEOP_CTRL_H_
#define _TELEOP_CTRL_H_

#include "peripherals/ITeleop.h"
#include <utils/rs_log.h>
#include <ros/ros.h>
#include <std_msgs/String.h>

class ITeleop;
class TeleopCtrl {
	public:
		TeleopCtrl(ITeleop* actor);
		~TeleopCtrl();

		void enable();
		void disable();

	private:
		void operate_cb(const std_msgs::String::ConstPtr &msg);

	private:
		ros::NodeHandle nh_;
		ros::NodeHandle pnh_;
		ros::Subscriber operate_sub_;
		ITeleop* actor_;
};

TeleopCtrl::TeleopCtrl(ITeleop* actor) : pnh_("~"), actor_(actor) {
}

TeleopCtrl::~TeleopCtrl() {
	disable();
	actor_ = nullptr;
}

void TeleopCtrl::enable() {
	std::cout << "teleop enabled, register callback function" << std::endl;
	operate_sub_ = nh_.subscribe("/teleop_node/cmd", 10, &TeleopCtrl::operate_cb, this);
}

void TeleopCtrl::disable() {
	std::cout << "teleop disabled, unregister callback function" << std::endl;
	operate_sub_.shutdown();
}

void TeleopCtrl::operate_cb(const std_msgs::String::ConstPtr &msg) {
	logsi("TeleopCtrl::received operate cmd: " << msg->data);
	actor_->operate(msg->data);
}
#endif
