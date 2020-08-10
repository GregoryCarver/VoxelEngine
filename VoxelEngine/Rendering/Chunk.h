#pragma once
#include <unordered_map>
#include "Block.h"

class Chunk
{
	static const unsigned char chunkDimension = 32;
	//Blocks of the chunk
	BlockIndex chunkBlocks[chunkDimension][chunkDimension][chunkDimension];
	//Mesh constructed from the blocks after face culling.:::Need to add greedy meshing.
	std::vector<float> chunkMesh;

	//Stores the current chunk the player is in. This keeps from needing each chunk to store its postion.
	static Chunk& currentChunk;

public:
	static const unsigned char renderDistance = 2;
	static Chunk loadedChunks[renderDistance][renderDistance][renderDistance];
	Chunk();
	std::vector<float>& GetChunkMesh();
	void BuildChunkMesh();
	void GenerateTestChunk();
	void GenerateRandomChunk(int chunkX, int chunkY, int chunkZ);
};