#pragma once
#include <vector>

class BlockType
{
	//Faces of the shape			//Facing the shape looking towards negative Z
	std::vector<float> posZFace;	//front
	std::vector<float> negXFace;	//left
	std::vector<float> negZFace;	//back
	std::vector<float> posXFace;	//right
	std::vector<float> posYFace;	//top
	std::vector<float> negYFace;	//bottom
	
public:
	BlockType(std::vector<float> front, std::vector<float> left, std::vector<float> back, std::vector<float> right, std::vector<float> top, std::vector<float> bottom);
	std::vector<float>& GetFrontFace();
	std::vector<float>& GetLeftFace();
	std::vector<float>& GetBackFace();
	std::vector<float>& GetRightFace();
	std::vector<float>& GetTopFace();
	std::vector<float>& GetBottomFace();
};