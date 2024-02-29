#include <iostream>
#include <string>

using namespace std;

string function21(string value){
    bool sign = true; //По умолчанию +
    if(value[0] == '-'){
        sign = false;
        value = value.substr(1, value.size()); //Удаляем минус
    }
    unsigned char* mas = new unsigned char[value.size()] { '0' };
    string answer = "";
    for(int i = 0; i < value.size(); i++){
        switch (value[i])
        {
        case '1':
            mas[i + 1] = '2';
            break;
        case '2':
            mas[i + 1] = '4';
            break;
        case '3':
            mas[i + 1] = '6';
            break;
        case '4':
            mas[i + 1] = '8';
            break;
        case '5':
            mas[i + 1] = '0';
            mas[i] += 1;
            break;
        case '6':
            mas[i + 1] = '2';
            mas[i] += 1;
            break;
        case '7':
            mas[i + 1] = '4';
            mas[i] += 1;
            break;
        case '8':
            mas[i + 1] = '6';
            mas[i] += 1;
            break;
        case '9':
            mas[i + 1] = '8';
            mas[i] += 1;
            break;
        case '0':
            mas[i + 1] = '0';
            break;
        default:
            break;
        }
    }
    int startIndex = 0;
    if(mas[0] == '0') startIndex = 1; //Проверка на стартовый 0
    for(int i = startIndex; i <= value.size(); i++){
        answer += mas[i]; //Добавляем значения массива в ответ
    }
    if(!sign) return "-" + answer;
    return answer;
}

int main(){
    setlocale(LC_ALL, "Russian");
    cout << function21("-22000000000000008") << endl;
    return 0;
}
