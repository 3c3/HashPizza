#pragma once

struct IngredientSum
{
	int mushroomSum;
	int tomatoSum;

	void operator+=(const IngredientSum& other)
	{
		mushroomSum += other.mushroomSum;
		tomatoSum += other.tomatoSum;
	}

	void operator-=(const IngredientSum& other)
	{
		mushroomSum -= other.mushroomSum;
		tomatoSum -= other.tomatoSum;
	}

	IngredientSum operator+(const IngredientSum& b)
	{
		IngredientSum result = *this;
		result += b;
		return result;
	}

	IngredientSum operator-(const IngredientSum& b)
	{
		IngredientSum result = *this;
		result -= b;
		return result;
	}
};