#include <iostream>
#include "Chunk.h"
#include "../Libraries/FastNoise/FastNoiseSIMD.h"

Chunk Chunk::loadedChunks[Chunk::renderDistance][Chunk::renderDistance][Chunk::renderDistance];

//Chunk::Chunk(int x, int y, int z)
//{
//	//chunks[{x, y, z}] = *this;
//	//currentChunk = chunks[Position(0, 0, 0)];
//	for (int i = 0; i < renderDistance; i++)
//	{
//		for (int j = 0; j < renderDistance; j++)
//		{
//			for (int k = 0; k < renderDistance; k++)
//			{
//				//loadedChunks[i][j][k] = Chunk(0,0,0);
//			}
//		}
//	}
//}

std::vector<float>& Chunk::GetChunkMesh()
{
	return chunkMesh;
}

//Need to add in calculating vertex position considering chunk position. This was used for testing, does not include greedy meshing.
void Chunk::BuildChunkMesh()
{
	for (int i = 0; i < chunkDimension; i++)
	{
		for (int j = 0; j < chunkDimension; j++)
		{
			for (int k = 0; k < chunkDimension; k++)
			{
				if (chunkBlocks[i][j][k] != BlockIndex::TestTransparent)
				{
					if (i == 0 || j == 0 || k == 0 || i == chunkDimension - 1 || j == chunkDimension - 1 || k == chunkDimension - 1 || Block::blocks[chunkBlocks[i][j][k - 1]].GetTransparency())
					{
						for (int frontIndex = 0; frontIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace().size();)
						{
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace()[frontIndex++] + i);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace()[frontIndex++] + j);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace()[frontIndex++] + k);
						}
					}
					if (i == 0 || j == 0 || k == 0 || i == chunkDimension - 1 || j == chunkDimension - 1 || k == chunkDimension - 1 || Block::blocks[chunkBlocks[i - 1][j][k]].GetTransparency())
					{
						for (int leftIndex = 0; leftIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace().size();)
						{
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace()[leftIndex++] + i);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace()[leftIndex++] + j);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace()[leftIndex++] + k);
						}
					}
					if (i == 0 || j == 0 || k == 0 || i == chunkDimension - 1 || j == chunkDimension - 1 || k == chunkDimension - 1 || Block::blocks[chunkBlocks[i][j][k + 1]].GetTransparency())
					{
						for (int backIndex = 0; backIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace().size();)
						{
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace()[backIndex++] + i);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace()[backIndex++] + j);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace()[backIndex++] + k);
						}
					}
					if (i == 0 || j == 0 || k == 0 || i == chunkDimension - 1 || j == chunkDimension - 1 || k == chunkDimension - 1 || Block::blocks[chunkBlocks[i + 1][j][k]].GetTransparency())
					{
						for (int rightIndex = 0; rightIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace().size();)
						{
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace()[rightIndex++] + i);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace()[rightIndex++] + j);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace()[rightIndex++] + k);
						}
					}
					if (i == 0 || j == 0 || k == 0 || i == chunkDimension - 1 || j == chunkDimension - 1 || k == chunkDimension - 1 || Block::blocks[chunkBlocks[i][j + 1][k]].GetTransparency())
					{
						for (int topIndex = 0; topIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace().size();)
						{
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace()[topIndex++] + i);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace()[topIndex++] + j);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace()[topIndex++] + k);
						}
					}
					if (i == 0 || j == 0 || k == 0 || i == chunkDimension - 1 || j == chunkDimension - 1 || k == chunkDimension - 1 || Block::blocks[chunkBlocks[i][j - 1][k]].GetTransparency())
					{
						for (int bottomIndex = 0; bottomIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBottomFace().size();)
						{
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBottomFace()[bottomIndex++] + i);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBottomFace()[bottomIndex++] + j);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBottomFace()[bottomIndex++] + k);
						}
					}
				}
			}
		}
	}
}

//void Chunk::BuildChunkMesh()
//{
//	for (int i = 0; i < 6; i++)
//	{
//		for (int z = 0; )
//		{
//
//		}
//	}
//}

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

//Tests noise generated chunk.
void Chunk::GenerateRandomChunk(int chunkX, int chunkY, int chunkZ)
{
	FastNoiseSIMD* myNoise = FastNoiseSIMD::NewFastNoiseSIMD();
	float* noiseSet = myNoise->GetSimplexFractalSet(chunkDimension * chunkX, chunkDimension * chunkY, chunkDimension * chunkZ, 
													chunkDimension * chunkX + chunkDimension, chunkDimension * chunkY + chunkDimension, chunkDimension * chunkZ + chunkDimension);
	int index = 0;
	for (int x = 0; x < chunkDimension; x++)
	{
		for (int y = 0; y < chunkDimension; y++)
		{
			for (int z = 0; z < chunkDimension; z++)
			{
				if (noiseSet[index++] > 0.05f)
				{
					chunkBlocks[x][y][z] = BlockIndex::Dirt;
				}
				else
				{
					chunkBlocks[x][y][z] = BlockIndex::TestTransparent;
				}
			}
		}
	}
}