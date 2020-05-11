#include "Texture2D.h"

#include "glad/glad.h"
#include "stb_image/stb_image.h"


Image::Image()
{
	//反转y轴
	stbi_set_flip_vertically_on_load(true);
	data_ = nullptr;
	path_ = nullptr;
	width_ = 0;
	height_ = 0;
	nr_channels_ = 0;
}


Image::Image(const char* path)
{
	//反转y轴
	stbi_set_flip_vertically_on_load(true);
	path_ = path;
	data_ = stbi_load(path, &width_, &height_, &nr_channels_, 0);
}


Image::~Image()
{
	DeletePicture();
}


void Image::SetPicture(const char* path)
{
	DeletePicture();
	path_ = path;
	data_ = stbi_load(path, &width_, &height_, &nr_channels_, 0);
}


void Image::DeletePicture()
{
	if (data_)
	{
		stbi_image_free(data_);
		data_ = nullptr;
		path_ = nullptr;
		width_ = 0;
		height_ = 0;
		nr_channels_ = 0;
	}
}


Texture2D::Texture2D()
{
	id_ = 0;
}


Texture2D::Texture2D(Image* image, bool isfree)
{
	id_ = 0;
	SetTexture(image, isfree);
}


Texture2D::~Texture2D()
{
	DeleteTexture();
}


void Texture2D::SetTexture(Image* image, bool isfree)
{
	if (!image->IsActive())
		return;

	DeleteTexture();

	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->Width(), image->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->Data());
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (isfree)
		image->DeletePicture();
}


void Texture2D::DeleteTexture()
{
	if (id_)
	{
		glDeleteTextures(1, &id_);
		id_ = 0;
	}
}


void Texture2D::SetData(Image* image)
{
	if (!id_)
		return;

	if (!image->IsActive())
		return;

	glBindTexture(GL_TEXTURE_2D, id_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->Width(), image->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->Data());
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture2D::Use()
{
	glBindTexture(GL_TEXTURE_2D, id_);
}