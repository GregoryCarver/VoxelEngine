#pragma once
#include "BlockShape.h"

//Stores the shapes of blocks using BlockType, and then Block along with the preconfigured BlockSahpes will be used to contruct blocks in their appropriate locations
//depending on where they are in their corresponding chunks.
enum BlockShapeIndex
{
	Cube = 0
};

class BlockShapes
{
public:
	static const BlockShape shapes[1];
};