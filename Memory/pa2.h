#include <string>
#include <iostream>
using namespace std;


class Node
{
private:
	string data;
	Node* next;
public:
	Node()
	{
		data = "Free";
		next = nullptr;
	}
	~Node() {}

	Node(string newData, Node* ptrNext)
	{
		data = newData;
		next = ptrNext;
	}

	void setData(string newData)
	{
		data = newData;
	}

	string getData() const
	{
		return data;
	}
	Node* getNext() const
	{
		return next;
	}

	void setNext(Node* ptr)
	{
		next = ptr;
	}

};


class PageList
{
private:
	const int LENGTH = 32;
	int size;
	Node* first;
	int findLastNonFree() const;

public:
	PageList();
	~PageList();

	void destroy();
	void killProgram(const string& dataToKill);
	void insertBack(const string& toInsert);
	void addProgram(const string& newData, int kb);

	int calcFragmentation() const;

	void print() const;
};