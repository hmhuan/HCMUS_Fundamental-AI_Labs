#include "Lib.h"

int main(int argc, char * argv[]) {
	int **matrix, n;
	cell s, g;
	fstream fIn, fOut;

	fIn.open(argv[1], ios_base::in);
	fOut.open(argv[2], ios_base::out);
	fIn >> n >> s.x >> s.y >> g.x >> g.y;
	matrix = new int*[n];
	
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			fIn >> matrix[i][j];

	ASS(fOut, matrix, n , s, g);
	fIn.close();
	fOut.close();

	delete[]matrix;
	return 0;
}