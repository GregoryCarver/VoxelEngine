#include "Block.h"

Block::Block(BlockShapeIndex shape, bool isTransparent)
{
	this->shape = shape;
	this->isTransparent = isTransparent;
}

const BlockShape& Block::GetBlockShape()
{
	return BlockShapes::shapes[shape];
}

const Block blocks[] =
{
	//Dirt
	Block(BlockShapeIndex::Cube, false),
};

const bool Block::GetTransparency()
{
	return isTransparent;
}