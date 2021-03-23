#include <RosTopics.hpp>

namespace RT
{
	void grab_faceVectors(const human_vision_exchange::FaceDescriptionVector& faceDescriptionVector)
	{
		std::vector<std::vector<double>> result;
		
		for(size_t i = 0; i < faceDescriptionVector.faces.size(); i++)
		{
			std::vector<double> faceVector;
			faceVector.resize( faceDescriptionVector.faces[i].points.size() );
			
			for(size_t j = 0; j < faceDescriptionVector.faces[i].points.size(); j++)
			{
				faceVector.at(j) = faceDescriptionVector.faces[i].points[j];
			}
			
			result.push_back(faceVector);
		}
		
		ZD::saveFaceDescriptionVector(result);
	}
}
