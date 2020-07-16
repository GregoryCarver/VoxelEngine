#include "Chunk.h"

void Chunk::BuildChunkMesh()
{
	for (int i = 1; i < chunkDimension - 1; i++)
	{
		for (int j = 1; j < chunkDimension - 1; j++)
		{
			for (int k = 1; k < chunkDimension - 1; k++)
			{
				if (!Block::blocks[chunkBlocks[i][j][k - 1]].GetTransparency())
				{
					for (float vertex : Block::blocks[chunkBlocks[i][j][k - 1]].GetBlockShape().GetFrontFace())
					{
						chunkMesh.push_back(vertex);
					}
				}
			}
		}
	}
}

//Generates a chunk of dirt to test the chunks.
void Chunk::GenerateTestChunk()
{
	for (int i = 0; i < chunkDimension; i++)
	{
		for (int j = 0; j < chunkDimension; j++)
		{
			for (int k = 0; k < chunkDimension; k++)
			{
				chunkBlocks[i][j][k] = BlockIndex::Dirt;
			}
		}
	}
}