#pragma once
#include <vector>
#include "BlockShapes.h"

enum BlockIndex
{
	Dirt = 0
};

class Block
{
private:
	BlockShapeIndex shape;
	bool isTransparent;

public:
	static const Block blocks[1];
	Block(BlockShapeIndex shape);
	const BlockShape& GetBlockShape();
	bool GetTransparency();
};