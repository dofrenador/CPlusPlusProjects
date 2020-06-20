#include "pa1-1.h"
#include <iostream>

using namespace std;

int main()
{
	bool flag = true;
	bool cond;
	MagicSquare* ms = nullptr;
	int input = 0;
	while (flag)
	{
		cout << "Enter an odd integer between 3 and 15: ";
		cin >> input;

		cond = cin.fail();
		cin.clear();
		cin.ignore(INT_MAX, '\n'); // get the correct input

		if (input % 2 == 1 && input >= 3 && input <= 15) // Restrict the input 3 to 15 with all odds.
		{

			ms = new MagicSquare(input);
			ms->generate();
			delete ms;

			cout << endl;
			cout << "Press 1 to try another value , 0 to quit: ";
			cin >> input;
			if (input != 1)
			{
				flag = false;
			}
		}

		else
		{
			cout << "Wrong input! " << endl;
		}

	}
	ms = nullptr;
	cout << "Goodbye! " << endl;
	system("pause");
	return 0;
}

MagicSquare::MagicSquare(int s)
{
	count = 1;
	size = s;
	matrix = new int*[s];
	for (int i = 0; i < s; ++i)
	{
		matrix[i] = new int[s];
		for (int j = 0; j < s; ++j)
		{
			matrix[i][j] = 0;
		}
	}
	siameseMethod();
}

MagicSquare::~MagicSquare()
{
	for (int i = 0; i < size; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}


void MagicSquare::generate() // generate the matrices
{
	int** second = reflectOX(matrix); //take the symmetry with respect to x
	int** third = reflectOY(matrix); //take the symmetry with respect to y
	int** forth = reflectOX(third);  //take the symmetry with respect to x then y

	int** fifth = reflectDiagonal(matrix); //take the symmetry with respect to diagonal or (take the transpose)
	int** sixth = reflectOX(fifth);  // take the transpose then take the symmetry with respect to x
	int** seventh = reflectOY(fifth);  //take the transpose then take the symmetry with respect to y
	int** eigth = reflectOY(sixth);  //transpose, x, and then y

									 //print the matrices
	print(matrix);
	print(second);
	print(third);
	print(forth);
	print(fifth);
	print(sixth);
	print(seventh);
	print(eigth);

	// n = 3 is a special case
	if (size > 3)
	{
		int** nineth = exchangeFirstLastSecondRows(matrix);
		int** tenth = reflectOX(nineth);
		print(nineth);
		print(tenth);
	}
	count = 1;
}

void MagicSquare::print(int** arr)
{
	//Magic Square #1 is:
	cout << "Magic Square #" << count << " is:" << endl;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	//print row sums
	cout << "Checking the sums of every row: ";
	for (int i = 0; i < size; ++i)
	{
		int sum = 0;
		for (int j = 0; j < size; ++j)
		{
			sum = sum + arr[i][j];
		}
		cout << sum << " ";
	}
	cout << endl;

	//print column sums
	cout << "Checking the sums of every column: ";
	for (int j = 0; j < size; ++j)
	{
		int sum = 0;
		for (int i = 0; i < size; ++i)
		{
			sum = sum + arr[i][j];
		}
		cout << sum << " ";
	}
	cout << endl;

	//print diagonal sums
	cout << "Checking the sums of every diagonal: ";
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum = sum + arr[i][i];
	}
	cout << sum << " ";

	sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum = sum + arr[i][i];
	}
	cout << sum;

	cout << endl;
	cout << endl;
	count++;
}



void MagicSquare::siameseMethod() // Apply the siamase method to compute magicsquares
{
	int x = 0;
	int y = (size - 1) / 2;
	matrix[x][y] = 1;

	for (int i = 2; i <= size * size; ++i)
	{
		int temp = x - 1;
		if (temp  <  0)
			temp = temp + size;

		if (matrix[temp][(y + 1) % size] == 0)
		{
			x = temp;
			y = (y + 1) % size;
		}

		else
		{
			x = (x + 1) % size;
		}
		matrix[x][y] = i;
	}

}


int** MagicSquare::reflectOX(int** arr) //method for taking symmetry with respect to x
{
	int** copy = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		copy[i] = new int[size];
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			copy[i][j] = arr[size - 1 - i][j];
		}
	}

	return copy;

}

int** MagicSquare::reflectOY(int** arr) // method for taking the symmetry with respect to y
{
	int** copy = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		copy[i] = new int[size];
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			copy[i][j] = arr[i][size - 1 - j];
		}
	}

	return copy;
}

int** MagicSquare::reflectDiagonal(int** arr) // method for taking the transpose
{
	int** copy = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		copy[i] = new int[size];
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = i; j < size; ++j)
		{
			copy[i][j] = arr[j][i];
			copy[j][i] = arr[i][j];
		}
	}
	return copy;
}


int** MagicSquare::exchangeFirstLastSecondRows(int** arr) // exchaning first and last second rows
{
	int** copy = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		copy[i] = new int[size];
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (i == 1)
			{
				copy[1][j] = arr[size - 2][j];
			}

			else if (i == size - 2)
			{
				copy[size - 2][j] = arr[1][j];
			}

			else
			{
				copy[i][j] = arr[i][j];
			}
		}
	}

	return copy;
}