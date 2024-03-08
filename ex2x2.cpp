#include <iostream>
#include <string>
#include <map>

using namespace std;

string to_lower(string raw, int _size) { //все char в нижний регистр
    for (int i = 0; i < _size; i++) {
        raw[i] = tolower(raw[i]);
    }
    return raw;
}

string to_first_upper(string& raw) { //первый элемент строки в верхний регистр
    string answer = "";
    answer += toupper(raw[0]);
    for (int i = 1; i < raw.size(); i++) answer += raw[i];
    return answer;
}

void split(string* &mas, int &_size, string raw, bool* &case_mas, map<string, string> &dictionary) { //split string with " "
    int index = 0;
    int finded = 0;
    while (raw.find(" ")) {
        if (index == _size) break;
        finded = raw.find(" ");
        mas[index] = raw.substr(0, finded);

        if (isupper(mas[index][0])) case_mas[index] = true;
        else case_mas[index] = false;
        //только если слово находится в словаре, заносим в нижний регистр:
        if (dictionary.count(to_lower(mas[index], mas[index].size())) != 0) {
            mas[index] = to_lower(mas[index], mas[index].size());
        }
        raw = raw.substr(finded + 1, raw.size());
        index++;
    }
}

string function22(string raw) {
    map<string, string> dictionary;
    dictionary["simultaneous"] = "одновременный";
    dictionary["action"] = "действие";
    dictionary["yes"] = "да";
    dictionary["no"] = "нет";
    int _size = count(raw.begin(), raw.end(), ' ') + 1; //Количество пробелов в строке
    string* mas = new string[_size];
    bool* case_mas = new bool[_size]{ false };
    split(mas, _size, raw, case_mas, dictionary);
    for (int i = 0; i < _size; i++) {
        if (dictionary.count(mas[i])) mas[i] = dictionary[mas[i]];
    }
    string answer = "";
    for (int i = 0; i < _size; i++) { 
        if (case_mas[i]) answer += to_first_upper(mas[i]) + " ";
        else answer += mas[i] + " ";
    }
    return answer;
}

int main() {
    setlocale(LC_ALL, "Russian");
    string a = "SimultAneoUs actIon FDSqA";
    cout << function22(a) << endl;
    return 0;
}
