#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <random>

using namespace std;

struct Bacterium
{
    bool busy = false;
    int x;
    int y;
    int dayLife = 0;
    int dayOfAppearance = 0;
    bool alive = true;
};

pair<int, int> generateRandomCoords(int start=0, int end){
    return pair<int, int>(rand() % (end - start + 1) + start, rand() % (end - start + 1) + start);
}

int generateRandomVaue(int k1, int k2){
    return rand() % (k2 - k1 + 1) + k1;
}

bool propability(int chance){ //Вычисление вероятности
    if(0 <= rand() % 101 <= chance) return true;
    return false;
}

void LifeTimeOfBacterium(int N, int K1, int K2, int D, int T, int P){
    Bacterium ** field = new Bacterium*[N];
    int count = 0;
    pair<int, int> coords;
    Bacterium time;
    for(int day = 0; day < D; day++){
        count = generateRandomVaue(K1, K2);
        for(int b = 0; b < count; b++){
            coords = generateRandomCoords(0, N);
            if(!field[coords.first][coords.second].busy){ //Место не занято
                field[coords.first][coords.second].busy = true;
                field[coords.first][coords.second].x = coords.first;
                field[coords.first][coords.second].y = coords.second;
                field[coords.first][coords.second].dayOfAppearance = day;
            }
        }
        for(int x = 0; x < N; x++){
            for(int y = 0; y < N; y++){
                time = field[x][y];
                if(time.busy and time.dayOfAppearance <= day + 1 and time.dayLife < T and time.alive){
                    if(propability(P += 5)){
                        if(x - 1 >= 0 and !field[x - 1][y].busy){ 
                            field[x - 1][y].busy = true;
                            field[x - 1][y].x = x - 1;
                            field[x - 1][y].y = y;
                            field[x - 1][y].dayOfAppearance = day;
                        }
                        if(x + 1 < N and !field[x + 1][y].busy){
                            field[x + 1][y].busy = true;
                            field[x + 1][y].x = x + 1;
                            field[x + 1][y].y = y;
                            field[x + 1][y].dayOfAppearance = day;
                        }
                        if(y - 1 >= 0 and !field[x][y - 1].busy){ 
                            field[x][y - 1].busy = true;
                            field[x][y - 1].y = y - 1;
                            field[x][y - 1].x = x;
                            field[x][y - 1].dayOfAppearance = day;
                        }
                        if(y + 1 < N and !field[x][y + 1].busy){
                            field[x][y + 1].busy = true;
                            field[x][y + 1].y = y + 1;
                            field[x][y + 1].x = x;
                            field[x][y + 1].dayOfAppearance = day;
                        }
                        if(y + 1 < N and x + 1 < N and !field[x + 1][y + 1].busy){
                            field[x + 1][y + 1].busy = true;
                            field[x + 1][y + 1].y = y + 1;
                            field[x + 1][y + 1].x = x + 1;
                            field[x + 1][y + 1].dayOfAppearance = day;
                        }
                        if(y + 1 < N and x - 1 >= 0 and !field[x - 1][y + 1].busy){
                            field[x - 1][y + 1].busy = true;
                            field[x - 1][y + 1].y = y + 1;
                            field[x - 1][y + 1].x = x - 1;
                            field[x - 1][y + 1].dayOfAppearance = day;
                        }
                        if(y - 1 >= 0 and x - 1 >= 0 and !field[x - 1][y - 1].busy){
                            field[x - 1][y - 1].busy = true;
                            field[x - 1][y - 1].y = y - 1;
                            field[x - 1][y - 1].x = x - 1;
                            field[x - 1][y - 1].dayOfAppearance = day;
                        }
                        if(y - 1 >= 0 and x + 1 < N and !field[x + 1][y - 1].busy){
                            field[x + 1][y - 1].busy = true;
                            field[x + 1][y - 1].y = y - 1;
                            field[x + 1][y - 1].x = x + 1;
                            field[x + 1][y - 1].dayOfAppearance = day;
                        }
                    }
                    time.dayLife += 1;
                    if(time.dayLife > T / 2 and propability(P -= 2)) time.alive = false;
                }
            }
        }
    }
}

int main(){
    int N, K1, K2, D, T, P;

}
