#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void split(int* &mas, int _size, string row, string sep, int len_sep = 2) { //split входящей строки
    int index = 0;
    string row2 = row;
    int finded = 0;
    while (row.find(sep)) {
        if (index == _size) break;
        finded = row.find(sep);
        mas[index] = stoi(row.substr(0, finded));
        row = row.substr(finded + len_sep, row.size());
        index++;
    }
}

bool isSimple(int value) { //Проверка на простое число
    if (value < 2) return false;
    if (value == 2) return true;
    for (int i = 2; i < sqrt(value) + 1; i++) {
        if (value % i == 0) return false;
    }
    return true;
}

int function3() {
    int _size = 0;
    int outputSize = 0;
    string data = "";
    string line;
    ifstream in("input.txt");
    if (in.is_open()) { //Чтение из входного файла
        getline(in, line);
        _size = stoi(line);
        getline(in, line);
        data = line;
    }
    in.close();
    int* mas = new int[_size] { 0 };
    
    if (data.find(",")) split(mas, _size, data, ",", 1);
    else if(data.find(", ")) split(mas, _size, data, ", "); //Приведение строки в массив с помощью ссылки на массив
    else split(mas, _size, data, " ", 1);

    int* mas_simple = new int[_size] { 0 };
    int index = 0;
    for (int i = 0; i < _size; i++) {
        if (isSimple(mas[i]) && mas[i] != 0) { //Проверка условия задачи
            mas_simple[index] = mas[i];
            index++; //Подсчёт количества реальных чисел в массиве
        }
    }
    delete[] mas; //Удаляем ненужный больше массив

    ofstream out("output.txt");
    out.put(0); //Записываем предварительный символ в файл, куда в последствии запишем количество чисел выходного массива
    out << endl;

    int v_size = index / 2; //т.к. нас интересуют только числа, стоящие на чётных местах, урезаем размер в два раза
    for (int i = 1; i < v_size * 2; i += 2) { //Записываем ответ в файл
        if (outputSize != v_size - 1) out << mas_simple[i] << ",";
        else out << mas_simple[i];
        outputSize++; //Подсчитываем количество чисел, записанных в файл
    }
    out.seekp(0); //Переводим указатель записи файла на нулевую позицию, что записать количество чисел в выходном массиве
    out << outputSize; //Записываем количество чисел выходного массива
    out.close();

    return outputSize; //Возвращаем ответ
}

int main()
{
    //EX3=================================================
    cout << function3();
}
