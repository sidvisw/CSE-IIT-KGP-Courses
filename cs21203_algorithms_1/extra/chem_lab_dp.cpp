#include <iostream>
using namespace std;

int main(){
	// IO:
	cout << "Enter N and C:" << endl;
	int N, C;
	cin >> N;
	cin >> C;

	float **e_matrix = new float*[N];
	for (int i = 0; i<N; i++){
		e_matrix[i]=new float[C];
	}

	for (int i = 0; i<N; i++){
		for (int j = 0; j < C; j++)
		{
			cin >> e_matrix[i][j];
		}
	}

	cout << "N: " << N << " C: " << C << endl;
	cout << "E:\n";
	for (int i = 0; i<N; i++){
		for (int j = 0; j < C; j++)
		{
			cout << e_matrix[i][j] << "\t";
		}
		cout << endl;
	}

	// SOLUTION: using tabulation
	float **dp = new float*[N];
	for (int i = 0; i<N; i++){
		dp[i]=new float[C+1];
	}

	int **comp = new int*[N];
	for (int i = 0; i<N; i++){
		comp[i]=new int[C+1];
	}

	// init
	for (int r = 1; r <= N; r++)
	{
		// not enough catalyst
		dp[r-1][0] = 0;
		comp[r-1][0] = 0;
		for (int c = 1; c < r; c++)
		{
			dp[r-1][c] = 0;
		}

		if (r > 1)
		{
			// just enough catalyst
			dp[r-1][r] = dp[r-2][r-1]*e_matrix[r-1][0];
			comp[r-1][r] = 1;
		}
		else
			// only one reaction
			for (int c = 1; c < C+1; c++)
			{
				dp[0][c] = e_matrix[0][c-1];
				comp[0][c] = c;
			}
	}


	for (int r = 2; r <= N; r++)
	{
		for (int c=r+1; c<=C; c++)
		{
			// solving for dp[r-1][c]
			float s_max = 0.0;
			int zmax = 0;
			// how much we assign to reaction r
			for (int z=1; z<=c-r; z++)
			{
				float solve = dp[r-2][c-z]*e_matrix[r-1][z-1];
				if (solve > s_max)
				{
					s_max = solve;
					zmax = z;
				}
			}

			dp[r-1][c] = s_max;
			comp[r-1][c] = zmax;
		}
	}

	cout << endl << "output.txt" << endl;

	cout << dp[N-1][C] << endl;

	int left = C;
	for (int r = N; r >= 1; r--)
	{
		int z = comp[r-1][left];
		cout << "reaction " << (r) << ": " << z << endl;
		left -= z;
	}


	return 0;
}