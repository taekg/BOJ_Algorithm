#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

int N;
int ans;

int func(int Num) {

	int Cnt = 0;
	int totalAns = 0;
	if (Num == 2) {
		return 3;
	}
	if (Num == 0) {
		return 1;
	}
	for (int i = Num-2; i >=0 ; i-=2)
	{
		if (i == Num - 2) {
			Cnt = 3 * func(i);
		}
		else {
			Cnt = 2 * func(i);
		}
		totalAns += Cnt;
	}
	return totalAns;
}

int main() {

	cin >> N;
	if (N % 2 == 1) {
		cout << 0;
	}
	else {
		// 규칙을 찾은 결과 
		//f(N) = f(N-2)*3 + f(N-4)*2 + ... + f(0)*2
		int Ans = func(N);
		cout << Ans;
	}
	return 0;
}