#pragma once
#include <windows.h>

struct Color
{
	unsigned char red, green, blue;
};

class Bitmap
{
private:
	char *data;
	Color *pixelArray;
	int w, h, pixelCount;
	int size;
	BITMAPFILEHEADER *header;
	BITMAPINFOHEADER *info;

	const int headerSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

public:
	void Create(int width, int height);
	void Save(char *szFilename);

	void Fill(int x1, int y1, int x2, int y2, Color color);
};
