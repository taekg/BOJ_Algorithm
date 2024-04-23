#define _CRT_SECURE_NO_WARNINGS
#include<queue>
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int N;
int M;
vector<int>v[32001];
int DAT[32001];

int main() {

	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int fr, en = 0;
		cin >> fr >> en;
		v[fr].push_back(en);
		DAT[en]++;
	}

	queue<int>q;

	// 앞에 있는 요소들은 미리 큐에 넣어버리자
	for (int i = 1; i <= N; i++)
	{
		if (DAT[i] == 0) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int now = q.front();
		q.pop();
		cout << now << " ";
		for (int i = 0; i < v[now].size(); i++)
		{
			DAT[v[now][i]]--;
			if (DAT[v[now][i]] == 0) {
				q.push(v[now][i]);
			}
		}
	}
	return 0;
}