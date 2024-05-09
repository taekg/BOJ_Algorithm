#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

int N;
int M;
vector<int>Arr;
int Ans = 21e8;
int btNum = 0;
int nowNum;
long long target;
int frNum;
bool isBreak = false;

void tp(int st, int en) {

    while (st <= en) {

        int mid = (st + en) / 2;
        if (Arr[mid] == target) {
            isBreak = true;
            break;
        }

        else if (Arr[mid] > target) {
            Ans = min(Ans, Arr[mid] - frNum);
            en = mid-1;
        }
        else {
            st = mid+1;
        }
    }
}

int main() {

    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        int Num = 0;
        cin >> Num;
        Arr.push_back(Num);
    }

    if (M == 0) {
        cout << M;
    }
    else {
        sort(Arr.begin(), Arr.end());

        // 벡터에서 하나씩 빼서 target을 설정하자
        for (int i = 0; i < Arr.size() - 1; i++)
        {
            frNum = Arr[i];
            target = frNum + M;
            tp(i + 1, N - 1);
            if (isBreak) {
                cout << M;
                break;
            }
        }
        if (!isBreak) {
            cout << Ans;
        }
    }

    return 0;
}