#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>

using namespace std;

struct peg
{
	string pegName;
	vector<int>diskStack;
};

void loadDisks(int numDisks, peg& startPeg);

void printPeg(peg startPeg, peg tempPeg, peg goalPeg);

int hanoi(int numDisks, peg &startPeg, peg &tempPeg, peg &goalPeg);

void moveDisk(peg& startPeg, peg& goalPeg);

int main()
{
	int numDisks = 7;
	peg startPeg;
	peg tempPeg;
	peg goalPeg;

	startPeg.pegName = "Peg1";
	tempPeg.pegName = "Peg2";
	goalPeg.pegName = "Peg3";

	loadDisks(numDisks, startPeg); //load disks onto start peg

	cout << "Starting condition of the pegs:" << endl;  // print starting position
	printPeg(startPeg, tempPeg, goalPeg);

	cout << endl << endl;

	cout << "A stack of " << numDisks << " disks can be transferred in "    // prints each move, then the total amount of moves needed
		<< hanoi(numDisks, startPeg, tempPeg, goalPeg) << " moves" << endl << endl << endl;

	cout << "Ending condition of the pegs:" << endl; // prints ending condition of the pegs
	printPeg(startPeg, tempPeg, goalPeg);
}

void loadDisks(int numDisks, peg& startPeg)
{
	for (int i = numDisks; i > 0; i--)
	{
		startPeg.diskStack.push_back(i);    // loads disks onto starting peg
	}
}

void printPeg(peg startPeg, peg tempPeg, peg goalPeg)
{
	cout << startPeg.pegName << " has " << startPeg.diskStack.size() << " disks:";  // prints out number of disks on peg
	for (int j : startPeg.diskStack)
	{
		cout << j;    // prints out which disks are on the peg  (repeats for each peg below)
	}
	cout << endl;

	cout << tempPeg.pegName << " has " << tempPeg.diskStack.size() << " disks:";
	for (int k : tempPeg.diskStack)
	{
		cout << k;
	}
	cout << endl;

	cout << goalPeg.pegName << " has " << goalPeg.diskStack.size() << " disks:";
	for (int l : goalPeg.diskStack)
	{
		cout << l;
	}
	cout << endl;
}

int hanoi(int numDisks, peg &startPeg, peg &tempPeg, peg &goalPeg)
{
	int counter = 0;

	if (numDisks > 0)
	{
		counter = hanoi(numDisks - 1, startPeg, goalPeg, tempPeg); // move n-1 disks
		moveDisk(startPeg, goalPeg);   // move bottom disk
		counter++;   
		counter += hanoi(numDisks - 1, tempPeg, startPeg, goalPeg); // move remaining disks from temp peg to goal peg
	}

	return counter;
}

void moveDisk(peg& startPeg, peg& goalPeg)
{
	int movingDisk = 0;
	
		movingDisk = startPeg.diskStack.back();  // assigns movingDisk to the top of the peg we are moving disks from
	
		if (goalPeg.diskStack.size() > 0)
		{
			assert(movingDisk < goalPeg.diskStack.back()); // this enforces the rule that we can't put a tile onto a tile
		}												  // that is smaller than it, but we can't use the back() func
													  // on an empty vector so I used the if statement to protect against that case
	
	startPeg.diskStack.pop_back();   // removes top disk from the peg
	goalPeg.diskStack.push_back(movingDisk);  // puts the disk from the previous peg onto the next peg

	cout << "Moved disk " << movingDisk << " from " << startPeg.pegName << " to " << goalPeg.pegName << endl;  // prints out each move
}
