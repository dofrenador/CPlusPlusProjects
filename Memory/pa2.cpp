#include "pa2.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	
	// PageList p;
	// p.print();
	// cout << "\n" << endl;

	// p.addProgram("P0", 15);
	// p.addProgram("P1", 7);
	// p.print();
	
	bool cond;
	int input;
	PageList p;
	do // Print the menu
	{
		cout << "1. Add program" << endl;
		cout << "2. Kill program" << endl;
		cout << "3. Fragmentation" << endl;
		cout << "4. Print memory" << endl;
		cout << "5. Exit" << endl;

		cout << "choice - ";
		cin >> input;
		
	
		cond = cin.fail();
		cin.clear();
		cin.ignore(INT_MAX, '\n'); // get the correct input
		
		//CASES
		if (input == 1) // case 1
		{
			string str;
			int kb;
			cout << "Program name - ";
			cin >> str;
			cout << "Program size (KB) - ";
			cin >> kb;
			p.addProgram(str, kb);
		}

		else if (input == 2) //case 2
		{
			string str;
			cout << "Program name - ";
			cin >> str;
			p.killProgram(str);
		}

		else if (input == 3) //case 3
		{
			cout << "\nThere are " << p.calcFragmentation() << " fragment(s)." << endl;
		}

		else if (input == 4) //case 4
		{
			cout << endl;
			p.print();
		}	

		else if (input != 5)
		{
			cerr << "\nInvalid Input!" << endl;
		}
		cout << "\n" << endl;
	} while (input != 5);

	p.destroy();
	cout << "Goodbye " << endl;
	system("pause");
	return 0;
}

PageList::PageList()
{
	for (int i = 0; i < LENGTH; ++i)
	{
		insertBack("Free");
	}
}


PageList:: ~PageList()
{
	destroy();
}

void PageList::killProgram(const string& dataToKill)
{
	Node* ptr = first;
	int totalKilled = 0;
	//while (ptr->getData() != dataToKill) 
	while (ptr != nullptr)
	{
		if (ptr->getData() == dataToKill)
		{
			++totalKilled;
			ptr->setData("Free");
		}
		ptr = ptr->getNext();
	}

	if (totalKilled == 0)
		cerr << "Error, Program " << dataToKill <<
		" not found in the memory! " << endl;
	else
		cout << "Program " << dataToKill <<
		" successfully killed, " << totalKilled << " page(s) reclaimed." << endl;
}

void PageList::insertBack(const string& toInsert)
{
	if (first == nullptr)
		first = new Node(toInsert, nullptr);

	else
	{
		Node* temp = first;
		Node* prev = temp;
		while (temp != nullptr)
		{
			prev = temp;
			temp = temp->getNext();
		}
		temp = new Node(toInsert, nullptr);
		prev->setNext(temp);
	}
	++size;
}


void PageList::addProgram(const string& newData, int kb)
{
	Node* ptr = first;


	//CHECK IF PROGRAM IS ALREADY RUNNING
	while (ptr != nullptr)
	{
		if (ptr->getData() == newData)
		{
			cerr << "Error, Program " << newData << " already running." << endl;
			return;
		}
		ptr = ptr->getNext();
	}
	ptr = first;

	int pos = findLastNonFree();
	int pages = kb / 4;
	if (kb % 4 != 0)
		++pages;

	//CHECK IF THERE IS ENOUGH SPACE IN THE MEMORY
	if (pos + pages >= LENGTH)
	{
		cerr << "Error, Not enough memory for Program " << newData << endl;
		return;
	}

	for (int i = 0; i < pos; ++i)
		ptr = ptr->getNext();

	if (pos != 0)
		ptr = ptr->getNext();

	for (int i = 0; i < pages && ptr != nullptr; ++i)
	{
		ptr->setData(newData);
		ptr = ptr->getNext();
	}
	cout << "\nProgram " << newData << " added successfully : "
		<< pages << " page(s) used." << endl;

}

int PageList::calcFragmentation() const
{
	Node* nextPtr = first;
	Node* prevPtr = first;
	int sum = 0;
	while (nextPtr != nullptr)
	{
		if ((nextPtr->getData() != prevPtr->getData()) &&
			(nextPtr->getData() == "Free" || prevPtr->getData() == "Free"))
			//nextPtr->getData() == "Free" )
		{
			if (nextPtr->getData() == "Free")
				++sum;
			prevPtr = nextPtr;
		}
		nextPtr = nextPtr->getNext();
	}
	return sum;
}


int PageList::findLastNonFree() const
{
	int pos = 0;
	int  i = 0;
	Node* ptr = first;
	while (ptr != nullptr)
	{
		if (ptr->getData() != "Free")
			pos = i;

		ptr = ptr->getNext();
		++i;
	}
	return pos;
}

void PageList::print() const
{
	Node* temp = first;
	int i = 0;
	while (temp != nullptr)
	{
		cout << temp->getData() << "\t";
		if (i % 8 == 7)
			cout << endl;
		++i;
		temp = temp->getNext();
	}
}

void PageList::destroy()
{
	Node* temp = first;
	Node* prev = first;

	while (temp != nullptr)
	{
		prev = temp;
		temp = temp->getNext();
		delete prev;
	}
}