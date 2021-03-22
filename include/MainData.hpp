#ifndef MAIN_DATA_HPP
#define MAIN_DATA_HPP

#include <iostream>

#include "ros/ros.h"
#include "human_vision_exchange/Objects.h"
#include "sensor_msgs/Image.h"

namespace MD
{
	const ros::Publisher* getObjectsPublisher();
	void setObjectsPublisher(ros::NodeHandle& node, std::string topicName);
	const ros::Publisher* getImagePublisher();
	void setImagePublisher(ros::NodeHandle& node, std::string topicName);
}

#endif
