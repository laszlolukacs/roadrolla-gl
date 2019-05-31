#ifndef TEXTURE_H
#define TEXTURE_H

#define TEXTURE_SIZE 32
static unsigned int g_CurrentTextureNumber = 1;

struct Texture
{
	unsigned int id;
	unsigned char texture[3 * TEXTURE_SIZE * TEXTURE_SIZE];

	virtual void generateTextureArray() = 0;

	void generate()
	{
		glGenTextures(g_CurrentTextureNumber, &id);
		g_CurrentTextureNumber++;
		glBindTexture(GL_TEXTURE_2D, id);

		generateTextureArray();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_SIZE, TEXTURE_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void setup_gl() const
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	virtual ~Texture()
	{
	}
};

#endif // TEXTURE_H