#ifndef SL_CV_CONVERTER_HPP
#define SL_CV_CONVERTER_HPP

#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>
#include <sl/Camera.hpp>
#include "sensor_msgs/Image.h"
#include "sensor_msgs/image_encodings.h"

namespace SCC
{
	cv::Mat slMat2cvMat(sl::Mat& input);
	void imageToROSmsg(sensor_msgs::Image& imgMsgPtr, sl::Mat img, std::string frameId, ros::Time t);
}

#endif
