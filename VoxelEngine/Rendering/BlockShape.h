#pragma once
#include <vector>

class BlockShape
{
	//Faces of the shape			//Facing the shape looking towards negative Z
	std::vector<float> posZFace;	//front
	std::vector<float> negXFace;	//left
	std::vector<float> negZFace;	//back
	std::vector<float> posXFace;	//right
	std::vector<float> posYFace;	//top
	std::vector<float> negYFace;	//bottom
	
public:
	BlockShape(std::vector<float> front, std::vector<float> left, std::vector<float> back, std::vector<float> right, std::vector<float> top, std::vector<float> bottom);
	const std::vector<float>& GetFrontFace() const;
	const std::vector<float>& GetLeftFace() const;
	const std::vector<float>& GetBackFace() const;
	const std::vector<float>& GetRightFace() const;
	const std::vector<float>& GetTopFace() const;
	const std::vector<float>& GetBottomFace() const;
};