#include "Drawer.h"

Color mushroomColor{ 100, 100, 100 };
Color tomatoColor{ 0, 0, 255 };
Color regionColor{ 130, 170, 0 };

Bitmap* CreateBitmap(int w, int h)
{
	Bitmap *result = new Bitmap;
	result->Create(w * BLOCK_SIZE, h * BLOCK_SIZE);
	return result;
}

void DrawArray(Bitmap *bmp, char pizza[MAX_SIZE][MAX_SIZE], int w, int h)
{
	int x, y;

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			x = i * BLOCK_SIZE;
			y = j * BLOCK_SIZE;

			if (pizza[j][i] == 'T')
				bmp->Fill(x + ITEM_OFFSET, y + ITEM_OFFSET, x + BLOCK_SIZE - ITEM_OFFSET, y + BLOCK_SIZE - ITEM_OFFSET, tomatoColor);
			else bmp->Fill(x + ITEM_OFFSET, y + ITEM_OFFSET, x + BLOCK_SIZE - ITEM_OFFSET, y + BLOCK_SIZE - ITEM_OFFSET, mushroomColor);
		}
	}
}

void DrawSlices(Bitmap *bmp, vector<Cut2D> &cuts)
{
	for (int i = 0; i < cuts.size(); i++)
	{
		Cut2D &cut = cuts[i];
		bmp->Fill(cut.col1 * BLOCK_SIZE + REGION_OFFSET, cut.row1 * BLOCK_SIZE + REGION_OFFSET,
			cut.col2 * BLOCK_SIZE + BLOCK_SIZE - REGION_OFFSET, cut.row2 * BLOCK_SIZE + BLOCK_SIZE - REGION_OFFSET,
			regionColor);
	}
}