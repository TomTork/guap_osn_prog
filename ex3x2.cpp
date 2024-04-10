#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> nonRepeatableRoutes(int n, int m, vector<pair<int, int>> rightMoves,
    pair<int, int> startPosition, pair<int, int> endPosition, int K,
    vector<pair<int, int>> result = {}, int iter = 0) {
    //Отладочная информация
    cout << "Current iter is " << iter << endl;
    cout << "Current position is " << startPosition.first << " " << startPosition.second << endl;
    cout << "Moves: ";
    for (pair<int, int> el : result) {
        cout << el.first << " " << el.second << "; ";
    }
    cout << endl;

    if (iter > K - 1 || rightMoves.size() == 0) return vector<pair<int, int>>{}; //неудачный путь
    if (iter == K - 1 && (bool)(startPosition == endPosition)) return result; //удачный путь
    
    if (iter == 0) result.push_back(startPosition);
    //проверка на выход за пределы области
    if (startPosition.first + rightMoves[0].first < n
        && startPosition.first + rightMoves[0].first >= 0
        && startPosition.second + rightMoves[0].second < m
        && startPosition.second + rightMoves[0].second >=0) {
        startPosition.first += rightMoves[0].first;
        startPosition.second += rightMoves[0].second;
        result.push_back(startPosition);
    }
    //Убираем ход, которым уже ходили
    vector<pair<int, int>> newRightMoves(rightMoves.begin() + 1, rightMoves.end());
    return nonRepeatableRoutes(n, m, newRightMoves, startPosition, endPosition, K, result, iter + 1);
}

vector<vector<pair<int, int>>> controller(int n, int m, vector<pair<int, int>> rightMoves,
    pair<int, int> startPosition, pair<int, int> endPosition, int K) {
    vector<vector<pair<int, int>>> answer;
    vector<pair<int, int>> iteration;
    int attempt = 0;
    //Перебираем все возможные комбинации ходов
    for (int i = 0; i < rightMoves.size(); i++) {
        for (int j = i; j < rightMoves.size(); j++) {
            cout << "ATTEMPT " << attempt << endl;
            iteration = nonRepeatableRoutes(n, m, rightMoves, startPosition, endPosition, K + 1);
            cout << endl;
            //проверка возвращаемого значения, способы сходить не должны повторяться
            if (iteration.size() == K + 1 &&
                answer.end() == find(answer.begin(),
                    answer.end(), iteration)) answer.push_back(iteration);
            swap(rightMoves[i], rightMoves[j]);
            attempt++;
        }
    }
    return answer;
}

typedef pair<int, int> p; //Для простоты переназываем переменную pair<int, int>

int main()
{
    vector<vector<pair<int, int>>> answer = controller(4, 4, { p(2, -1) , p(-2, 1),
        p(1, 2), p(-1, -2) }, p(0, 0), p(3, 1), 3); //из условия
    //vector<vector<p>> answer = controller(5, 5, { p(2, 1), p(-1, 2), p(-1, 2), p(2, 1) }, p(1, 1), p(2, 4), 2); //два направления
    //vector<vector<p>> answer = controller(5, 5, { p(2, 1), p(-1, 2), p(-1, 2), p(2, 1) }, p(1, 1), p(5, 5), 2); //до точки невозможно добраться
    //vector<vector<p>> answer = controller(5, 5, { p(2, 1), p(-1, 2), p(-1, 2), p(2, 1) }, p(1, 1), p(1, 1), -1); //фигура уже в этой точке
    for (int k = 0; k < answer.size(); k++) {
        cout << "Way number: " << k << endl;
        for (int i = 0; i < answer[k].size(); i++) {
            cout << answer[k][i].first << " " << answer[k][i].second << endl;
        }
    }
}
