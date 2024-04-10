#include <iostream>
#include <string>
#include <math.h>
#include <chrono>

using namespace std;

struct Object{
    float volume = 0;
    float weight = 0;
};

float searchMax(float* mas, int size){
    float ma = __FLT_MIN__;
    for(int i = 0; i < size; i++){
        if(mas[i] > ma) ma = mas[i];
    }
    return ma;
}

Object* funcPlacingItemsInBaskets(int N, Object* items, int K, float Vmax){
    Object* allIters = new Object[N * N * K];
    int globalIndex = 0;
    Object* iter = new Object[K];
    Object* timeMas = new Object[N];
    float* sumOfWeights = new float[N * N]{0};
    int globalIndex2 = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < K; k++) iter[k] = Object{0, 0};
            for(int r = 0; r < N; r++){
                timeMas[r] = items[r];
            }
            for(int z = 0; z < N; z++){
                for(int k = 0; k < K; k++){
                    if(iter[k].volume + timeMas[z].volume <= Vmax){
                        iter[k].volume += timeMas[z].volume;
                        iter[k].weight += timeMas[z].weight;
                        timeMas[z].volume = 0;
                        timeMas[z].weight = 0;
                    }
                }
            }
            for(int ind = 0; ind < N; ind++){
                for(int k = 0; k < k; k++){
                    if(iter[k].volume + timeMas[ind].volume <= Vmax){
                        iter[k].volume += timeMas[ind].volume;
                        iter[k].weight += timeMas[ind].weight;
                        timeMas[ind].volume = 0;
                        timeMas[ind].weight = 0;
                    }
                }
            }
            float sum = 0;
            for(int e = 0; e < K; e++){
                sum += iter[e].weight;
                allIters[globalIndex] = iter[e];
                globalIndex++;
            }
            swap(items[i], items[j]);
            sumOfWeights[globalIndex2] = sum;
            globalIndex2++;
        }
    }
    float maxSumOfWeights = searchMax(sumOfWeights, globalIndex2);
    Object* result = new Object[K];

    float resultRaz = __FLT_MAX__;
    for(int i = 0; i < globalIndex2; i++){
        if(sumOfWeights[i] == maxSumOfWeights){
            float raz = 0;
            for(int j = 0; j < K - 1; j++){
                raz += abs(allIters[j + i * K].weight - allIters[j + i * K + 1].weight);
            }
            if(raz < resultRaz){
                resultRaz = raz;
                for(int q = 0; q < K; q++){
                    result[q] = allIters[i * K + q];
                }
            }
        }
    }
    return result;
}


int main()
{
    Object item;
    int N, K;
    float _volume, _weight, Vmax;
    cin >> N;
    Object* items = new Object[N];
    for(int i = 0; i < N; i++){
        cin >> _volume;
        cin >> _weight;
        
        item.volume = _volume;
        item.weight = _weight;
        items[i] = item;
    }
    cin >> K;
    cin >> Vmax;
    auto begin = chrono::steady_clock::now();
    cout << ":ANSWER:" << endl;
    Object* result = funcPlacingItemsInBaskets(N, items, K, Vmax);
    auto end = chrono::steady_clock::now();
    cout << (chrono::duration_cast<chrono::milliseconds>(end - begin)).count() << endl;
    cout << endl;
    for(int i = 0; i < K; i++){
        cout << result[i].volume << " " << result[i].weight << endl;
    }
}
