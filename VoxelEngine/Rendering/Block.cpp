#include "Block.h"

Block::Block(BlockShapeIndex shape, bool isTransparent)
{
	this->shape = shape;
	this->isTransparent = isTransparent;
}

const BlockShape& Block::GetBlockShape() const
{
	return BlockShapes::shapes[shape];
}

const Block Block::blocks[] =
{
	//Dirt
	Block(BlockShapeIndex::Cube, true),
	Block(BlockShapeIndex::Cube, false)
};

const bool Block::GetTransparency() const
{
	return isTransparent;
}