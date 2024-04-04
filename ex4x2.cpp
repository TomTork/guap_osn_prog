#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

struct Item
{
    float volume = 0;
    float weight = 0;
};

typedef struct Basket
{
    float volume = 0;
    float weight = 0;
} basket;

int compare(const void *a, const void *b) {
  
    basket *basketA = (basket *)a;
    basket *basketB = (basket *)b;
  
    return (basketA->weight - basketB->weight);
}

Basket* func_placing_items_in_baskets(int& amount_items, Item* items, int& amount_basket, float& max_volume){
    Item time;
    Item* time_items = new Item[amount_items];
    Basket* in_all_baskets = new Basket[amount_basket * amount_items * amount_items];
    int index_baskets = 0;
    for(int i = 0; i < amount_items; i++){
        for(int j = i + 1; j < amount_items; j++){
            if(items[i].volume < items[j].volume && items[i].weight > items[j].weight){
                
                //поиск лучших значений
                Basket* time_baskets = new Basket[amount_basket];
                
                for(int z = 0; z < amount_items; z++) time_items[z] = items[z]; //Копирование во временный массив
                for(int index_item = 0; index_item < amount_items; index_item += amount_basket){
                    for(int d = 0; d < amount_basket; d++){
                        if(time_baskets[d].volume + time_items[index_item + d].volume <= max_volume){
                            time_baskets[d].volume += time_items[index_item + d].volume;
                            time_baskets[d].weight += time_items[index_item + d].weight;
                            time_items[index_item + d].volume = 0;
                            time_items[index_item + d].weight = 0;
                        }
                    }
                }
                qsort(time_baskets, amount_basket, sizeof(basket), compare); //сортировка по возрастанию массы
                for(int z = 0; z < amount_items; z++){
                    if(time_items[z].volume > 0){
                        for(int ti = 0; ti < amount_basket; ti++){
                            if(time_baskets[ti].volume + time_items[z].volume <= max_volume){
                                time_baskets[ti].volume += time_items[z].volume;
                                time_baskets[ti].weight += time_items[z].weight;
                                time_items[z].volume = 0;
                                time_items[z].weight = 0;
                            }
                        }
                    }
                }
                qsort(time_baskets, amount_basket, sizeof(basket), compare); //сортировка по возрастанию массы
                for(int z = 0; z < amount_basket; z++){
                    in_all_baskets[index_baskets] = time_baskets[z];
                    index_baskets++;
                }
                time = items[i];
                items[i] = items[j];
                items[j] = time;
                delete[] time_baskets;
                delete[] time_items;
            }
        }
    }
    //поиск лучших значений
    Basket* time_baskets = new Basket[amount_basket];
    for(int z = 0; z < amount_items; z++) time_items[z] = items[z]; //Копирование во временный массив
    for(int index_item = 0; index_item < amount_items; index_item += amount_basket){
        for(int d = 0; d < amount_basket; d++){
            if(time_baskets[d].volume + time_items[index_item + d].volume <= max_volume){
                time_baskets[d].volume += time_items[index_item + d].volume;
                time_baskets[d].weight += time_items[index_item + d].weight;
                time_items[index_item + d].volume = 0;
                time_items[index_item + d].weight = 0;
            } 
        }
    }
    qsort(time_baskets, amount_basket, sizeof(basket), compare); //сортировка по возрастанию массы
    for(int z = 0; z < amount_items; z++){
        if(time_items[z].volume > 0){
            for(int ti = 0; ti < amount_basket; ti++){
                if(time_baskets[ti].volume + time_items[z].volume <= max_volume){
                    time_baskets[ti].volume += time_items[z].volume;
                    time_baskets[ti].weight += time_items[z].weight;
                    time_items[z].volume = 0;
                    time_items[z].weight = 0;
                }
            }
        }
    }
    qsort(time_baskets, amount_basket, sizeof(basket), compare); //сортировка по возрастанию массы
    for(int z = 0; z < amount_basket; z++){
        in_all_baskets[index_baskets] = time_baskets[z];
        index_baskets++;
    }
    int* index_results = new int[amount_basket * amount_items * amount_items]{0};
    int index = 0;
    int raz = 0;
    int answer_raz = __INT32_MAX__;
    int result_index = 0;

    for(int i = 0; i < amount_basket * amount_items * amount_items; i += amount_basket){
        raz = 0;
        if(in_all_baskets[i].weight > 0 && in_all_baskets[i].volume > 0){
            for(int j = 0; j < amount_basket - 1; j++){
                raz += abs(in_all_baskets[i + j].weight - in_all_baskets[i + j + 1].weight);
            }
            if(raz != 0){
                index_results[index] = raz;
                index++;
            }
            else if(raz == 0){ //Найдено идеально усреднённое значение
                result_index = i;
                break;
            }
            else{
                if(answer_raz > raz){
                    answer_raz = raz;
                    result_index = i;
                }
            }
        }
        
        
    }
    Basket* result = new Basket[amount_basket];
    for(int i = 0; i < amount_basket; i++){
        result[i] = in_all_baskets[result_index + i];
    }
    return result;
}

int main()
{
    Item item;
    int N, K;
    float _volume, _weight, Vmax;
    cin >> N;
    Item* items = new Item[N];
    for(int i = 0; i < N; i++){
        cin >> _volume;
        cin >> _weight;
        
        item.volume = _volume;
        item.weight = _weight;
        items[i] = item;
    }
    cin >> K;
    cin >> Vmax;
    Basket* result = func_placing_items_in_baskets(N, items, K, Vmax);
    for(int i = 0; i < K; i++){
        cout << result[i].volume << " " << result[i].weight << endl;
    }
}
