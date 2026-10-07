#include <iostream>
#include <new>

int main() {

    int k_str = 0;
    int k_stlb = 0;

    std::cout << "Введите кол-во строк матрицы: ";
    if (!(std::cin >> k_str) || k_str <= 0) {
        std::cerr << "Ошибка: введено не число\n";
        return 1;
    }
    std::cout << "Введите кол-во столбцов матрицы: ";
    if (!(std::cin >> k_stlb) || k_stlb <= 0) {
        std::cerr << "Ошибка: введено не число\n";
        return 1;
    }

    int** matrix = nullptr;
    int n = 0;

    try {
        matrix = new int*[k_str];

        for (n = 0; n < k_str; n++) {
            matrix[n] = new int[k_stlb];
        }
    }
    catch (const std::bad_alloc&) {
        for (int m = 0; m < n; m++) {
            delete[] matrix[m];
        }

        delete[] matrix;

        std::cerr << "Ошибка: не удалось выделить память\n";
        return 2;
    }

    std::cout << "Введите элементы матрицы:\n";
    for (int n = 0; n < k_str; n++) {
        for (int m = 0; m < k_stlb; m++) {
            if (!(std::cin >> matrix[n][m])) {
                std::cerr << "Ошибка: введено не число\n";

                for (int i = 0; i < k_str; i++) {
                    delete[] matrix[i];
                }

                delete[] matrix;

                return 1;
            }
        }
    }

    std::cout << "Транспонированная матрица:\n";
    for (int m = 0; m < k_stlb; m++) {
        for (int n = 0; n < k_str; n++) {
            std::cout << matrix[n][m] << " ";
        }
        std::cout << "\n";
    }

    for (int n = 0; n < k_str; n++) {
        delete[] matrix[n];
    }
    delete[] matrix;
    return 0;
}