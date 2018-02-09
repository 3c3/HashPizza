#include "Bitmap.h"

void Bitmap::Create(int width, int height)
{
	size = width*height * 3 + headerSize;
	data = new char[size];

	header = (BITMAPFILEHEADER*)data;
	info = (BITMAPINFOHEADER*)(data + 14);

	header->bfType = 0x4D42;
	header->bfSize = 0;
	header->bfOffBits = headerSize;
	header->bfReserved1 = 0;
	header->bfReserved2 = 0;

	w = width;
	h = height;
	pixelArray = (Color*)(data + headerSize);
	pixelCount = w*h;

	info->biBitCount = 24;
	info->biClrImportant = 0;
	info->biClrUsed = 0;
	info->biCompression = 0;
	info->biHeight = -height;
	info->biWidth = width;
	info->biPlanes = 1;
	info->biSize = sizeof(BITMAPINFOHEADER);
	info->biSizeImage = size;	
	info->biXPelsPerMeter = 0;
	info->biYPelsPerMeter = 0;

	for (int i = 0; i < pixelCount; i++) pixelArray[i] = { 255,255,255 };
}

void Bitmap::Save(char *szFilename)
{
	HANDLE file = CreateFile(szFilename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD written;
	WriteFile(file, data, size, &written, 0);
}

void Bitmap::Fill(int x1, int y1, int x2, int y2, Color color)
{
	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++)
			pixelArray[j*w + i] = color;
	}
}