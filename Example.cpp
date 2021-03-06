#include<iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int M = 1002;
bool memo[M][M];
int a[M], b[M], c[2 * M], la, lb;

bool dfs(int x, int y, int z)
{
	if (z == la + lb - 1) return true;
	if (memo[x][y]) return false;
	memo[x][y] = true;
	if (a[x] == c[z] && x < la && dfs(x + 1, y, z + 1)) return true;
	if (b[y] == c[z] && y < lb && dfs(x, y + 1, z + 1)) return true;
	return false;
}

int main()
{
	while (cin >> la >> lb && !(la == 0 && lb == 0))
	{
		for (int i = 0; i < la; ++i) scanf_s("%d", &a[i]);
		for (int i = 0; i < lb; ++i) scanf_s("%d", &b[i]);
		for (int i = 0; i < la + lb; ++i) scanf_s("%d", &c[i]);
		memset(memo, false, sizeof(memo));
		if (dfs(0, 0, 0)) puts("possible");
		else puts("not possible");
	}
	return 0;
}