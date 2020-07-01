#include "BlockType.h"

BlockType::BlockType(std::vector<float> front, std::vector<float> left, std::vector<float> back, std::vector<float> right, std::vector<float> top, std::vector<float> bottom)
{
	posZFace = front;
	negXFace = left;
	negZFace = back;
	posXFace = right;
	posYFace = top;
	negYFace = bottom;
}

std::vector<float>& BlockType::GetFrontFace()
{
	return posZFace;
}

std::vector<float>& BlockType::GetLeftFace()
{
	return negXFace;
}
std::vector<float>& BlockType::GetBackFace()
{
	return negZFace;
}
std::vector<float>& BlockType::GetRightFace()
{
	return posXFace;
}
std::vector<float>& BlockType::GetTopFace()
{
	return posYFace;
}
std::vector<float>& BlockType::GetBottomFace()
{
	return negYFace;
}