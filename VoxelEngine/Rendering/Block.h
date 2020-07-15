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
	Block(BlockShapeIndex shape, bool isTransparent);
	const BlockShape& GetBlockShape();
	const bool GetTransparency();
};