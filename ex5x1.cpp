#include <iostream>
#include <math.h>
#include <vector>
#include <unordered_map>

using namespace std;

int generateNumberFromByte(vector<unsigned char> BYTE, int _size = 8) {
    int number = 0;
    for (int i = _size - 1; i >= 0; i--) {
        number += BYTE[i] * pow(2, _size - i - 1);
    }
    return number;
}

int _sum(unsigned char* A, int _size) {
    int su = 0;
    for (int i = 0; i < _size; i++) su += A[i];
    return su;
}

vector<int> generateRandomNumber(int n) {
    unsigned char* A = new unsigned char[n] {0};
    int controlSum = n % 8; //переменная, следящая за кратностью n
    vector<int> numbers;
    hash<unsigned char> hasher;
    int add = 1, __sum;
    for (int i = 1; i < n; i++) { //генератор случайных чисел
        __sum = _sum(A, n);
        if (__sum != 0) add = (__sum / i >> A[i - 1]);
        A[i] = ((hasher(clock()) * A[i - 1] * _sum(A, n) / i - add
            + ((clock()) ^ i + (A[i - 1] << i) * hasher(clock()) | A[i - 1]))) % 2;
    }
    vector<vector<unsigned char>> BYTES;
    vector<unsigned char> TIME_BYTE;
    int counter = 0;
    for (int i = 0; i < n; i++) { //Распределение случайных чисел по байтам
        TIME_BYTE.push_back(A[i]);
        counter++;
        if (counter == 8 || (i == n - 1 && controlSum != 0)) {
            BYTES.push_back(TIME_BYTE);
            TIME_BYTE.clear();
            counter = 0;
        }
    }
    for (vector<unsigned char> e : BYTES) {
        numbers.push_back(generateNumberFromByte(e, e.size()));
    }
    return numbers;
}

int main() {
    int n = 2;
    for (int j = 0; j < 1; j++) {
        vector<int> answer = generateRandomNumber(n);
        for (int i = 0; i < answer.size(); i++) cout << answer[i] << endl;
        cout << endl;
    }
}
