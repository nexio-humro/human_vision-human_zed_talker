#ifndef MAIN_FUNCTIONS_HPP
#define MAIN_FUNCTIONS_HPP

#include <iostream>

#include "ros/ros.h"
#include <sl/Camera.hpp>

#include "human_vision_exchange/Objects.h"
#include "sensor_msgs/Image.h"

namespace MF
{
	void setInitParameters(sl::InitParameters& initParameters);
	void setObjectDetectionParameters(sl::ObjectDetectionParameters& obj_det_params);
	void setObjectDetectionRuntimeParameters(sl::ObjectDetectionRuntimeParameters& objectTracker_parameters_rt);
	bool initZedCamera(sl::Camera& zed);
	void prepareObjectsMsg(sl::Objects& objects, human_vision_exchange::Objects& objectsMsg);
}

#endif
