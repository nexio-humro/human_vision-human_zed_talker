#ifndef ROS_TOPIC_HPP
#define ROS_TOPIC_HPP

#include <iostream>

#include "ros/ros.h"
#include "human_vision_exchange/FaceDescriptionVector.h"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <ZedData.hpp>

namespace RT
{	
	void grab_faceVectors(const human_vision_exchange::FaceDescriptionVector& faceDescriptionVector);
}

#endif
