#pragma once
#include <vector>
#include "BlockShapes.h"
//Enum so that blocks can be identified by name instead of integers.
enum BlockIndex
{
	TestTransparent = 0,
	Dirt = 1
};

class Block
{
private:
	//Block's shape.
	BlockShapeIndex shape;
	bool isTransparent;

public:
	//Array to store block types. Ex: dirt, sand, stone...
	static const Block blocks[2];
	Block(BlockShapeIndex shape, bool isTransparent);
	const BlockShape& GetBlockShape() const;
	const bool GetTransparency() const;
};