#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;

struct Cubic
{
	int weight;
	int value;

	bool operator<(Cubic Right) const {
		if (weight > Right.weight)return true;
		if (weight < Right.weight)return false;
		return false;
	}
};

struct lanecb
{
	int weight;
	int value;
	bool operator<(lanecb right) const {
		if (value < right.value)return true;
		if (value > right.value)return false;
		return false;
	}
};

priority_queue<Cubic>Cv;
priority_queue<lanecb>cq;
priority_queue<long long, vector<long long>, greater<long long>>bag;

int N;
int K;
long long Ans;

void input() {
	cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		int m = 0;
		int v = 0;
		cin >> m >> v;
		Cv.push({ m,v });
	}
	for (int i = 0; i < K; i++)
	{
		long long Num = 0;
		cin >> Num;
		bag.push(Num);
	}
}

int main() {

	input();
	// 가방 개수만큼 진행
	for (int i = 0; i < K; i++)
	{
		long long nowbag = bag.top();
		bag.pop();
		while (!Cv.empty()) {
			Cubic now = Cv.top();
			if (now.weight <= nowbag) {
				Cv.pop();
				cq.push({ now.weight, now.value });
			}
			else {
				break;
			}
		}
		if (cq.size() != 0) {
			lanecb fr = cq.top();
			Ans += fr.value;
			cq.pop();
		}
	}
	cout << Ans;

	return 0;
}