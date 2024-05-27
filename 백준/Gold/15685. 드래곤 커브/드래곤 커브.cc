#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<deque>
#include<queue>

using namespace std;

int N;
int x, y, d, g;
int MAP[110][110];
int cnt;
int ansCnt;

int dy[4] = {0,-1,0,1};
int dx[4] = {1,0,-1,0};

deque<int>Aq;

void init() {
	memset(MAP, 0, sizeof(MAP));
	ansCnt = 0;
	cnt = 0;
	Aq.clear();
}

void solution() {

	MAP[y][x] = 1;

	Aq.push_back(d);

	for (int i = 0; i < g; i++)
	{
		deque<int>copyQ(Aq);
		int qsize = copyQ.size();
		for (int j = 0; j < qsize; j++)
		{
			int qBack = copyQ.back();
			copyQ.pop_back();
			Aq.push_back((qBack + 1) % 4);
		}
	}
	
	int qsize = Aq.size();
	for (int i = 0; i < qsize; i++)
	{
		int dir = Aq.front();
		Aq.pop_front();
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		
		MAP[ny][nx] = 1;
		y = ny;
		x = nx;
	}
}

int squareCheck() {

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			cnt = MAP[i][j] + MAP[i + 1][j] + MAP[i][j + 1] + MAP[i + 1][j + 1];
			if (cnt == 4) {
				ansCnt++;
				cnt = 0;
			}
		}
		cnt = 0;
	}
	return ansCnt;
}

int main()
{
	init();
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> x >> y >> d >> g;
		solution();
	}
	int Ans = squareCheck();
	cout << Ans;
	return 0;
}