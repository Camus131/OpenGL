#pragma once



class Image
{
public:
	Image();
	Image(const char* path);
	~Image();

	//加载图片
	void SetPicture(const char* path);

	//卸载图片
	void DeletePicture();

	//是否可用
	bool IsActive()const { return data_ ? true : false; }

	//图片数据
	unsigned char* Data()const { return data_; }

	//图片路径
	const char* Path()const { return path_; }

	//宽
	int Width()const { return width_; }

	//高
	int Height()const { return height_; }

	//颜色通道个数
	int NrChannels()const { return nr_channels_; }

private:
	unsigned char* data_;
	const char* path_;
	int width_;
	int height_;
	int nr_channels_;
};


class Texture2D
{
public:
	Texture2D();
	Texture2D(Image* image, bool isfree = true);
	~Texture2D();

	//生成纹理
	void SetTexture(Image* image, bool isfree = true);

	//删除纹理
	void DeleteTexture();

	//更新数据
	//void SetData(Image* image);

	//是否可用
	bool IsActive() { return id_ != 0; }

	//激活纹理
	void Use();

private:
	unsigned int id_;
};
