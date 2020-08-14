#include "Block.h"

//Contructor
Block::Block(BlockShapeIndex shape, bool isTransparent)
{
	this->shape = shape;
	this->isTransparent = isTransparent;
}
//Get the block's shape.
const BlockShape& Block::GetBlockShape() const
{
	return BlockShapes::shapes[shape];
}
//Static array that stores the block types.
const Block Block::blocks[] =
{
	//TestTransparent
	Block(BlockShapeIndex::Cube, true),
	//Dirt
	Block(BlockShapeIndex::Cube, false)
};
//Return whether or not the block is transparent.
const bool Block::GetTransparency() const
{
	return isTransparent;
}