#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Input2D {
    float x;
    float y;
};

bool function1(Input2D P, Input2D A, Input2D B) {
    if (P.x >= A.x and P.y <= A.y and P.x <= B.x and P.y >= B.y) {
        if ((A.x == 0 and P.x == 0) or (B.x == 0 and P.x == 0)) return true;
        if ((A.y == 0 and P.y == 0) or (B.y == 0 and P.y == 0)) return true;
        if ((A.y / A.x) == (P.y / P.x)) return true;
        if ((B.y / B.x) == (P.y / P.x)) return true;
    }
    return false;
}

int main()
{
    //EX1===============================================
    vector<float> mas;
    string value;
    for (int i = 0; i < 6; i++) {
        cin >> value;
        if (value[value.size() - 1] == ',') mas.push_back(stof(value.substr(0, value.size() - 1)));
        else mas.push_back(stof(value));
    }
    bool result = function1({ mas[0], mas[1] }, { mas[2], mas[3] }, { mas[4], mas[5] });
    
    if (result == false) cout << "false" << endl;
    else cout << "true" << endl;
}
