#include "Chunk.h"

float*** Chunk::BuildChunkMesh()
{

}

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