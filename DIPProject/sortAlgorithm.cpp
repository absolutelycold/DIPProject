#include "sortAlgorithm.h"

void bolbSortInt(int* inputArray, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			
			if (inputArray[j] > inputArray[j + 1])
			{
				int temp = inputArray[j + 1];
				inputArray[j + 1] = inputArray[j];
				inputArray[j] = temp;
			}
		}
	}
}
