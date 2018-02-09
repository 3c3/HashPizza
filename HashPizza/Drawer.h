#pragma once
#include "Bitmap.h"
#include "Common.h"
#include <vector>

using namespace std;

#define BLOCK_SIZE 16
#define ITEM_OFFSET 4
#define REGION_OFFSET 2

Bitmap* CreateBitmap(int w, int h);
void DrawArray(Bitmap *bmp, char pizza[MAX_SIZE][MAX_SIZE], int w, int h);
void DrawSlices(Bitmap *bmp, vector<Cut2D> &cuts);