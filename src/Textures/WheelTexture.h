#ifndef WHEEL_TEXTURE_H
#define WHEEL_TEXTURE_H

#include <stdlib.h>
#include <math.h>
#include "../Texture.h"

struct WheelTexture : public Texture
{
	void generateTextureArray() override
	{
		srand(glutGet(GLUT_ELAPSED_TIME));
		for (unsigned char i = 0; i < TEXTURE_SIZE; i++)
			for (unsigned char j = 0; j < TEXTURE_SIZE; j++)
			{
				if ((i / 2 % (rand() % 7 + 1)) ^ (j / 4 % (rand() % 5 + 2)))
				{
					texture[i * 3 * TEXTURE_SIZE + 3 * j] = (unsigned char)(1);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 1] = (unsigned char)(1);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 2] = (unsigned char)(16);
				}
				else
				{
					texture[i * 3 * TEXTURE_SIZE + 3 * j] = (unsigned char)((1.0f + 0.133f * sinf((float)i * 0.125f)) * 112.0f);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 1] = (unsigned char)((1.0f + 0.125f * cosf((float)i * 0.25f)) * 128.0f);
					texture[i * 3 * TEXTURE_SIZE + 3 * j + 2] = (unsigned char)((1.0f + 0.0625f * sinf((float)j * 0.125f)) * 144.0f);
				}
			}
	}
};

#endif