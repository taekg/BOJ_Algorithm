#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

struct first {
	int size;
	int rainbow;
	int standY;
	int standX;
	int idx;

	bool operator<(first right) const {
		if (size > right.size)return true;
		if (size < right.size)return false;

		if (rainbow > right.rainbow)return true;
		if (rainbow < right.rainbow)return false;

		if (standY > right.standY)return true;
		if (standY < right.standY)return false;

		if (standX > right.standX)return true;
		if (standX < right.standX)return false;

		return false;
	}
};

struct pos {
	int y;
	int x;
	int block;
};
struct qpos {
	int y;
	int x;
};
vector<pos>v[400];
vector<first>find_first;
int N, M;
int MAP[20][20];
int visited[20][20];
int Nowvis[20][20];
int turnMAP[20][20];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int Score;
int breakFlag = 0;
int cpIdx;

void init() {
	memset(visited, 0, sizeof(visited));
	memset(MAP, 0, sizeof(MAP));
	find_first.clear();
	Score = 0;
	breakFlag = 0;
	cpIdx = -1;
}

void input() {

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}
}

void eraseMAP(int idx) {

	// 빈공간을 -2로 만들자
	if (breakFlag != 1) {
		int scCnt = 0;
		for (int i = 0; i < v[idx].size(); i++)
		{
			MAP[v[idx][i].y][v[idx][i].x] = -2;
			scCnt++;
		}
		Score += scCnt * scCnt;

		// 중력 적용

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N - 1; j++)
			{
				// 두 칸중에 하나라도 -1이면 바뀌지 않는다.
				if (MAP[j][i] == -1 || MAP[j + 1][i] == -1) {
					continue;
				}
				// 빈칸이고 컬러블록이면 둘이 바꾼다
				if (MAP[j + 1][i] == -2) {
					int temp = MAP[j + 1][i];
					MAP[j + 1][i] = MAP[j][i];
					MAP[j][i] = temp;
				}
				for (int k = N - 1; k > 0; k--)
				{
					if (MAP[k][i] == -1 || MAP[k - 1][i] == -1)continue;
					// 빈칸이고 컬러블록이면 둘이 바꾼다
					if (MAP[k][i] == -2) {
						int temp = MAP[k - 1][i];
						MAP[k - 1][i] = MAP[k][i];
						MAP[k][i] = temp;
					}
				}
			}
		}

		// 반시계로 90돌리자

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				turnMAP[i][j] = MAP[j][N - i - 1];
			}
		}

		// 중력 적용

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N - 1; j++)
			{
				// 두 칸중에 하나라도 -1이면 바뀌지 않는다.
				if (turnMAP[j][i] == -1 || turnMAP[j + 1][i] == -1) {
					continue;
				}
				// 빈칸이고 컬러블록이면 둘이 바꾼다
				if (turnMAP[j + 1][i] == -2) {
					int temp = turnMAP[j + 1][i];
					turnMAP[j + 1][i] = turnMAP[j][i];
					turnMAP[j][i] = temp;
				}
				for (int k = N - 1; k > 0; k--)
				{
					if (turnMAP[k][i] == -1 || turnMAP[k - 1][i] == -1)continue;
					// 빈칸이고 컬러블록이면 둘이 바꾼다
					if (turnMAP[k][i] == -2) {
						int temp = turnMAP[k - 1][i];
						turnMAP[k - 1][i] = turnMAP[k][i];
						turnMAP[k][i] = temp;
					}
				}
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				MAP[i][j] = turnMAP[i][j];
			}
		}

	}
	for (int i = 0; i < cpIdx; i++)
	{
		v[i].clear();
	}
}

void makegroup() {
	// 블록그룹을 어떻게 만들것인가?
	// 같은 숫자 1~M 까지
	// 방향벡터를 활용해서 만약 0이거나 같은 숫자이면 벡터에 넣자
	// 벡터가 다 만들어지면 블록그룹 우선순위를 만들자
	// 새로운 벡터를 생성하여 각 블록그룹의 사이즈, 무지개블록수, 기준블록의 위치를 저장한다
	int idx = 0;
	//v->clear();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			memset(Nowvis, 0, sizeof(Nowvis));
			if (visited[i][j] == 1)continue;
			if (MAP[i][j] == -1 || MAP[i][j] == -2) {
				visited[i][j] = 1;
				continue;
			}
			v[idx].push_back({ i,j,MAP[i][j] });
			Nowvis[i][j] = 1;
			if (MAP[i][j] != 0) {
				visited[i][j] = 1;
			}
			queue<qpos>q;
			q.push({ i,j });
			int color = MAP[i][j];
			while (!q.empty()) {
				qpos now = q.front();
				q.pop();
				for (int d = 0; d < 4; d++)
				{
					int ny = now.y + dy[d];
					int nx = now.x + dx[d];
					if (ny >= N || nx >= N || ny < 0 || nx < 0)continue;
					if (visited[ny][nx] == 1)continue;
					if (Nowvis[ny][nx] == 1)continue;
					if (MAP[ny][nx] >= 1 && MAP[ny][nx] <= M) {
						if (MAP[ny][nx] != color)continue;
					}
					if (MAP[ny][nx] == -1 || MAP[ny][nx] == -2) {
						visited[ny][nx] = 1;
						continue;
					}
					v[idx].push_back({ ny,nx,MAP[ny][nx] });
					if (MAP[ny][nx] != 0) {
						visited[ny][nx] = 1;
					}
					Nowvis[ny][nx] = 1;
					q.push({ ny,nx });
				}
			}
			idx++;
		}
	}

	memset(visited, 0, sizeof(visited));
	find_first.clear();
	// 블록 그룹의 우선순위를 판단하기 위해 first_find 벡터를 채운다
	for (int i = 0; i < idx; i++)
	{
		int size = 0;
		int rainbowCnt = 0;
		int stY = 21e8;
		int stX = 21e8;
		for (int j = 0; j < v[i].size(); j++)
		{
			size++;
			if (v[i][j].block == 0) {
				rainbowCnt++;
			}
			else {
				if (v[i][j].x < stX) {
					stX = v[i][j].x;
					if (v[i][j].y < stY) {
						stY = v[i][j].y;
					}
				}
			}
		}
		find_first.push_back({ size, rainbowCnt, stY, stX ,i });
	}

	cpIdx = idx;

	// 사이즈가 1인 블록들은 지운다
	// 블록 그룹이 아니기 때문에
	for (int i = 0; i < idx; i++)
	{
		if (find_first[i].size == 1 || find_first[i].standX==21e8) {
			find_first.erase(find_first.begin()+i, find_first.begin() + i+1);
			i--;
			idx--;
		}
	}
	// 블록 그룹의 우선순위를 정하자
	sort(find_first.begin(), find_first.end());
	if (idx == 0) {
		breakFlag = 1;
	}
	else {
		eraseMAP(find_first[0].idx);
	}
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	init();
	input();
	while (true) {
		if (breakFlag == 1)break;
		makegroup();
	}
	cout << Score;
	return 0;
}