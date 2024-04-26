#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;

// 무한 수열 A는 다음과 같다
// A0 = 1
// Ai = A⌊i/P⌋ + A⌊i/Q⌋ (i ≥ 1)
// N과 P가 주어질 때, An을 구하는 프로그램을 작성하시오


// A7 = A[7/2] + A[7/3] == 4+3 = 7
// A3 = A[3/2] + A[3/3] == A[1] + A[1] == 4
// A2 = A[2/2] + A[2/3] == A[1] + A[0] = 3

long long N;
long long P;
long long Q;
unordered_map<long long, long long>um;

long long func(long long Num) {

	if (Num == 0) {
		return 1;
	}
	if (um.count(Num)) {
		return um[Num];
	}
	um[Num]=func(Num / P) + func(Num / Q);
	return um[Num];
}

int main() {

	cin >> N >> P >> Q;
	long long ans = func(N);
	cout << ans;
	return 0;
}