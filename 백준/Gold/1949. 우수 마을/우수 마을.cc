#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;


// dp[4][0] = 4 + dp[5][1] = 4;
// dp[4][1] = max(dp[5][1], dp[5][0]) = 5;
// dp[3][0] = 3 + dp[4][1] = 8(OXO)
// dp[3][1] = max(dp[4][1], dp[4][0]) = 5(XXO)
// dp[6][1] = max(dp[7][1], dp[7][0]) = 7
// dp[6][0] = 6 + dp[7][1] = 6
// 
// dp[2][0] = 20 + dp[3][1] + dp[6][1] = 20 + 5 + 7 = 32
// dp[2][1] = max(dp[3][1], dp[3][0]) + max(dp[6][1], max[6][0]) = 8 + 7 = 15
// dp[1][0] = 1 + dp[2][1] = 16
// dp[1][1] = max(dp[2][1], dp[2][0]) = 32

// 현재 마을이 우수마을이면 자신값과 다음 마을을 일반마을로 지정했을때의 값을 가져온다
// 현재 마을이 우수마을이 아니라면 자식 마을이 우수마을과 우수마을이 아닌값중에 큰 값을 가져온다

// 자식 마을 중에 탐색하여 가장 큰 인구수를 반환하는 값을 저장한다
// 재귀 함수를 쓰다가
// 가장 큰 값을 반환하는 리턴값을 가져온다

int N;
int citizen[10001];
int visited[10001];
int save[10001][2];
vector<int>route[10001];

void input() {

	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> citizen[i];
	}
	for (int i = 0; i < N-1; i++)
	{
		int fr, en = 0;
		cin >> fr >> en;
		route[fr].push_back(en);
		route[en].push_back(fr);
	}
}

int func(int now, int good) {

	int nowSum = 0;
	if (good)nowSum = citizen[now];
	visited[now] = 1;

	for (int i = 0; i < route[now].size(); i++)
	{
		// 이미 계산한 마을이라면 다시 가지 않는다
		if (visited[route[now][i]] == 1)continue;

		int childgood = save[route[now][i]][1];
		int childbad = save[route[now][i]][0];
		// now번째 마을이 우수마을일때
		// 자기 자신 마을의 시민수를 더한다
		if (good) {
			if (childbad != 0) {
				nowSum += childbad;
			}
			else {
				nowSum += func(route[now][i], 0);
			}
		}
		// now번째 마을이 우수마을이 아닐때
		// 자기 자신의 마을의 시민수를 더하지 않는다
		else {
			if (childgood != 0 && childbad != 0) {
				nowSum += max(childgood, childbad);
			}
			else {
				nowSum += max(func(route[now][i], 1), func(route[now][i], 0));

			}	
		}
	}
	if (good) {
		save[now][1] = nowSum;
	}
	else {
		save[now][0] = nowSum;
	}

	visited[now] = 0;
	return nowSum;
}

int main() {

	input();
	int Ans = max(func(1, 1), func(1, 0));
	cout << Ans;
	return 0;
}