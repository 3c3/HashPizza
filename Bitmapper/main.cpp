#include <iostream>
#include "Bitmap.h"

using namespace std;

int main()
{
	Bitmap bmp;
	bmp.Create(300, 300);

	bmp.Fill(0, 0, 8, 8, { 0, 255, 0 });

	bmp.Save("test.bmp");
}