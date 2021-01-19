#pragma once

#include"../Utils/IO/FileReader.h"

struct ImageData
{
	unsigned char* pixels;
	int width, height;
	int BPP;

	ImageData()
		:
		pixels(nullptr),
		width(0),
		height(0),
		BPP(0)
	{
	}

	ImageData(unsigned char* pixels,const unsigned int& width,const unsigned int& height,const unsigned int& BPP)
		:
		pixels(pixels),
		width(width), 
		height(height),
		BPP(BPP)
	{}

	ImageData(const ImageData& image)
	{
		this->width = image.width;
		this->height = image.height;
		this->BPP = image.BPP;

		this->pixels = new unsigned char[this->width * this->height * this->BPP];

		memcpy(this->pixels, image.pixels, image.width * image.height * image.BPP);
	}

	ImageData(ImageData&& image)
	{
		this->width = image.width;
		this->height = image.height;
		this->BPP = image.BPP;

		this->pixels = image.pixels;
		image.pixels = nullptr;
	}


	~ImageData()
	{
		PX::IO::FreeImage(this->pixels);
	}

	void operator = (const ImageData& image)
	{
		PX::IO::FreeImage(this->pixels);
		this->pixels = nullptr;

		this->width = image.width;
		this->height = image.height;
		this->BPP = image.BPP;

		this->pixels = new unsigned char[this->width * this->height * this->BPP];

		memcpy(this->pixels, image.pixels, image.width * image.height * image.BPP);
	}

	void operator = (ImageData&& image)
	{
		PX::IO::FreeImage(this->pixels);
		this->pixels = nullptr;

		this->width = image.width;
		this->height = image.height;
		this->BPP = image.BPP;

		this->pixels = image.pixels;
		image.pixels = nullptr;
	}

};