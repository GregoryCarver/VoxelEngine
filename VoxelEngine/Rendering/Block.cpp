#include "Block.h"

Block::Block(BlockShapeIndex shape)
{
	this->shape = shape;
}

const BlockShape& Block::GetBlockShape()
{
	return BlockShapes::shapes[shape];
}

const Block blocks[] =
{
	Block(BlockShapeIndex::Cube)
};

bool Block::GetTransparency()
{
	return isTransparent;
}