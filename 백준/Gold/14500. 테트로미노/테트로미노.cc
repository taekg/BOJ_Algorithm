#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

int N, M;
int MAP[500][500];
int visited[500][500];
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
int Sum;
int Max;
// 뻐규모양 폴리오미노 따로 생각한다
int middle[8][8] = {
	{0,0,0,1,0,2,-1,1},
	{0,0,0,1,0,2,1,1},
	{0,0,-1,0,-2,0,-1,1},
	{0,0,-1,0,-2,0,-1,-1},
	{0,0,0,-1,0,-2,-1,-1},
	{0,0,0,-1,0,-2,1,-1},
	{0,0,1,0,2,0,1,1},
	{0,0,1,0,2,0,1,-1}
};

void Cntmiddle(int y, int x) {

	for (int i = 0; i < 8; i++)
	{
		int middleSum = 0;
		for (int j = 0; j < 8; j+=2)
		{
			int ny = y + middle[i][j];
			int nx = x + middle[i][j + 1];
			if (ny >= N || nx >= M || ny < 0 || nx < 0) {
				middleSum = 0;
				break;
			}
			middleSum += MAP[ny][nx];
		}
		Max = max(Max, middleSum);
	}
}

void init() {


}

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAP[i][j];
		}
	}
}

void func(int now,int y, int x) {

	if (now == 4) {
		Max = max(Max, Sum);
		return;
	}

	int nowy = y;
	int nowx = x;
	for (int d = 0; d < 4; d++)
	{
		int ny = nowy + dy[d];
		int nx = nowx + dx[d];
		if (visited[ny][nx] == 1)continue;
		if (ny >= N || nx >= M || ny < 0 || nx < 0)continue;
		visited[ny][nx] = 1;
		Sum += MAP[ny][nx];
		func(now + 1, ny, nx);
		visited[ny][nx] = 0;
		Sum -= MAP[ny][nx];
		visited[ny][nx] = 0;
	}

}

int main() {

	//freopen("sample_input.txt", "r", stdin);
	init();
	input();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			func(0,i,j);

			Cntmiddle(i, j);
		}
	}
	cout << Max;

	return 0;
}