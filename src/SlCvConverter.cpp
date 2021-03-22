#include <SlCvConverter.hpp>

namespace SCC
{
	cv::Mat slMat2cvMat(sl::Mat& input) 
	{
		// Mapping between MAT_TYPE and CV_TYPE
		int cv_type = -1;
		switch (input.getDataType()) {
			case sl::MAT_TYPE::F32_C1: cv_type = CV_32FC1; break;
			case sl::MAT_TYPE::F32_C2: cv_type = CV_32FC2; break;
			case sl::MAT_TYPE::F32_C3: cv_type = CV_32FC3; break;
			case sl::MAT_TYPE::F32_C4: cv_type = CV_32FC4; break;
			case sl::MAT_TYPE::U8_C1: cv_type = CV_8UC1; break;
			case sl::MAT_TYPE::U8_C2: cv_type = CV_8UC2; break;
			case sl::MAT_TYPE::U8_C3: cv_type = CV_8UC3; break;
			case sl::MAT_TYPE::U8_C4: cv_type = CV_8UC4; break;
			default: break;
		}

		// Since cv::Mat data requires a uchar* pointer, we get the uchar1 pointer from sl::Mat (getPtr<T>())
		// cv::Mat and sl::Mat will share a single memory structure
		
		if(input.getMemoryType() == sl::MEM::CPU)
		{
			return cv::Mat(input.getHeight(), input.getWidth(), cv_type, input.getPtr<sl::uchar1>(sl::MEM::CPU));
		}
		else
		{
			return cv::Mat(input.getHeight(), input.getWidth(), cv_type, input.getPtr<sl::uchar1>(sl::MEM::GPU));
		}
	}
	
	void imageToROSmsg(sensor_msgs::Image& imgMsgPtr, sl::Mat img, std::string frameId, ros::Time t)
	{
        imgMsgPtr.header.stamp = t;
        imgMsgPtr.header.frame_id = frameId;
        imgMsgPtr.height = img.getHeight();
        imgMsgPtr.width = img.getWidth();

        int num = 1; // for endianness detection
        imgMsgPtr.is_bigendian = !(*(char*)&num == 1);

        imgMsgPtr.step = img.getStepBytes();

        size_t size = imgMsgPtr.step * imgMsgPtr.height;
        imgMsgPtr.data.resize(size);

        sl::MAT_TYPE dataType = img.getDataType();

        switch (dataType) {
        case sl::MAT_TYPE::F32_C1: /**< float 1 channel.*/
            imgMsgPtr.encoding = sensor_msgs::image_encodings::TYPE_32FC1;
            memcpy((char*)(&imgMsgPtr.data[0]), img.getPtr<sl::float1>(), size);
            break;

        case sl::MAT_TYPE::F32_C2: /**< float 2 channels.*/
            imgMsgPtr.encoding = sensor_msgs::image_encodings::TYPE_32FC2;
            memcpy((char*)(&imgMsgPtr.data[0]), img.getPtr<sl::float2>(), size);
            break;

        case sl::MAT_TYPE::F32_C3: /**< float 3 channels.*/
            imgMsgPtr.encoding = sensor_msgs::image_encodings::TYPE_32FC3;
            memcpy((char*)(&imgMsgPtr.data[0]), img.getPtr<sl::float3>(), size);
            break;

        case sl::MAT_TYPE::F32_C4: /**< float 4 channels.*/
            imgMsgPtr.encoding = sensor_msgs::image_encodings::TYPE_32FC4;
            memcpy((char*)(&imgMsgPtr.data[0]), img.getPtr<sl::float4>(), size);
            break;

        case sl::MAT_TYPE::U8_C1: /**< unsigned char 1 channel.*/
            imgMsgPtr.encoding = sensor_msgs::image_encodings::MONO8;
            memcpy((char*)(&imgMsgPtr.data[0]), img.getPtr<sl::uchar1>(), size);
            break;

        case sl::MAT_TYPE::U8_C2: /**< unsigned char 2 channels.*/
            imgMsgPtr.encoding = sensor_msgs::image_encodings::TYPE_8UC2;
            memcpy((char*)(&imgMsgPtr.data[0]), img.getPtr<sl::uchar2>(), size);
            break;

        case sl::MAT_TYPE::U8_C3: /**< unsigned char 3 channels.*/
            imgMsgPtr.encoding = sensor_msgs::image_encodings::BGR8;
            memcpy((char*)(&imgMsgPtr.data[0]), img.getPtr<sl::uchar3>(), size);
            break;

        case sl::MAT_TYPE::U8_C4: /**< unsigned char 4 channels.*/
            imgMsgPtr.encoding = sensor_msgs::image_encodings::BGRA8;
            memcpy((char*)(&imgMsgPtr.data[0]), img.getPtr<sl::uchar4>(), size);
            break;
        }
    }
}
