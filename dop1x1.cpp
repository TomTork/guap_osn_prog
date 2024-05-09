#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Bacterium
{
    bool busy = false;
    int dayLife = 0;
    int dayOfAppearance = 0;
    bool alive = true;
};

int generateRandomVaue(int k1, int k2){ //Генерация случайного числа в диапозоне
    return rand() % (k2 - k1 + 1) + k1;
}

pair<int, int> generateRandomCoords(int start=0, int end=0){
    return pair<int, int>(rand() % (end - start + 1) + start, rand() % (end - start + 1) + start);
}

bool propability(int chance){ //Вычисление вероятности
    if(0 <= rand() % 101 <= chance) return true;
    return false;
}

bool controlSum(Bacterium** field, int N, int breakIter){
    int cs = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(field[i][j].busy) cs += 1;
        }
    }
    if(cs == breakIter) return true;
    return false;
}

int LifeTimeOfBacterium(int N, int K1, int K2, int D, int T, int P){
    Bacterium ** field = new Bacterium*[N];
    for(int i = 0; i < N; i++) field[i] = new Bacterium[N];
    int iter = 0;
    int breakIter = N * N;
    int day = 0;
    int k; //Параметр для появления случайного числа бактерий
    pair<int, int> randomCoords;
    int i, j;
    int answerDay = -1;
    while (true){
        if(iter == breakIter) break;
        if(day < D){
            k = generateRandomVaue(K1, K2);
            for(i = 0; i < k; i++){
                randomCoords = generateRandomCoords(0, N - 1);
                if(!field[randomCoords.first][randomCoords.second].busy){ //Если ячейка не занята
                    field[randomCoords.first][randomCoords.second] = Bacterium { true, 0, day, true };
                }
            }
            day++;
        }
        if(controlSum(field, N, breakIter)){ answerDay = iter; break; }
        for(i = 0; i < N; i++){
            for(j = 0; j < N; j++){
                if(field[i][j].busy && field[i][j].alive && field[i][j].dayOfAppearance <= day + 1 && field[i][j].dayLife < T){
                    if(field[i][j].alive) field[i][j].dayLife += 1;
                    if(field[i][j].alive && field[i][j].dayLife > T / 2){
                        if(propability(P)){
                            field[i][j].alive = false;
                        }
                        P -= 2;
                    }
                    if(i - 1 >= 0 && !field[i - 1][j].busy && propability(P)) field[i - 1][j] = Bacterium { true, 0, day, true };
                    if(i + 1 < N && !field[i + 1][j].busy && propability(P)) field[i + 1][j] = Bacterium { true, 0, day, true };
                    if(j - 1 >= 0 && !field[i][j - 1].busy && propability(P)) field[i][j - 1] = Bacterium { true, 0, day, true };
                    if(j + 1 < N && !field[i][j + 1].busy && propability(P)) field[i][j + 1] = Bacterium { true, 0, day, true };
                    if(j + 1 < N && i + 1 < N && !field[i + 1][j + 1].busy && propability(P)) field[i + 1][j + 1] = Bacterium { true, 0, day, true };
                    if(i + 1 < N && j - 1 >= 0 && !field[i + 1][j - 1].busy && propability(P)) field[i + 1][j - 1] = Bacterium { true, 0, day, true };
                    if(i - 1 >= 0 && j + 1 < N && !field[i - 1][j + 1].busy && propability(P)) field[i - 1][j + 1] = Bacterium { true, 0, day, true };
                    if(i - 1 >= 0 && j - 1 >= 0 && !field[i - 1][j - 1].busy && propability(P)) field[i - 1][j - 1] = Bacterium { true, 0, day, true };
                    P += 5;
                }
                
            }
        }
        iter++;
    }
    return answerDay;
}


int main(){
    srand(time(NULL)); //seed случайного числа
    int answerDay;
    int a = 0;
    for(int i = 0; i < 1000; i++){
        answerDay = LifeTimeOfBacterium(500, 1, 1, 7, 14, 5);
        if(answerDay == -1) { cout << "true" << endl; a += 1; }
    }
    cout << endl;
    cout << endl;
    cout << a << endl;
}
