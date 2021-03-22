#include <sl/Camera.hpp>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <SystemFunctions.hpp>
#include <RosTopics.hpp>
#include <MainData.hpp>
#include <MainFunctions.hpp>
#include <SlCvConverter.hpp>

#include "ros/ros.h"
#include "ros/package.h"

int main(int argc, char **argv) 
{
	ros::init(argc, argv, "human_zed_talker");
	ros::NodeHandle node("/human_zed_talker/");

	MD::setObjectsPublisher(node, "objects");
	MD::setImagePublisher(node, "leftImage");
	
	sl::Camera zed;
	bool zedInit = MF::initZedCamera(zed);
	
	if(zedInit == false)
	{
		return 1;
	}

	// Configure object detection runtime parameters
    sl::ObjectDetectionRuntimeParameters objectTracker_parameters_rt;
    MF::setObjectDetectionRuntimeParameters(objectTracker_parameters_rt);

    // Create ZED Objects filled in the main loop
    sl::Objects objects;
    sl::Mat lImage;
	sensor_msgs::Image leftImageMsg;
	
	while (ros::ok())
	{
        // Grab images
        sl::ERROR_CODE zed_error = zed.grab();
        
        if (zed_error == sl::ERROR_CODE::SUCCESS) 
        {        
			// Retrieve left image
			zed.retrieveImage(lImage, sl::VIEW::LEFT, sl::MEM::CPU);
			
			// Prepare image message  
			SCC::imageToROSmsg(leftImageMsg, lImage, "leftImage", ros::Time::now());

			// Retrieve Objects
			zed.retrieveObjects(objects, objectTracker_parameters_rt);
			
			// Prepare Objects message
			human_vision_exchange::Objects objectsMsg;
			MF::prepareObjectsMsg(objects, objectsMsg);
			
			MD::getImagePublisher()->publish(leftImageMsg);	
			MD::getObjectsPublisher()->publish(objectsMsg);
		}
		
		ros::spinOnce();
	}
    
    return 0;
}
