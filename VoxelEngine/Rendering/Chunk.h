#pragma once
#include "Block.h"

class Chunk
{
	static const char chunkDimension = 32;
	unsigned int chunkBlocks[chunkDimension][chunkDimension][chunkDimension];
	std::vector<float> chunkMesh;

public:
	void BuildChunkMesh();
	void GenerateTestChunk();
};