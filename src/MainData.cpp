#include <MainData.hpp>

namespace
{
	ros::Publisher objectsPublisher;
	ros::Publisher imagePublisher;
}

namespace MD
{
	const ros::Publisher* getObjectsPublisher()
	{
		return &objectsPublisher;
	}
	
	void setObjectsPublisher(ros::NodeHandle& node, std::string topicName)
	{
		objectsPublisher = node.advertise<human_vision_exchange::Objects>(topicName.c_str(), 10);
	}
	
	const ros::Publisher* getImagePublisher()
	{
		return &imagePublisher;
	}
	
	void setImagePublisher(ros::NodeHandle& node, std::string topicName)
	{
		imagePublisher = node.advertise<sensor_msgs::Image>(topicName.c_str(), 10);
	}
}
