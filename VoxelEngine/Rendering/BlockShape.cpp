#include "BlockShape.h"

BlockShape::BlockShape(std::vector<float> front, std::vector<float> left, std::vector<float> back, std::vector<float> right, std::vector<float> top, std::vector<float> bottom)
{
	posZFace = front;
	negXFace = left;
	negZFace = back;
	posXFace = right;
	posYFace = top;
	negYFace = bottom;
}

const std::vector<float>& BlockShape::GetFrontFace() const
{
	return posZFace;
}
const std::vector<float>& BlockShape::GetLeftFace() const
{
	return negXFace;
}
const std::vector<float>& BlockShape::GetBackFace() const
{
	return negZFace;
}
const std::vector<float>& BlockShape::GetRightFace() const
{
	return posXFace;
}
const std::vector<float>& BlockShape::GetTopFace() const
{
	return posYFace;
}
const std::vector<float>& BlockShape::GetBottomFace() const
{
	return negYFace;
}