#pragma once
#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<stack>
#include <functional>

using namespace std;

struct cell {
	int x, y;
	double f, g, h;

	bool operator<(const cell& rhs) const {
		return (f < rhs.f);
	}
	bool operator> (const cell& rhs) const {
		return (f > rhs.f);
	}
};

bool inBounds(int n, int x, int y) {
	return (x >= 0) && (x < n) && (y >= 0) && (y < n);
}

double h(int x, int y, cell g) {
	return (double)sqrt((x - g.x)*(x - g.x) + (y - g.y)*(y - g.y));
}

void ASS(fstream &fOut, int **&grid, int &n, cell &s, cell &g) {

	priority_queue<cell, vector<cell>, greater<cell>> pQ;
	int dx[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	int dy[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	//check
	if (!inBounds(n, s.x, s.y) || !inBounds(n, g.x, g.y) || grid[s.x][s.y] == 1 || grid[g.x][g.y] == 1)
	{
		fOut << -1;
		return;
	}

	bool **closedList;
	closedList = new bool*[n];
	for (int i = 0; i<n; i++) {
		closedList[i] = new bool[n];
		memset(closedList[i], false, sizeof(bool)*n);
	}

	vector<vector<double>> H(n); //Create Heuristic
	vector<vector<pair<double, pair<int, int>>>> Pa(n); //Create Parent of cell
	bool check = false;

	for (int i = 0; i<n; i++)
	{
		H[i] = vector<double>(n);
		Pa[i] = vector<pair<double, pair<int, int>>>(n);
		for (int j = 0; j < n; j++)
		{
			if (grid[i][j] != 1)
				H[i][j] = h(i, j, g);
			Pa[i][j].first = FLT_MAX; Pa[i][j].second = make_pair(-1, -1);
		}
	}
	s.g = 0.0; s.f = 0.0;
	Pa[s.x][s.y].first = 0.0;
	pQ.push(s);

	while (!pQ.empty())
	{
		cell q = pQ.top();
		pQ.pop();
		closedList[q.x][q.y] = true;
		for (int i = 0; i<8; i++)
			if (inBounds(n, q.x + dx[i], q.y + dy[i]))//check p in bounds
			{
				cell p;
				p.x = q.x + dx[i];
				p.y = q.y + dy[i];

				if (p.x == g.x && p.y == g.y) //check p is Goal
				{
					Pa[p.x][p.y].second = make_pair(q.x, q.y); //
					Pa[p.x][p.y].first = q.g + p.h;

					check = true;

					int u = g.x, v = g.y, temp;
					stack<pair<int, int>> S;
					pair<int, int> t;
					vector<vector<char>> map(n);

					S.push(make_pair(g.x, g.y));
					for (int i = 0; i < n; i++)
					{
						map[i] = vector<char>(n);
						for (int j = 0; j < n; j++)
							if (grid[i][j] == 0)
								map[i][j] = '-';
							else
								map[i][j] = 'o';
					}

					while (u != s.x || v != s.y)
					{
						temp = u;
						u = Pa[u][v].second.first;
						v = Pa[temp][v].second.second;
						S.push(make_pair(u, v));
					}
					fOut << S.size() << "\n";
					while (!S.empty()) {
						t = S.top();
						//printf("(%d,%d) ", t.first, t.second);
						fOut << "(" << t.first << "," << t.second << ") ";
						map[t.first][t.second] = 'x';
						S.pop();
					}
					map[s.x][s.y] = 'S'; map[g.x][g.y] = 'G'; //Set map[Start] = 'S', map[Goal] = 'G'
					for (int i = 0; i < n; i++)
					{
						fOut << "\n";
						for (int j = 0; j < n; j++)
							fOut << map[i][j] << " ";
					}
					return;
				}
				else if (closedList[p.x][p.y] == false && grid[p.x][p.y] == 0) //p not in closedList and p == 0
				{
					//update cell p
					p.g = q.g + 1.0; p.h = H[p.x][p.y];
					p.f = p.g + p.h;

					if (Pa[p.x][p.y].first == FLT_MAX || Pa[p.x][p.y].first > p.f)
					{
						Pa[p.x][p.y].first = p.f;
						Pa[p.x][p.y].second = make_pair(q.x, q.y);
						pQ.push(p);
					}
				}
			}
	}
	if (check == false)
	{
		fOut << -1;
		printf("-1");
	}

	delete[] closedList;
}