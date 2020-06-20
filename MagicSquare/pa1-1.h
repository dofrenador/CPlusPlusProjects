
class MagicSquare
{
public:
	MagicSquare(int);
	~MagicSquare();
	void generate();

private:
	int size;
	int count;
	int** matrix;

	void siameseMethod();
	void print(int**);
	int** reflectOX(int**);
	int** reflectOY(int**);
	int** reflectDiagonal(int**);
	int**  exchangeFirstLastSecondRows(int**);

};
