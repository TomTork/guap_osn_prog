#include <iostream>
#include <string>
#include <vector>

using namespace std;

int* function2(int value) {
    if (value <= 0) return new int[1]{2};
    int* mas = new int[value * 2 + 1];
    for (int i = 0; i < value * 2 + 1; i++) {
        mas[i] = i;
    }
    for (int s = 2; s < value * 2 + 1; s++) { //Нахождение простых чисел с помощью решета Эратосфена
        if (mas[s] != 0) {
            for (int d = s * s; d < value * 2 + 1; d += s) {
                mas[d] = 0;
            }
        }
    }
    vector<int> simple;
    int first = 0;
    int second = 0;
    for (int i = 2; i < value * 2 + 1; i++) { //Группировка простых чисел в один массив
        if (mas[i] != 0) simple.push_back(mas[i]);
    }
    for (int i = 0; i < simple.size(); i++) { //Нахождение двух ближайших простых чисел
        if (simple[i] > value) { first = simple[i]; break; }
        else if(simple[i] != value) second = simple[i];
    }

    int* answer = new int[2] {second, first};
    return answer;
}



int main()
{
    //EX2=================================================
    int number;
    cin >> number;
    int* answer = function2(number);
    for (int index = 0; index < 2; index++) {
        if(answer[index] > 0) cout << answer[index] << endl;
    }
}
