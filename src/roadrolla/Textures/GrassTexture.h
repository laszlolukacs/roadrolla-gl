#ifndef GRASS_TEXTURE_H
#define GRASS_TEXTURE_H

#include <stdlib.h>
#include <math.h>
#include "../Texture.h"

struct GrassTexture : public Texture
{
	void generateTextureArray() override
	{
		for (unsigned char i = 0; i < TEXTURE_SIZE; i++)
			for (unsigned char j = 0; j < TEXTURE_SIZE; j++)
			{
				if ((i / 2 % (rand() % 7 + 1)) ^ (j / 4 % (rand() % 5 + 2)))
				{
					texture[i * 3 * TEXTURE_SIZE + 3 * j] = (unsigned char)((1.0f + 0.75f * sinf((float)j * 0.125f)) * 34.0f);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 1] = (unsigned char)((1.0f + 0.0625f * sinf((float)i * 0.25f)) * 139.0f);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 2] = (unsigned char)((1.0f + 0.5f * cosf((float)j * 0.125f)) * 34.0f);
				}
				else
				{
					texture[i * 3 * TEXTURE_SIZE + 3 * j] = (unsigned char)(0);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 1] = (unsigned char)(100);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 2] = (unsigned char)(0);
				}
			}
	}
};

#endif
