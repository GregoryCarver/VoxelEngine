#pragma once
#include <unordered_map>
#include "Block.h"

class Chunk
{
	static const unsigned char chunkDimension = 32;
	static const unsigned char renderDistance = 5;
	//Blocks of the chunk
	BlockIndex chunkBlocks[chunkDimension][chunkDimension][chunkDimension];
	//Mesh constructed from the blocks after face culling.:::Need to add greedy meshing.
	std::vector<float> chunkMesh;

	//Stores chunks, with the chunk as the key, and the value is their position.
	static Chunk loadedChunks[renderDistance][renderDistance][renderDistance];
	//Stores the current chunk the player is in. This keeps from needing each chunk to store its postion.
	static Chunk& currentChunk;

public:
	//Chunk(int x, int y, int z);
	std::vector<float>& GetChunkMesh();
	void BuildChunkMesh();
	void GenerateTestChunk();
	void GenerateRandomChunk();
};