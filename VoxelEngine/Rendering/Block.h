#pragma once
#include <vector>
#include "BlockType.h"

class Block
{
private:
	BlockType type;
	std::vector<float> frontFace;
};