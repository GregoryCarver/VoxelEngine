#pragma once
#include "BlockType.h"

//Stores the types of blocks using BlockType, and then Block along with the preconfigured BlockTypes will be used to contruct blocks in their appropriate locations
//depending on where they are in their corresponding chunks.
class BlockTypes
{
public:
	static const BlockType cube;
};