#include <iostream>
#include <vector>
#include "SumManager.h"
#include "IngredientSum.h"
#include "ArrayCutter.h"
#include "Common.h"
#include "Drawer.h"

using namespace std;

SumManager<IngredientSum> rowSums[MAX_SIZE];
char inputTable[MAX_SIZE][MAX_SIZE];
int inputRows, inputColumns;
int inputMin, inputMax;

IngredientSum rowBuffer[MAX_SIZE];

void MakeArrayFromSlice(IngredientSum *arr, int startColumn, int endColumn)
{
	for (int i = 0; i < inputRows; i++)
		arr[i] = rowSums[i].Get(startColumn, endColumn);
}

int GetSliceScore(int start, int end, vector<Cut> &cuts)
{
	MakeArrayFromSlice(rowBuffer, start, end);
	int score = FindBestScore(rowBuffer, inputRows, inputMin, inputMax);
	score *= (end - start + 1);
	ExtractCuts(0, cuts);
	return score;
}

int bestSliceScoreStartingAt[MAX_SIZE];
Cut bestSliceStartingAt[MAX_SIZE];
vector<Cut> bestSliceCuts[MAX_SIZE];
int minSliceLen = 1;
int maxSliceLen;

// най-добрите точки на резен, който почва не по-рано от startIdx
int BestScorePizza(int startIdx)
{
	if (startIdx >= inputColumns) return 0;
	if (bestSliceScoreStartingAt[startIdx] != -1) return bestSliceScoreStartingAt[startIdx];

	int origStart = startIdx;

	int candScore = 0;
	Cut candSlice;
	vector<Cut> candCuts;
	vector<Cut> tmpCuts;

	int maxStartIdx = -1;

	// Специален цикъл за намиране на първия добър резен
	// за да знаем колко максимално колони можем да пропуснем
	// без сигурно да губим оптималност
	int j = startIdx + minSliceLen - 1;
	while (startIdx < inputColumns && j < inputColumns)
	{
		if ((j - startIdx) >= maxSliceLen)
		{
			if (candScore) break; // вече сме открили добри резени, спираме
			// явно от тая позиция не става, пробваме от следващата
			startIdx++;
			j = startIdx + minSliceLen - 1;
			continue;
		}

		int score = GetSliceScore(startIdx, j, tmpCuts) + BestScorePizza(j+1);
		if (score)
		{
			// ако пропуснем повече от толкова колони, със сигурност губим точки
			if (maxStartIdx == -1) maxStartIdx = j;
			if (score > candScore)
			{
				candScore = score;
				candSlice = { startIdx, j };
				candCuts = tmpCuts;
			}
		}
		j++;
	}

	if (!candScore)
	{
		bestSliceScoreStartingAt[origStart] = 0;
		return 0;
	}

	// проверяваме дали няма да направим повече точки ако пропуснем някои колони
	for (++startIdx; startIdx <= maxStartIdx; startIdx++)
	{
		j = startIdx + minSliceLen - 1;
		while (j < inputColumns && (j - startIdx) < maxSliceLen)
		{
			int score = GetSliceScore(startIdx, j, tmpCuts) + BestScorePizza(j + 1);
			if (score > candScore)
			{
				candScore = score;
				candSlice = { startIdx, j };
				candCuts = tmpCuts;
			}
			j++;
		}
	}

	bestSliceScoreStartingAt[origStart] = candScore;
	bestSliceStartingAt[origStart] = candSlice;
	bestSliceCuts[origStart] = candCuts;

	return candScore;
}

void ExtractCuts2D(vector<Cut2D> &outVec)
{
	outVec.clear();

	Cut currentSlice = bestSliceStartingAt[0];
	int startIdx = 0;

	while (bestSliceScoreStartingAt[startIdx] > 0)
	{
		for (int i = 0; i < bestSliceCuts[startIdx].size(); i++)
		{
			Cut &cut = bestSliceCuts[startIdx][i];
			outVec.push_back(Cut2D{ cut.start, cut.end, currentSlice.start, currentSlice.end });
		}
		startIdx = currentSlice.end + 1;
		currentSlice = bestSliceStartingAt[startIdx];
	}
}

int main()
{
	cin >> inputRows >> inputColumns;
	cin >> inputMin >> inputMax;

	IngredientSum* currentRow = new IngredientSum[inputColumns];
	//IngredientSum currentRow[MAX_SIZE];

	for (int i = 0; i < inputRows; i++)
	{
		for (int j = 0; j < inputColumns; j++)
		{
			cin >> inputTable[i][j];
			if (inputTable[i][j] == 'T') currentRow[j] = IngredientSum{ 0, 1 };
			else currentRow[j] = IngredientSum{ 1, 0 };
		}

		rowSums[i].Build(currentRow, inputColumns);
	}

	delete[] currentRow;

	memset(bestSliceScoreStartingAt, -1, MAX_SIZE * sizeof(int));

	cout << "Enter min slice len: ";
	cin >> minSliceLen;

	maxSliceLen = pow(inputMax, 0.66);
	cout << "max len is " << maxSliceLen << endl;

	int score = BestScorePizza(0);
	vector<Cut2D> cuts;
	ExtractCuts2D(cuts);

	cout << "Score: " << score << endl;
	int percentScore = 100 * score / (inputColumns * inputRows);
	cout << percentScore << "%" << endl;
	/*for (int i = 0; i < cuts.size(); i++)
	{
		Cut2D &cut = cuts[i];
		cout << cut.row1 << " " << cut.col1 << " " <<  cut.row2 << " " << cut.col2 << endl;
	}*/

	cout << "Drawing..." << endl;
	Bitmap *output = CreateBitmap(inputColumns, inputRows);
	DrawSlices(output, cuts);
	DrawArray(output, inputTable, inputColumns, inputRows);

	output->Save("output.bmp");

	system("pause");
}