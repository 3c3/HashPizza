#include "ArrayCutter.h"

int n;
int min, max;

IngredientSum items[MAX_SIZE];
int bestScoreStartingAt[MAX_SIZE];
Cut bestCutStartingAt[MAX_SIZE];

inline bool TooLittle(IngredientSum sum)
{
	return sum.mushroomSum < min || sum.tomatoSum < min;
}

inline bool TooMuch(IngredientSum sum)
{
	return sum.mushroomSum + sum.tomatoSum > max;
}

int BestScoreArray(IngredientSum *items, int startIdx)
{
	if (startIdx >= n) return 0;
	int origStart = startIdx;

	// вече сме го сметнали
	if (bestScoreStartingAt[startIdx] != -1) return bestScoreStartingAt[startIdx];

	int maxStartIdx = -1;

	int j = startIdx;
	IngredientSum sum = items[startIdx];

	int candScore = 0;
	Cut candCut;

	while (startIdx < n && j < n)
	{
		if (TooMuch(sum)) // превишили сме
		{ // но е първата сума и затова просто изместваме началото
			if (candScore != 0)
			{
				break;
			}
			sum -= items[startIdx];
			//sum = sumMan.Get(startIdx, j);
			startIdx++;
		}
		else if (TooLittle(sum)) // още трябва
		{
			j++;
			sum += items[j];
			//sum = sumMan.Get(startIdx, j);
		}
		else // имаме правилна сума
		{
			if (!candScore)
			{
				maxStartIdx = j; // ако почнем след j, то със сигурност
								 // сме пропуснали един хубав слайс
			}

			int afterScore = BestScoreArray(items, j + 1);
			int score = j - startIdx + 1 + afterScore;
			if (score > candScore)
			{
				candScore = score;
				candCut.start = startIdx;
				candCut.end = j;
			}
			j++;
			sum += items[j];
			//sum = sumMan.Get(startIdx, j);
		}
	}

	if (!candScore)
	{
		bestScoreStartingAt[startIdx] = 0;
		return 0;
	}

	// Опитваме се да образуваме и други суми
	// туй може и да се окаже частично излишно
	for (startIdx = origStart + 1; startIdx <= maxStartIdx; startIdx++)
	{
		sum = items[startIdx];
		j = startIdx;

		while (j < n)
		{
			if (TooMuch(sum)) break;

			if (TooLittle(sum))
			{
				j++;
				sum += items[j];
				//sum = sumMan.Get(startIdx, j);
			}
			else
			{
				int score = j - startIdx + 1 + BestScoreArray(items, j + 1);
				if (score > candScore)
				{
					candScore = score;
					candCut.start = startIdx;
					candCut.end = j;
				}

				j++;
				sum += items[j];
				//sum = sumMan.Get(startIdx, j);
			}
		}
	}

	bestScoreStartingAt[origStart] = candScore;
	bestCutStartingAt[origStart] = candCut;

	return candScore;
}

void ExtractCuts(int startIdx, vector<Cut> &outCuts)
{
	outCuts.clear();
	Cut current = bestCutStartingAt[startIdx];
	int sum = 0;
	while (bestScoreStartingAt[startIdx] != 0 && bestScoreStartingAt[startIdx] != -1)
	{
		int len = current.end - current.start + 1;
		outCuts.push_back(current);
		sum += len;
		startIdx = bestCutStartingAt[startIdx].end + 1;
		current = bestCutStartingAt[startIdx];
	}
}

int FindBestScore(IngredientSum *arr, int size, int min, int max)
{
	memset(bestScoreStartingAt, -1, MAX_SIZE * sizeof(int));
	n = size;
	::min = min;
	::max = max;
	return BestScoreArray(arr, 0);
}