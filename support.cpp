#include "support.h"

bool gameOver(int& winner, Scaffold s, int N)
{

	int color = -1;
	if (win(s, color, N))
	{
		winner = color;
		return true;
	}

	// Neither player won and there are no more vacant spots left
	if (s.numberEmpty() == 0)
	{
		winner = TIE_GAME;
		return true;
	}

	// No one has won and there are still vacant spots left
	return false;
}

bool win(Scaffold s, int &color, int N)
{

	// It's impossible for anyone to win the game if there are too many empty spots
	if (s.numberEmpty() > (s.cols() * s.levels() - N))
		return false;

	// Use this scaffold numbering: levels go from bottom to top starting at 1, columns go from left to right starting at 1


	// Check horizontal
	for (int i = 1; i <= s.levels(); i++)	// Traverse the rows from bottom to top
	{
		for (int j = 1; j <= s.cols() - N + 1; j++)	// Traverse the columns from left to right
		{
			int checkerColor = s.checkerAt(j, i);
			if (checkerColor == VACANT)
			{
				continue;
			}
			int numInARow = 1;
			for (int k = 1; k < N && s.checkerAt(j + k, i) == checkerColor; k++)		// Check for consecutive colors
			{
				numInARow++;
				if (numInARow == N)
				{
					color = checkerColor;
					return true;
				}
			}
		}
	}

	// Check vertical
	for (int i = 1; i <= s.levels() - N + 1; i++)		// Traverse rows from bottom to top
	{
		for (int j = 1; j <= s.cols(); j++)		// Traverse columns from left to right
		{
			int checkerColor = s.checkerAt(j, i);
			if (checkerColor == VACANT)
			{
				continue;
			}
			int numInARow = 1;
			for (int k = 1; k < N && s.checkerAt(j, i + k) == checkerColor; k++)		// Check for consecutive colors
			{
				numInARow++;
				if (numInARow == N)
				{
					color = checkerColor;
					return true;
				}
			}
		}
	}

	// Check diagonal (top left to bottom right)
	for (int i = N; i <= s.levels(); i++)		// Traverse rows from bottom to top
	{
		for (int j = 1; j <= s.cols() - N + 1; j++)	// Traverse columns from left to right
		{
			int checkerColor = s.checkerAt(j, i);
			if (checkerColor == VACANT)
			{
				continue;
			}
			int numInARow = 1;
			for (int k = 1; k < N && s.checkerAt(j + k, i - k) == checkerColor; k++)		// Check for consecutive colors
			{
				numInARow++;
				if (numInARow == N)
				{
					color = checkerColor;
					return true;
				}
			}
		}
	}

	// Check diagonal (bottom left to top right)
	for (int i = 1; i <= s.levels() - N + 1; i++)		// Traverse rows from bottom to top
	{
		for (int j = 1; j <= s.cols() - N + 1; j++)	// Traverse columns from left to right
		{
			int checkerColor = s.checkerAt(j, i);
			if (checkerColor == VACANT)
			{
				continue;
			}
			int numInARow = 1;
			for (int k = 1; k < N && s.checkerAt(j + k, i + k) == checkerColor; k++)		// Check for consecutive colors
			{
				numInARow++;
				if (numInARow == N)
				{
					color = checkerColor;
					return true;
				}
			}
		}
	}

	return false;	// Player hasn't won
}
