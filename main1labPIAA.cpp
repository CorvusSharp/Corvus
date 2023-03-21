#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

class Border {
public:
    int x;
    int y;
    int w;
};
// Проверяет, перекрывает ли заданный квадрат другие квадраты в данной картографической карте
bool overlaySearch(const vector<Border> &vec, int x, int y) {
    for (auto sq: vec) {
        if (x >= sq.x && x < sq.x + sq.w && y >= sq.y && y < sq.y + sq.w) {
            return true;
        }
    }
    return false;
}
// Рекурсивная функция, реализующая алгоритм обхода дерева решений
void backtrack(vector<Border> &map, int occupancySquare, int bordlen,
               int xLeftOccupancy, int yLeftOccupancy, int n, int &bestcount, vector<Border> &bestarry,
               int &counterOpertion) {
    counterOpertion++;
    for (int x = xLeftOccupancy; x < n; ++x) {
        for (int y = yLeftOccupancy; y < n; ++y) {
            if (!overlaySearch(map, x, y)) {
// Определение максимального размера квадрата, который может быть помещен на данной позиции
                int maxside = min(n - 1, min(n - x, n - y));
                for (auto sq: map) {
                    if (sq.x + sq.w > x && sq.y > y) {
                        maxside = min(maxside, sq.y - y);
                    }
                }
// Пробуем добавлять квадраты на данную позицию, начиная с максимального возможного размера
                for (int ms = maxside; ms >= 1; --ms) {
                    Border sq{x, y, ms};
                    vector<Border> tmpBest = map;
                    tmpBest.push_back(sq);
                    cout << "TmpSolve:\n";
                    for (auto i: tmpBest) {
                        cout << 1 + i.x << ' ' << 1 + i.y << ' ' << i.w << '\n';
                    }

// Если столешница заполнена полностью, и это решение имеет меньшее количество квадратов, чем лучшее решение,
// то обновляем лучшее решение
                    if (occupancySquare + pow(sq.w, 2) == n * n) {
                        if (bordlen + 1 < bestcount) {
                            bestcount = bordlen + 1;
                            bestarry = tmpBest;
                            cout <<"TMP BRST ARRAY: \n";
                            cout <<"TMP BEST COUNT SQ: "<< bestcount <<'\n';
                            for (auto i: tmpBest) {
                                cout << 1 + i.x << ' ' << 1 + i.y << ' ' << i.w << '\n';
                            }
                        }
                    } else {
// Если столешница еще не полностью заполнена, и это решение имеет меньшее количество квадратов, чем лучшее решение,
// то продолжаем рекурсивно обходить дерево решений
                        if (bordlen + 1 < bestcount) {
                            backtrack(tmpBest, occupancySquare + pow(sq.w, 2), bordlen + 1,
                                      xLeftOccupancy, yLeftOccupancy, n, bestcount, bestarry, counterOpertion);
                        } else {
                            return;
                        }
// Если количество квадратов в текущем решении больше, чем в лучшем решении, то возврат из функции
                    }
                }
                return;
            }
        }
// Если не было найдено свободного места в текущей строке, то переходим на следующую строку
        xLeftOccupancy = n / 2;
        yLeftOccupancy = 0;
    }
}
// Инициализация начальной картографической карты, состоящей из трех квадратов
vector<Border> initStartSqOptimization(int n) {
    vector<Border> map;
    map.push_back({0, 0, (n + 1) / 2});
    map.push_back({0, (n + 1) / 2, n / 2});
    map.push_back({(n + 1) / 2, 0, n / 2});
    return map;
}
// Функция для определения максимального размера квадрата, на которые можно разбить столешницу
int maxDivision(int n, int &sqSize) {
    sqSize = 2;
    for (int i = 1; i <= n / 2; ++i) {
        if (n % i == 0) {
            sqSize = i;
        }
    }
    return n / sqSize;
}
int main() {
    int counterOperation = 0;
    int n; // размер столешницы
    std::cin >> n;
    int multiSqSize;
    n = maxDivision(n, multiSqSize);
    int bestcount = 2 * n + 1;
    vector<Border> map = initStartSqOptimization(n);
    vector<Border> bestarry;
    int StartOccupancySq = ((n + 1) / 2) * ((n + 1) / 2) + 2 * (n / 2) * (n / 2);// площадь заполненных квадратов;
    int maxlen; //максимальная длина обрезка
    int xLeftOccupancy = n / 2, yLeftOccupancy = (n + 1) / 2; //координаты левее которых заполнена столешница
    backtrack(map, StartOccupancySq, 3, xLeftOccupancy, yLeftOccupancy, n, bestcount, bestarry, counterOperation);
    std::cout << "final result: :\n";
    std::cout << "Count Operation: "<< counterOperation <<'\n';
    std::cout << bestcount << '\n';
    for (auto i: bestarry) {
        cout << 1 + i.x * multiSqSize << ' ' << 1 + i.y * multiSqSize << ' ' << i.w * multiSqSize << '\n';
    }
}
