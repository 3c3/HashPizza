#pragma once

template <class T>
class SumManager
{
private:
	
	int size;
	
public:
	T *sumArray;

	void Build(T *srcArray, int size)
	{
		this->size = size;
		sumArray = new T[size];
		sumArray[0] = srcArray[0];
		for (int i = 1; i < size; i++) sumArray[i] = sumArray[i - 1] + srcArray[i];
	}

	T Get(int endIdx)
	{
		return sumArray[endIdx];
	}
	T Get(int startIdx, int endIdx)
	{
		if (startIdx) return sumArray[endIdx] - sumArray[startIdx - 1];
		else return sumArray[endIdx];
	}
};

