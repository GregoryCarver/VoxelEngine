#pragma once
#include <unordered_map>
#include "Block.h"
#include "../OpenGL/IRenderable.h"

class Chunk : IRenderable
{
	//How many blocks wide each chunk is.
	static const unsigned char chunkDimension = 32;
	//Blocks of the chunk
	BlockIndex chunkBlocks[chunkDimension][chunkDimension][chunkDimension];
	//Mesh constructed from the blocks after face culling.:::Need to add greedy meshing.
	std::vector<float> chunkMesh;


public:
	//How far chunks are rendered USED FOR TESTING///////
	static const unsigned char renderDistance = 2;
	//USED FOR TESTING
	static Chunk loadedChunks[renderDistance][renderDistance][renderDistance];
	Chunk(int chunkX, int chunkY, int chunkZ);
	std::vector<float>& GetChunkMesh();
	void BuildChunkMesh(int chunkX, int chunkY, int chunkZ);
	void GenerateTestChunk();
	void GenerateRandomChunk(int chunkX, int chunkY, int chunkZ);
	void DrawChunk();
};