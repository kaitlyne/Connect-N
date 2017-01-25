// Scaffold.cpp

#include "provided.h"
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

class ScaffoldImpl
{
public:
    ScaffoldImpl(int nColumns, int nLevels);
	//~ScaffoldImpl();
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const; 
    void display() const; 
    bool makeMove(int column, int color); 
    int undoMove();
private:
	int m_Levels;
	int m_Cols;
	vector<vector<int>> scafPtr;
	stack <Coord> moveStack;
};

// Construct a Scaffold with the indicated number of columns and levels.
ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
	m_Levels = nLevels;
	m_Cols = nColumns;

	for (int i = 0; i < m_Levels; i++)
	{
		scafPtr.push_back(vector<int>());
	}

	// Indicate that each spot is vacant
	for (int j = 0; j < m_Levels; j++)
	{
		for (int k = 0; k < m_Cols; k++)
		{
			scafPtr[j].push_back(VACANT);
		}
	}
}

// Return the number of columns in the scaffold.
int ScaffoldImpl::cols() const
{
	return m_Cols;
}

// Return the number of levels in the scaffold.
int ScaffoldImpl::levels() const
{
	return m_Levels;
}

// Return the number of positions in the scaffold not occupied by a checker.
int ScaffoldImpl::numberEmpty() const
{
	int count = 0;

	// Loop through each element of the 2d array and count the number of vacant spots
	for (int j = 0; j < m_Levels; j++)
	{
		for (int k = 0; k < m_Cols; k++)
		{
			if (scafPtr[j][k] == VACANT)
				count++;
		}
	}
	return count;
}

// If there is a red checker at the indicated column and level, return RED;
// if there's a black checker there, return BLACK; otherwise, return VACANT.
int ScaffoldImpl::checkerAt(int column, int level) const
{
	// Users think the columns are numbered from left to right starting at 1
	// And the levels are considered to be numbered from bottom to top starting at 1
	// So, adjust the column and level parameters to match the numbering of the elements in the array
	return scafPtr[m_Levels - level][column - 1];
}

// Display the scaffold to the screen in the following manner:
// Display the levels of the scaffold from highest to lowest.
// Display each red checker as an R.
// Display each black checker as a B.
// Display each vacant cell as a space character.
// Display a - (hyphen)character below level 1 of each column.
// Display the side of each column as a | character.
// Display the joints between the bottom of the column and the sides of the columns as + characters.
void ScaffoldImpl::display() const
{
	// Display each level
	for (int j = 0; j < m_Levels; j++)
	{
		for (int k = 0; k < m_Cols; k++)
		{
			cout << '|';
			switch (scafPtr[j][k])
			{
			case RED:
				cout << 'R';
				break;
			case BLACK:
				cout << 'B';
				break;
			default:
				cout << ' ';
				break;
			}
		}
		cout << '|' << endl;
	}

	// Display the bottom of the scaffold
	for (int i = 0; i < m_Cols; i++)
	{
		cout << "+-";
	}
	cout << "+" << endl;
}

// If the first parameter is a valid column number with at least one vacant position in that column,
// and if color is RED or BLACK, drop a checker of the appropriate color into that column and return true.
// Otherwise, do nothing and return false.
bool ScaffoldImpl::makeMove(int column, int color)
{
	if (color != RED && color != BLACK)
		return false;

	// Loop starts at bottom level of the specified column and moves up until a vacant spot is found
	for (int i = m_Levels - 1; i >= 0; i--)
	{
		if (scafPtr[i][column - 1] == VACANT)	// Use "column - 1" because the user considers the column numbers to start at 1 instead of 0
		{
			// Add checker
			scafPtr[i][column - 1] = color;
			// Push the coordinate of the updated array element onto a stack (useful for undoing moves)
			moveStack.push(Coord(i, column - 1));
			return true;
		}
	}

	// No vacant spot found in the specified column
	return false;
}

// Undo the most recently made move that has not already been undone (i.e., remove the checker in the
// scaffold that was most recently added), and return the number of the column from which that checker was
// removed. If there are no checkers in the scaffold, do nothing and return 0.
int ScaffoldImpl::undoMove()
{
	if (!moveStack.empty())
	{
		scafPtr[moveStack.top().r()][moveStack.top().c()] = VACANT;
		int column = moveStack.top().c() + 1;
		moveStack.pop();
		return column;
	}
	else
		return 0;
}

//******************** Scaffold functions *******************************

// These functions simply delegate to ScaffoldImpl's functions.
// You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
