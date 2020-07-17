#include "Chunk.h"
#include <iostream>

std::vector<float>& Chunk::GetChunkMesh()
{
	return chunkMesh;
}

//Need to add in calculating vertex position considering chunk position.
void Chunk::BuildChunkMesh()
{
	for (int i = 0; i < chunkDimension - 1; i++)
	{
		for (int j = 0; j < chunkDimension - 1; j++)
		{
			for (int k = 0; k < chunkDimension - 1; k++)
			{
				if (i == 0 || j == 0 || k == 0 || Block::blocks[chunkBlocks[i][j][k - 1]].GetTransparency())
				{
					for (int frontIndex = 0; frontIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace().size();)
					{
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace()[frontIndex++] + i);
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace()[frontIndex++] + j);
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetFrontFace()[frontIndex++] + k);
					}
				}
				if (i == 0 || j == 0 || k == 0 || Block::blocks[chunkBlocks[i - 1][j][k]].GetTransparency())
				{
					for (int leftIndex = 0; leftIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace().size();)
					{
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace()[leftIndex++] + i);
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace()[leftIndex++] + j);
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetLeftFace()[leftIndex++] + k);
					}
				}
				if (i == 0 || j == 0 || k == 0 || Block::blocks[chunkBlocks[i][j][k + 1]].GetTransparency())
				{
					for (int backIndex = 0; backIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace().size();)
					{
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace()[backIndex++] + i);
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace()[backIndex++] + j);
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetBackFace()[backIndex++] + k);
					}
				}
				if (i == 0 || j == 0 || k == 0 || Block::blocks[chunkBlocks[i + 1][j][k]].GetTransparency())
				{
					for (int rightIndex = 0; rightIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace().size();)
					{
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace()[rightIndex++] + i);
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace()[rightIndex++] + j);
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetRightFace()[rightIndex++] + k);
					}
				}
				if (i == 0 || j == 0 || k == 0 || Block::blocks[chunkBlocks[i][j + 1][k]].GetTransparency())
				{
					for (int topIndex = 0; topIndex < Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace().size();)
					{
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace()[topIndex++] + i);
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace()[topIndex++] + j);
						chunkMesh.push_back(Block::blocks[chunkBlocks[i][j][k]].GetBlockShape().GetTopFace()[topIndex++] + k);
					}
				}
				if (i == 0 || j == 0 || k == 0 || Block::blocks[chunkBlocks[i][j - 1][k]].GetTransparency())
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