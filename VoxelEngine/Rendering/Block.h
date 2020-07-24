#pragma once
#include <vector>
#include "BlockShapes.h"

enum BlockIndex
{
	TestTransparent = 0,
	Dirt = 1
};

class Block
{
private:
	BlockShapeIndex shape;
	bool isTransparent;

public:
	static const Block blocks[2];
	Block(BlockShapeIndex shape, bool isTransparent);
	const BlockShape& GetBlockShape() const;
	const bool GetTransparency() const;
};