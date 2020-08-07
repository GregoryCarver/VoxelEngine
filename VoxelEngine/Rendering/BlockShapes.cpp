#include "BlockShapes.h"

const BlockShape BlockShapes::shapes[] = 
	{
		BlockShape
		(
			//Front Face
			{
				 0.0f,  0.0f,  0.0f,
				 1.0f,  0.0f,  0.0f,
				 0.0f,  1.0f,  0.0f,
				 0.0f,  1.0f,  0.0f,
				 1.0f,  0.0f,  0.0f,
				 1.0f,  1.0f,  0.0f
			},
			//Left Face
			{
				 0.0f,  0.0f, -1.0f,
				 0.0f,  0.0f,  0.0f,
				 0.0f,  1.0f, -1.0f,
				 0.0f,  1.0f, -1.0f,
				 0.0f,  0.0f,  0.0f,
				 0.0f,  1.0f,  0.0f
			},
			//Back Face
			{
				 1.0f,  0.0f, -1.0f,
				 0.0f,  0.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				 0.0f,  0.0f, -1.0f,
				 0.0f,  1.0f, -1.0f
			},
			//Right Face
			{
				 1.0f,  0.0f,  0.0f,
				 1.0f,  0.0f, -1.0f,
				 1.0f,  1.0f,  0.0f,
				 1.0f,  1.0f,  0.0f,
				 1.0f,  0.0f, -1.0f,
				 1.0f,  1.0f, -1.0f
			},
			//Top Face
			{
				 0.0f,  1.0f,  0.0f,
				 1.0f,  1.0f,  0.0f,
				 0.0f,  1.0f, -1.0f,
				 0.0f,  1.0f, -1.0f,
				 1.0f,  1.0f,  0.0f,
				 1.0f,  1.0f, -1.0f
			},
			//Bottom Face
			{
				 1.0f,  0.0f,  0.0f,
				 0.0f,  0.0f,  0.0f,
				 1.0f,  0.0f, -1.0f,
				 1.0f,  0.0f, -1.0f,
				 0.0f,  0.0f,  0.0f,
				 0.0f,  0.0f, -1.0f
			}
		)
	};