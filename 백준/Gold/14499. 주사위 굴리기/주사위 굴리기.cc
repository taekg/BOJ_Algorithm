#define _NO_CRT_NO_SECURE
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

int N, M, X, Y, K;
int MAP[21][21];
int dy[4] = {1,-1,0,0};
int dx[4] = {0,0,-1,1};
int dir;
int dice[4][4] = {0,};

void init() {
	memset(MAP, 0, sizeof(MAP));
	memset(dice, 0, sizeof(dice));
}

int func(int x, int y, int dir) {


	// 주사위가 돌고 난 후
	//1. 맵에서 다음 위치가 0인지 아닌지 판단
	int ny = y + dy[dir - 1];
	int nx = x + dx[dir - 1];
	// 맵 바깥으로 이동하려고 하는 경우
	if (nx >= N || ny >= M || nx < 0 || ny < 0) {
		return -1;
	}
	else {
		// 주사위 배열 만들기
	// 맨 바닥에 해당하는 인덱스 dice(1,3), dice(3,1)
	// 그 후 주사위 돌리기
	// 동쪽으로 돌릴 때 
		if (dir == 1) {
			int temp = dice[1][3];
			for (int i = 2; i >= 0; i--)
			{
				dice[1][i + 1] = dice[1][i];
			}
			dice[1][0] = temp;
			dice[3][1] = dice[1][3];
		}
		// 서쪽으로 돌릴 때
		else if (dir == 2) {
			int temp = dice[1][0];
			for (int i = 0; i < 3; i++)
			{
				dice[1][i] = dice[1][i + 1];
			}
			dice[1][3] = temp;
			dice[3][1] = dice[1][3];
		}
		// 북쪽으로 돌릴 때
		else if (dir == 3) {
			int temp = dice[0][1];
			for (int i = 0; i < 3; i++)
			{
				dice[i][1] = dice[i + 1][1];
			}
			dice[3][1] = temp;
			dice[1][3] = dice[3][1];
		}
		// 남쪽으로 돌릴 때
		else {
			int temp = dice[3][1];
			for (int i = 2; i >= 0; i--)
			{
				dice[i + 1][1] = dice[i][1];
			}
			dice[0][1] = temp;
			dice[1][3] = dice[3][1];
		}
		X = nx;
		Y = ny;
		if (MAP[nx][ny] == 0) {
			// 주사위에서 칸으로 복사
			MAP[nx][ny] = dice[3][1];
			return dice[1][1];
		}
		else {
			// 칸에서 주사위로 복사
			dice[3][1] = MAP[nx][ny];
			dice[1][3] = MAP[nx][ny];
			// 칸은 0으로 바뀜
			MAP[nx][ny] = 0;
			return dice[1][1];
		}
	}
}

int main() {

	cin >> N >> M >> X >> Y >> K;
	init();

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAP[i][j];
		}
	}
	for (int i = 0; i < K; i++)
	{
		cin >> dir;
		int ans = func(X,Y,dir);
		// 맵 안에 있을때만 출력
		if (ans != -1) {
			cout << ans << endl;
		}
	}
	return 0;
}