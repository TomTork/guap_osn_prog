#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

bool issimple(int n){
    for(int i = 2; i < sqrt(n) + 1; i++){
        if(n % i == 0) return false;
    }
    return true;
}

int search_index_nearest_prime_number(int*& mas, int _size, int currentIndex, int step, int deep = 0){
    if(currentIndex < 0 or currentIndex >= _size) return -1;
    else if(issimple(mas[currentIndex])) {cout << "DEEP " << deep << endl; return currentIndex;}
    return search_index_nearest_prime_number(mas, _size, currentIndex + step, step, deep + 1);
}

int answer(int*& mas, int _size, int index){
    int m1 = search_index_nearest_prime_number(mas, _size, index, 1);
    int m2 = search_index_nearest_prime_number(mas, _size, index, -1);
    if(m1 == -1 and m2 != -1) return m2;
    else if(m2 == -1 and m1 != -1) return m1;
    else if(m1 != -1 and m2 != -1){
        int b1 = abs(index - m1);
        int b2 = abs(index - m2);
        if(b1 <= b2) return m1;
        return m2;
    }
    return -1;
}

int main()
{
    
    int* mas = new int[9]{ 3, 21, 35, 7, 31, 4, 4, 8, 7 };
    cout << "RESULT:" << answer(mas, 9, 6) << endl;
}
