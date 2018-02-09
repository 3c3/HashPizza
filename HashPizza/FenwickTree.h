#pragma once
#include "IngredientSum.h"

class FenwickTree
{
private:
	IngredientSum *tree;
	int size;

public:
	void Build(IngredientSum *srcArray, int size);
	IngredientSum Read(int idx);
	IngredientSum Read(int start, int end);
	void AddAt(int idx, IngredientSum value);
};