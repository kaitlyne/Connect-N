// Player.cpp

#include "provided.h"
#include "support.h"
#include <string>
#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

//========================================================================
// Timer t;                 // create a timer and start it
// t.start();               // start the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#include <chrono>

class Timer
{
public:
	Timer()
	{
		start();
	}
	void start()
	{
		m_time = std::chrono::high_resolution_clock::now();
	}
	double elapsed() const
	{
		std::chrono::duration<double, std::milli> diff =
			std::chrono::high_resolution_clock::now() - m_time;
		return diff.count();
	}
private:
	std::chrono::high_resolution_clock::time_point m_time;
};

// CLASS DECLARATIONS
class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
	virtual bool isInteractive() const;
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
private:
	struct columnResult
	{
		int m_column;
		int m_result;
	};
	columnResult determineBestComputerMove(Scaffold& s_copy, int N, int color, int otherColor, bool isComputer);
};


// IMPLEMENTATIONS
int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
	int column;
	cout << "Enter a column number:";
	cin >> column;

	// Prompt the human for valid input: Column must be within range, and column must not be full
	while (column <= 0 || column > s.cols() || s.checkerAt(column, s.levels()) != VACANT)
	{
		if (column <= 0 || column > s.cols())
			cout << "Column number is out of range. Try another one: ";
		else if (s.checkerAt(column, s.levels()) != VACANT)
			cout << "Column is already full. Try another one: ";
		cin >> column;
	}
	return column;
}

bool HumanPlayerImpl::isInteractive() const
{
	return true;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
	// Choose the leftmost column that isn't full
	for (int i = 0; i < s.cols(); i++)
	{
		if (s.checkerAt(i + 1, s.levels()) == VACANT)
			return (i + 1);
	}

	// All columns are full
	return -1;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
	Timer timer;
	timer.start();
	if (s.numberEmpty() == s.cols()*s.levels())
	{
		if (s.cols() == s.levels() && s.cols() == N)
			return 1;
		else
			return (s.cols() / 2 + 1);
	}
	Scaffold temp_s = s;
	int otherColor = 10;
	switch (color)
	{
	case RED:
		otherColor = BLACK;
		break;
	case BLACK:
		otherColor = RED;
		break;
	default:
		return -1;
	}
	int chosenMove = determineBestComputerMove(temp_s, N, color, otherColor, true).m_column;
	cerr << timer.elapsed() << " milliseconds" << endl;
	return chosenMove;
}

SmartPlayerImpl::columnResult SmartPlayerImpl::determineBestComputerMove(Scaffold& s_copy, int N, int color, int otherColor, bool isComputer)
{
	int potentialWinner;
	columnResult bestResult;
	if (isComputer)
	{
		bestResult.m_result = INT_MIN;
	}
	else
	{
		bestResult.m_result = INT_MAX;
	}
	for (int i = 1; i <= s_copy.cols(); i++)	// Traverse columns
	{
		bool moveMade;
		if (isComputer)
		{
			moveMade = s_copy.makeMove(i, color);
		}
		else
		{
			moveMade = s_copy.makeMove(i, otherColor);
		}

		if (moveMade)
		{
			columnResult result;
			if (gameOver(potentialWinner, s_copy, N))	// Base case: Game is over. Someone won, or no more vacant spots left
			{

				if (potentialWinner == color)
				{
					result.m_result = s_copy.numberEmpty() + 1;
				}
				else if (potentialWinner == otherColor)
				{
					result.m_result = -1 * (s_copy.numberEmpty() + 1);
				}
				else
				{
					result.m_result = 0;
				}
			}
			else
			{
				result = determineBestComputerMove(s_copy, N, color, otherColor, !isComputer);
			}
			if (isComputer && (result.m_result > bestResult.m_result))
			{
				bestResult.m_column = i;
				bestResult.m_result = result.m_result;
			}
			else if (!isComputer && (result.m_result < bestResult.m_result))
			{
				bestResult.m_column = i;
				bestResult.m_result = result.m_result;
			}
			s_copy.undoMove();
		}
	}

	return bestResult;
}

//******************** Player derived class functions *************************

// These functions simply delegate to the Impl classes' functions.
// You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
