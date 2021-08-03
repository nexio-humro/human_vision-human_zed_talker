#include "MainFunctions.hpp"

namespace MF
{
	void setInitParameters(sl::InitParameters& initParameters)
	{
		initParameters.depth_mode = sl::DEPTH_MODE::PERFORMANCE;
		initParameters.coordinate_system = sl::COORDINATE_SYSTEM::RIGHT_HANDED_Y_UP;
		initParameters.coordinate_units = sl::UNIT::METER;
		initParameters.depth_maximum_distance = 15.f;
		initParameters.camera_image_flip = sl::FLIP_MODE::AUTO; // 3.2 and ZED2 --> detect automatically the flip mode
		initParameters.camera_resolution = sl::RESOLUTION::HD1080;
//		initParameters.camera_resolution = sl::RESOLUTION::HD720;
		initParameters.camera_fps = 30;
	}
	
	void setObjectDetectionParameters(sl::ObjectDetectionParameters& obj_det_params)
	{
		obj_det_params.image_sync = true;
		obj_det_params.enable_tracking = true;
		obj_det_params.enable_mask_output = false;
		obj_det_params.detection_model = sl::DETECTION_MODEL::HUMAN_BODY_FAST;
	}
	
	void setObjectDetectionRuntimeParameters(sl::ObjectDetectionRuntimeParameters& objectTracker_parameters_rt)
	{
		objectTracker_parameters_rt.detection_confidence_threshold = 50;
		objectTracker_parameters_rt.object_class_filter.clear();
		objectTracker_parameters_rt.object_class_filter.push_back(sl::OBJECT_CLASS::PERSON);
	}
	
	bool initZedCamera(sl::Camera& zed)
	{
		bool result = true;
		
		// Configure init parameters
		sl::InitParameters initParameters;
		MF::setInitParameters(initParameters);
		
		sl::ERROR_CODE zed_error = zed.open(initParameters);
		if (zed_error != sl::ERROR_CODE::SUCCESS) 
		{
			std::cout << sl::toVerbose(zed_error) << "\nExit program during opening camera." << std::endl;
			zed.close();
			result = false; 
		}
		
		sl::PositionalTrackingParameters trc_params;
		zed_error = zed.enablePositionalTracking(trc_params);
		if (zed_error != sl::ERROR_CODE::SUCCESS) {
			std::cout << sl::toVerbose(zed_error) << "\nExit program during enabling tracking." << std::endl;
			zed.close();
			result = false;
		}
		
		// Enable the Objects detection module
		sl::ObjectDetectionParameters obj_det_params;
		MF::setObjectDetectionParameters(obj_det_params);

		zed_error = zed.enableObjectDetection(obj_det_params);
		if (zed_error != sl::ERROR_CODE::SUCCESS) 
		{
			std::cout << sl::toVerbose(zed_error) << "\nExit program." << std::endl;
			zed.close();
			result = false;
		}
		
		return result;
	}
	
	void prepareObjectsMsg(sl::Objects& objects, human_vision_exchange::Objects& objectsMsg)
	{
		objectsMsg.objects.resize(objects.object_list.size());

		std_msgs::Header header;
		header.stamp = ros::Time::now();

		for (size_t i = 0; i < objects.object_list.size(); i++) 
		{
			sl::ObjectData data = objects.object_list[i];

			objectsMsg.objects[i].header = header;

			objectsMsg.objects[i].label_id = data.id;
			
            objectsMsg.objects[i].position.x = data.position.x;
            objectsMsg.objects[i].position.y = data.position.y;
            objectsMsg.objects[i].position.z = data.position.z;
			
			for (size_t j = 0; j < data.keypoint_2d.size(); j++)
			{
				objectsMsg.objects[i].keypoint_2d[j].x = data.keypoint_2d[j].x;
				objectsMsg.objects[i].keypoint_2d[j].y = data.keypoint_2d[j].y;
			}
			
			for (size_t j = 0; j < data.keypoint.size(); j++)
			{
				objectsMsg.objects[i].keypoint_3d[j].x = data.keypoint[j].x;
				objectsMsg.objects[i].keypoint_3d[j].y = data.keypoint[j].y;
				objectsMsg.objects[i].keypoint_3d[j].z = data.keypoint[j].z;
			}
			
			objectsMsg.objects[i].tracking_state = static_cast<int>(data.tracking_state);
		}
	}
}

