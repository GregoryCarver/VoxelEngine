#pragma once
#include "Block.h"

class Chunk
{
	static const char chunkDimension = 32;
	unsigned int chunkBlocks[chunkDimension][chunkDimension][chunkDimension];

public:
	float*** BuildChunkMesh();
	void GenerateTestChunk();
};