#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

struct MyOperator{
    string name;
    float spend = 0.0;
    string *notRelated = nullptr;
};

struct SpendMustForm{
    string name;
    float spend = 0.0;
    float must = 0.0;
};

struct Transactions{
    string sender;
    string recipient;
    float money;
};

MyOperator scrapData(int maxPeople, string &line){
    string name, other, raw;
    float money;
    auto *notRelated = new string[maxPeople]{""};
    name = line.substr(0, line.find(':'));
    other = line.substr(line.find(':'), line.length());
    if (other.find('/') != std::string::npos){
        raw = other.substr(other.find('/')+1, other.length());
        if (raw.find(',') != std::string::npos){ // more one people
            int index = 0, findIndex = 0;
            while (raw.find(',') != std::string::npos){
                if (index == maxPeople) break;
                findIndex = raw.find(',');
                notRelated[index] = raw.substr(0, findIndex);
                raw = raw.substr(findIndex + 1, raw.size());
                index++;
            }
            if(raw != "") notRelated[index] = raw;
        }
        else notRelated[0] = raw;
        money = stof(other.substr(1, other.find('/')-1));
    }
    else money = stof(other.substr(1, other.length()));
    return MyOperator{name, money, notRelated};
}

int dividerForDebt(int n, string*& people){
    int answer = 0;
    for(int i = 0; i < n; i++){
        if(!people[i].empty()) answer++;
    }
    if(answer == 0) return n;
    return n - answer;
}

bool nameInMas(string& name, int n, string*& people){
    for(int i = 0; i < n; i++){
        if(people[i] == name) return true;
    }
    return false;
}

SpendMustForm* generateTable(int n, string*& names, MyOperator*& operators) {
    auto* form = new SpendMustForm[n];
    float spend, must;
    for(int i = 0; i < n; i++){
        form[i].name = names[i];
        spend = 0;
        must = 0;
        for(int j = 0; j < n; j++){
            if(names[i] == operators[j].name) spend += operators[j].spend;
            else{
                if(!nameInMas(names[i], n, operators[j].notRelated)) {
                    must += operators[j].spend /
                            (float)dividerForDebt(n, operators[j].notRelated);
                }

            }
        }
        form[i].spend = spend + must;
        form[i].must = must;
    }
    return form;
}

//Тактика: перевести все деньги одному пользователю, а он переведёт долги остальным
vector<Transactions> generateTransactions(int n, SpendMustForm*& form){
    vector<Transactions> transactions;
    float totalDebt = 0;
    for(int i = 0; i < n; i++) totalDebt += form[i].must;
    float basicExpenses = totalDebt / (float)n; //Эту сумму мы должны будем получить у каждого
    for(int i = 1; i < n; i++){
        transactions.push_back(Transactions {
            form[i].name, form[0].name, form[i].must
        });
        form[0].must += form[i].must;
        form[i].must = 0;
    }
    for(int i = 1; i < n; i++){
        transactions.push_back(Transactions{
           form[0].name, form[i].name, basicExpenses
        });
        form[0].must -= basicExpenses;
        form[i].must += basicExpenses;
    }
    return transactions;
}

int main(){
    int n;
    string *names;
    MyOperator *operators;

    string filename = "/home/tomtork/CLionProjects/untitled/file.txt";
    ifstream in(filename);
    string line = "";
    if (in.is_open()){
        getline(in, line);
        n = stoi(line);
        names = new string[n];
        operators = new MyOperator[n];
        for (int i = 0; i < n; i++){
            getline(in, line);
            names[i] = line;
        }
        for (int i = 0; i < n; i++){
            getline(in, line);
            operators[i] = scrapData(n, line);
        }
    }
    in.close();
    auto* answer1 = generateTable(n, names, operators);
    for(int i = 0; i < n; i++){
        cout << answer1[i].name << "\t\t" << "|" << "\t\t" << setprecision(8) << answer1[i].spend << "\t\t" << "|"
        << "\t\t" << setprecision(8) << answer1[i].must << endl;
    }
    cout << endl;
    for(auto element: generateTransactions(n, answer1)){
        cout << element.sender << " -> " << element.recipient << " " << element.money << endl;
    }
    return 0;
}
