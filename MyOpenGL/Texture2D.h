#pragma once



class Image
{
public:
	Image();
	Image(const char* path);
	~Image();

	//����ͼƬ
	void SetPicture(const char* path);

	//ж��ͼƬ
	void DeletePicture();

	//�Ƿ����
	bool IsActive()const { return data_ ? true : false; }

	//ͼƬ����
	unsigned char* Data()const { return data_; }

	//ͼƬ·��
	const char* Path()const { return path_; }

	//��
	int Width()const { return width_; }

	//��
	int Height()const { return height_; }

	//��ɫͨ������
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

	//��������
	void SetTexture(Image* image, bool isfree = true);

	//ɾ������
	void DeleteTexture();

	//��������
	//void SetData(Image* image);

	//�Ƿ����
	bool IsActive() { return id_ != 0; }

	//��������
	void Use();

private:
	unsigned int id_;
};
