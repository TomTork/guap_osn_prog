#include <iostream>
#include <string>
#include <math.h>
#include <time.h>

using namespace std;

struct Point
{
    float x;
    float y;
};

//<поиск по абсолютному координатному значению>
//алгоритм возводит обе координаты точки в квадрат и складывает их
//далее сортирует все эти точки по возрастанию, не забывая менять элементы массива местами
//далее находит самое минимальное требуемое значение
//и возвращает искомые точки

pair<Point, Point> search_min_ev_distance(Point mas[], int _size){
    pair<Point, Point> answer;
    answer.first = {0, 0};
    answer.second = {0, 0};

    float* pow_mas = new float[_size];
    for(int i = 0; i < _size; i++){
        pow_mas[i] = pow(mas[i].x, 2) + pow(mas[i].y, 2);
    }
    for(int i = 1; i < _size; i++){
        for(int j = i; j > 0 && pow_mas[j - 1] > pow_mas[j]; j--){
            swap(pow_mas[j - 1], pow_mas[j]);
            swap(mas[j - 1], mas[j]);
        }
    }
    float _min = __FLT_MAX__;
    int index = 0;
    float op;
    for(int num = 0; num < _size - 1; num++){
        op = pow(mas[num].x - mas[num+1].x, 2) + pow(mas[num].y - mas[num+1].y, 2);
        if(op < _min){
            _min = op;
            index = num;
        }
    }
    answer.first = mas[index];
    answer.second = mas[index+1];
    return answer;
}

int main()
{

    double cltimeclock, cltimeEnd;

    cltimeclock = clock();
    Point mas[] = {{6428, 7412},  {5754, 5043},  {8149, 9320},  {9978, 7172},  {6035, 98},  {46, 6246},  {3848, 9481},  {6671, 4640},  {162, 2763},  {9940, 9893},  {6948, 3786},  {2094, 5292},  {8216, 3871},  {4450, 9331},  {931, 8539},  {8860, 8465},  {6438, 3503},  {2752, 8515},  {6305, 2428},  {8600, 7496},  {5205, 3798},  {2420, 4974},  {3301, 9801},  {2437, 6691},  {2975, 5445},  {1995, 8585},  {7758, 6682},  {538, 2057},  {7865, 4740},  {9704, 2466},  {1998, 7660},  {4120, 88},  {2885, 6382},  {6988, 4347},  {5210, 6457},  {9929, 846},  {3402, 4742},  {9985, 385},  {9583, 5247},  {9831, 499},  {418, 4693},  {8864, 6558},  {4554, 5870},  {3987, 6341},  {2953, 3936},  {54, 2718},  {639, 8835},  {6005, 9433},  {2743, 589},  {2290, 5107},  {9907, 7521},  {5418, 3207},  {6114, 4191},  {8337, 5070},  {8950, 2475},  {3483, 2943},  {8047, 5703},  {7810, 4606},  {7738, 6093},  {5621, 7847},  {1504, 9480},  {6232, 9208},  {362, 1374},  {3865, 1706},  {6988, 5915},  {3286, 2355},  {3550, 7841},  {9897, 1933},  {4700, 7685},  {5624, 5599},  {7407, 9535},  {3552, 1610},  {8744, 8178},  {9259, 5101},  {1486, 3558},  {6656, 7216},  {8591, 845},  {4921, 7835},  {3570, 1255},  {5676, 3753},  {3973, 9779},  {3824, 9536},  {707, 7483},  {1240, 6627},  {8371, 1015},  {7356, 7999},  {4061, 4850},  {365, 247},  {1271, 1550},  {8259, 6064},  {3908, 7596},  {5121, 3978},  {4750, 6022},  {2330, 4904},  {8706, 5121},  {8719, 5425},  {9183, 7275},  {49, 7991},  {363, 6365},  {581, 2786},  {7483, 7777},  {336, 7511},  {9641, 4588},  {5822, 8014},  {9881, 548},  {370, 1964},  {3833, 7753},  {8038, 9438},  {2320, 7118},  {267, 9440},  {4602, 2021},  {9481, 5150},  {9146, 9654},  {2962, 6207},  {6150, 2178},  {2488, 4432},  {9322, 1532},  {5560, 5607},  {8753, 1413},  {7227, 3258},  {1612, 3514},  {6400, 6333},  {7798, 2400},  {5887, 5659},  {2886, 8024},  {8716, 1237},  {4531, 6446},  {3261, 3797},  {3784, 718},  {5683, 2558},  {9739, 5335},  {7474, 3212},  {6525, 3992},  {3640, 2775},  {5110, 9},  {8108, 5709},  {8646, 8186},  {9721, 4422},  {4567, 858},  {8827, 5760},  {6476, 9965},  {1103, 4499},  {5496, 8744},  {3449, 2078},  {6366, 2390},  {6513, 5549},  {701, 2454},  {7927, 3691},  {8694, 9049},  {3804, 2753},  {8873, 3476},  {808, 49},  {6041, 9951},  {8766, 5807},  {6640, 4502},  {5297, 9540},  {3166, 9776},  {2948, 4359},  {7849, 6890},  {5549, 8160},  {6558, 2294},  {3129, 2890},  {7109, 4379},  {805, 5367},  {3477, 3324},  {7464, 8180},  {4701, 9910},  {2981, 7680},  {2231, 552},  {3438, 2030},  {5488, 5973},  {4128, 4793},  {9874, 8264},  {7773, 2543},  {3043, 5289},  {7532, 528},  {6348, 7782},  {4076, 3486},  {3214, 8110},  {5132, 6053},  {4603, 7259},  {5355, 3828},  {4195, 2905},  {2181, 7378},  {8841, 2785},  {9619, 6442},  {4284, 6133},  {2820, 3521},  {3480, 4358},  {1756, 6698},  {4626, 5442},  {7661, 8304},  {3058, 1809},  {7970, 4963},  {4056, 5498},  {2132, 4923},  {8564, 523},  {3349, 6365},  {2391, 2624},  {4122, 5133},  {6564, 787},  {5184, 7089},  {4126, 4691},  {5660, 9526},  {1478, 7227},  {8157, 5898},  {3362, 5439},  {3543, 3823},  {1195, 7616},  {2904, 6028},  {2830, 180},  {4948, 656},  {3479, 6302},  {2395, 8834},  {3285, 8771},  {8964, 2337},  {2730, 3582},  {2376, 7147},  {464, 7400},  {3142, 1330},  {3492, 4571},  {5211, 4862},  {7177, 835},  {7968, 9490},  {6415, 8188},  {3426, 1484},  {7668, 2464},  {8693, 9010},  {3807, 723},  {4046, 8427},  {6847, 5115},  {9384, 4603},  {1637, 3071},  {3040, 3005},  {9044, 6488},  {3664, 6063},  {465, 1845},  {2680, 2698},  {3951, 5538},  {7880, 6006},  {3093, 3292},  {4215, 2963},  {259, 670},  {1010, 1568},  {502, 4396},  {3831, 1505},  {1935, 9655},  {8412, 8294},  {6468, 1552},  {8804, 9751},  {6828, 2763},  {5329, 1658},  {3528, 9373},  {4986, 2181},  {4476, 8300},  {4906, 4150},  {5136, 4953},  {5819, 8567},  {7967, 1669},  {6974, 9798},  {4885, 8340},  {8258, 4906},  {3350, 6805},  {8529, 3509},  {3248, 9084},  {5621, 5998},  {4254, 9378},  {9918, 2086},  {226, 8789},  {2044, 8339},  {5345, 9649},  {5244, 7485},  {3423, 8339},  {65, 9921},  {4884, 6662},  {8670, 4271},  {5781, 8541},  {9224, 204},  {1665, 9306},  {3952, 2739},  {4442, 2870},  {8065, 8260},  {5761, 1985},  {2884, 9053},  {4544, 4968},  {9328, 9568},  {3433, 2486},  {5440, 624},  {8431, 2283},  {324, 7524},  {6880, 7116},  {4965, 4883},  {3405, 1223},  {1033, 6229},  {127, 4341},  {6663, 8813},  {616, 1625},  {2383, 3739},  {8838, 9864},  {5596, 8833}};
    pair<Point, Point> answer = search_min_ev_distance(mas, 300);
    cltimeEnd = clock();
    cout << ((double) cltimeEnd - cltimeclock) / (double) CLOCKS_PER_SEC << endl;

    cout << endl;
    cout << answer.first.x << " " << answer.first.y << endl;
    cout << answer.second.x << " " << answer.second.y << endl;
}
