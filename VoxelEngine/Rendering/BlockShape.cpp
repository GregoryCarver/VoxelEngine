#include "BlockShape.h"

BlockShape::BlockShape(std::vector<float> front, std::vector<float> left, std::vector<float> back, std::vector<float> right, std::vector<float> top, std::vector<float> bottom)
{
	/*posZFace = front;
	negXFace = left;
	negZFace = back;
	posXFace = right;
	posYFace = top;
	negYFace = bottom;*/
	faces.push_back(front);
	faces.push_back(left);
	faces.push_back(back);
	faces.push_back(right);
	faces.push_back(top);
	faces.push_back(bottom);
}

const std::vector<float>& BlockShape::GetFrontFace() const
{
	return faces[FaceIndex::Front];
}
const std::vector<float>& BlockShape::GetLeftFace() const
{
	return faces[FaceIndex::Left];
}
const std::vector<float>& BlockShape::GetBackFace() const
{
	return faces[FaceIndex::Back];
}
const std::vector<float>& BlockShape::GetRightFace() const
{
	return faces[FaceIndex::Right];
}
const std::vector<float>& BlockShape::GetTopFace() const
{
	return faces[FaceIndex::Top];
}
const std::vector<float>& BlockShape::GetBottomFace() const
{
	return faces[FaceIndex::Bottom];
}

const std::vector<std::vector<float>>& BlockShape::GetFaces() const 
{
	return faces;
}