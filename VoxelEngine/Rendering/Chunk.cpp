#include <iostream>
#include "Chunk.h"
#include "../Libraries/FastNoise/FastNoiseSIMD.h"

//Chunk Chunk::loadedChunks[Chunk::renderDistance][Chunk::renderDistance][Chunk::renderDistance];

Chunk::Chunk(int chunkX, int chunkY, int chunkZ)
{
	GenerateRandomChunk(chunkX, chunkY, chunkZ);
	BuildChunkMesh(chunkX, chunkY, chunkZ);
	RenderableInit(chunkMesh.size(), chunkMesh);
}

std::vector<float>& Chunk::GetChunkMesh()
{
	return chunkMesh;
}

//Need to add in calculating vertex position considering chunk position. This was used for testing, does not include greedy meshing.
void Chunk::BuildChunkMesh(int chunkX, int chunkY, int chunkZ)
{
	for (int i = 0; i < chunkDimension; i++)
	{
		for (int j = 0; j < chunkDimension; j++)
		{
			for (int k = 0; k < chunkDimension; k++)
			{
				if (chunkBlocks[i][j][k] != BlockIndex::TestTransparent)
				{
					if (i == 0 || j == 0 || k == 0 || i == chunkDimension - 1 || j == chunkDimension - 1 || k == chunkDimension - 1 || Block::blocks[chunkBlocks[i][j][k + 1]].GetTransparency())
					{
						for (int frontIndex = 0; frontIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace().size();)
						{
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace()[frontIndex++] + i + (chunkX * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace()[frontIndex++] + j + (chunkY * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace()[frontIndex++] + k + (chunkZ * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace()[frontIndex++]);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace()[frontIndex++]);
						}
					}
					if (i == 0 || j == 0 || k == 0 || i == chunkDimension - 1 || j == chunkDimension - 1 || k == chunkDimension - 1 || Block::blocks[chunkBlocks[i - 1][j][k]].GetTransparency())
					{
						for (int leftIndex = 0; leftIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace().size();)
						{
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace()[leftIndex++] + i + (chunkX * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace()[leftIndex++] + j + (chunkY * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace()[leftIndex++] + k + (chunkZ * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace()[leftIndex++]);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace()[leftIndex++]);
						}
					}
					if (i == 0 || j == 0 || k == 0 || i == chunkDimension - 1 || j == chunkDimension - 1 || k == chunkDimension - 1 || Block::blocks[chunkBlocks[i][j][k - 1]].GetTransparency())
					{
						for (int backIndex = 0; backIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace().size();)
						{
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace()[backIndex++] + i + (chunkX * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace()[backIndex++] + j + (chunkY * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace()[backIndex++] + k + (chunkZ * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace()[backIndex++]);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace()[backIndex++]);
						}
					}
					if (i == 0 || j == 0 || k == 0 || i == chunkDimension - 1 || j == chunkDimension - 1 || k == chunkDimension - 1 || Block::blocks[chunkBlocks[i + 1][j][k]].GetTransparency())
					{
						for (int rightIndex = 0; rightIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace().size();)
						{
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace()[rightIndex++] + i + (chunkX * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace()[rightIndex++] + j + (chunkY * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace()[rightIndex++] + k + (chunkZ * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace()[rightIndex++]);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace()[rightIndex++]);

						}
					}
					if (i == 0 || j == 0 || k == 0 || i == chunkDimension - 1 || j == chunkDimension - 1 || k == chunkDimension - 1 || Block::blocks[chunkBlocks[i][j + 1][k]].GetTransparency())
					{
						for (int topIndex = 0; topIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace().size();)
						{
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace()[topIndex++] + i + (chunkX * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace()[topIndex++] + j + (chunkY * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace()[topIndex++] + k + (chunkZ * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace()[topIndex++]);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace()[topIndex++]);
						}
					}
					if (i == 0 || j == 0 || k == 0 || i == chunkDimension - 1 || j == chunkDimension - 1 || k == chunkDimension - 1 || Block::blocks[chunkBlocks[i][j - 1][k]].GetTransparency())
					{
						for (int bottomIndex = 0; bottomIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBottomFace().size();)
						{
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBottomFace()[bottomIndex++] + i + (chunkX * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBottomFace()[bottomIndex++] + j + (chunkY * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBottomFace()[bottomIndex++] + k + (chunkZ * chunkDimension));
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBottomFace()[bottomIndex++]);
							chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBottomFace()[bottomIndex++]);
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
	float* noiseSet = myNoise->GetPerlinSet(chunkDimension * chunkX, chunkDimension * chunkY, chunkDimension * chunkZ, 
													chunkDimension * chunkX + chunkDimension, chunkDimension * chunkY + chunkDimension, chunkDimension * chunkZ + chunkDimension);
	int index = 0;
	for (int x = 0; x < chunkDimension; x++)
	{
		std::cout << noiseSet[index] << std::endl;
		for (int y = 0; y < chunkDimension; y++)
		{
			for (int z = 0; z < chunkDimension; z++)
			{
				if (noiseSet[index++] < 0.05f)
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

void Chunk::DrawChunk()
{
	Draw(chunkMesh.size());
}