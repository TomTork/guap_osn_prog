#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

unsigned char* generateRandomNumber(int n, vector<unsigned char> init){
    unsigned char* A = new unsigned char[n]{0};
    unsigned char a;
    unsigned char b;
    int indexInit = 0;
    for(int i = 1; i < n; i++){
        if(indexInit + 1 == init.size() - 1) indexInit = 0;
        A[i] = (init[indexInit] * A[i - 1] + init[indexInit + 1]) % 2;
        indexInit++;
    }
    return A;
}

int main(){
    int n = 22;
    vector<unsigned char> init = { 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1 };
    unsigned char* answer = generateRandomNumber(n, init);
    for(int i = 0; i < n; i++){
        if(answer[i] == 0) cout << 0 << endl;
        else cout << 1 << endl;
    }
}
