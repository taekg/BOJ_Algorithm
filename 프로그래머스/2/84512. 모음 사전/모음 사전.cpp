#include <string>
#include <vector>
#include <iostream>

using namespace std;

string answord="";
int Cnt;
int ans;
char Arr[5]={'A','E','I','O','U'};
bool Exit = false;


void func(string nowword){
    if(nowword == answord){
        //Exit = true;
        ans = Cnt;
        return;
    }
    
    for(int i =0;i<5;i++){
        if(nowword.length()>=5)continue;
        nowword.push_back(Arr[i]);
        Cnt++;
        func(nowword);
        //if(Exit == true)return;
        //Cnt--;
        nowword.pop_back();
    }
    
}

int solution(string word) {
    int answer = 0;
    answord = word;
    func("");
    
    return ans;
}