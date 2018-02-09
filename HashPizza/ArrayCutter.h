#pragma once
#include "IngredientSum.h"
#include "Common.h"
#include <vector>

using namespace std;

inline bool TooLittle(IngredientSum sum);

inline bool TooMuch(IngredientSum sum);

int BestScoreArray(IngredientSum *items, int startIdx);

void ExtractCuts(int startIdx, vector<Cut> &outCuts);

int FindBestScore(IngredientSum *arr, int size, int min, int max);