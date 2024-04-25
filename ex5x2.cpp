#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

bool inMas(vector<unsigned int> mas, int value){ //Проверка вхождения элемента в массив (вектор)
    for(int i = 0; i < mas.size(); i++){
        if(mas[i] == value) return true;
    }
    return false;
}

unsigned char* multidimensionalTurboCode(int T, int Nd, int N, unsigned char* C){
    int S = 1; //Шаг, с помощью которого будем брать элементы
    unsigned char* allIters = new unsigned char[Nd * N]; //Массив всех индексов
    int index = 0;
    vector<pair<int, int>> accIndexes; //вектор доступных индексов
    unsigned char* answer = new unsigned char[Nd * N];
    for(int i = 0; i < N; i++){ //преинициализируем вектор доступных индексов
        accIndexes.push_back(pair<int, int>(i, -1));
    }
    vector<unsigned int> inds; //временный вектор индексов
    for(int env = 0; env < Nd; env++){
        for(int i = 0; i < N; i++){
            accIndexes[i].second = accIndexes[i].first + S;
        }
        inds.push_back(accIndexes[0].first);
        inds.push_back(accIndexes[0].second);
        for(int i = 1; i < N; i++){
            if(!inMas(inds, accIndexes[i].first) and !inMas(inds, accIndexes[i].second)){
                inds.push_back(accIndexes[i].first);
                inds.push_back(accIndexes[i].second);
            }
        }
        for(int i = 0; i < N; i++) allIters[i + index] = inds[i];
        inds.clear();
        index += N;
        S *= T;
    }
    for(int i = 0; i < Nd * N; i++){ //Записываем ответ
        answer[i] = C[allIters[i]];
    }
    return answer;
}

int main()
{
    int T = 2, Nd = 3, N = 8;
    unsigned char* C = new unsigned char[N]{ 0, 0, 1, 1, 1, 0, 0, 1 };
    unsigned char* answer = multidimensionalTurboCode(T, Nd, N, C);
    for(int i = 0; i < Nd * N; i++){
        if(i % N == 0) cout << endl << (i / N) + 1 << ":" << endl;
        cout << (answer[i] == 1);
    }
    cout << endl;
}
