#include "FenwickTree.h"

inline int LSB(int x)
{
	return x & -x;
}

void FenwickTree::Build(IngredientSum *srcArray, int size)
{
	tree = new IngredientSum[size];
	for (int i = 0; i < size; i++) tree[i] = srcArray[i];
	for (int i = 0; i < size; i++)
	{
		int j = i + LSB(i+1);
		if (j < size) tree[j] += tree[i];
	}
}

IngredientSum FenwickTree::Read(int idx)
{
	idx++;
	IngredientSum sum { 0, 0 };
	while (idx)
	{
		sum += tree[idx - 1];
		idx -= LSB(idx);
	}
	return sum;
}

IngredientSum FenwickTree::Read(int start, int end)
{
	IngredientSum result = Read(end);
	result -= Read(start - 1);
	return result;
}

void FenwickTree::AddAt(int idx, IngredientSum value)
{
	while (idx < size)
	{
		tree[idx] += value;
		idx += LSB(idx + 1);
	}
}