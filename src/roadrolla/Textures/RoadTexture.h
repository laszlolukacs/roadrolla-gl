#ifndef ROAD_TEXTURE_H
#define ROAD_TEXTURE_H

#include <stdlib.h>
#include <math.h>
#include "../Texture.h"

struct RoadTexture : public Texture
{
	void generateTextureArray() override
	{
		for (unsigned char i = 0; i < TEXTURE_SIZE; i++)
			for (unsigned char j = 0; j < TEXTURE_SIZE; j++)
			{
				if ((i / 2 % (rand() % 7 + 1)) ^ (j / 4 % (rand() % 5 + 2)))
				{
					texture[i * 3 * TEXTURE_SIZE + 3 * j] = (unsigned char)(112);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 1] = (unsigned char)(128);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 2] = (unsigned char)(144);
				}
				else
				{
					texture[i * 3 * TEXTURE_SIZE + 3 * j] = (unsigned char)((1.0f + 0.75f * sinf((float)i * 0.125f)) * 70.0f);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 1] = (unsigned char)((1.0f + 0.125f * cosf((float)i * 0.25f)) * 130.0f);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 2] = (unsigned char)((1.0f + 0.0625f * sinf((float)j * 0.125f)) * 180.0f);
				}

				if (i == TEXTURE_SIZE / 2)
				{
					texture[i * 3 * TEXTURE_SIZE + 3 * j] = (unsigned char)(255);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 1] = (unsigned char)(236);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 2] = (unsigned char)(139);
				}
			}
	}
};

#endif