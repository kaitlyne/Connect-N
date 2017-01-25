// main.cpp

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	//BadPlayer bp1("Kaitlyne");
	//BadPlayer bp2("Michael");
	//Game g1(5, 3, 3, &bp1, &bp2);
	//g1.play();

	//HumanPlayer hp1("Kaitlyne");
	//BadPlayer bp3("Computer");
	//Game g2(5, 4, 3, &hp1, &bp3);
	//g2.play();

	//HumanPlayer hp2("Kaitlyne");
	//HumanPlayer hp3("Michael");
	//Game g3(3, 3, 3, &hp2, &hp3);
	//g3.play();

	SmartPlayer sp1("Computer");
	HumanPlayer hp("Kaitlyne");
	Game g4(4, 3, 3, &sp1, &hp);
	g4.play();

	//string name;
	//cout << "What's your name?  ";
	//getline(cin, name);
	//HumanPlayer hp(name);
	//SmartPlayer sp("Computer");
	//Game g1(4, 3, 3, &hp, &sp);
	//g1.play();
	//cout << endl << "This time I'll go first." << endl;
	//Game g2(4, 3, 3, &sp, &hp);
	//g2.play();
}
