#include "Chunk.h"

float*** Chunk::BuildChunkMesh()
{
	//Need to update for when there are other chunks, right now just clearing center.
	float*** chunkMesh;
	for (int i = 1; i < chunkDimension - 1; i++)
	{
		for (int j = 1; j < chunkDimension - 1; j++)
		{
			for (int k = 1; k < chunkDimension - 1; k++)
			{
				if (Block::blocks[chunkBlocks[i][j][k]].GetTransparency())
				{

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