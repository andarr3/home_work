
#include <iostream>
#include <new>

void free_matrix(int ** a, size_t rows) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] a[i];
    }
    delete[] a;
}

int ** read_matrix(size_t n, size_t m) {
    int ** a = nullptr;

    try {
        a = new int*[n];

        for (size_t i = 0; i < n; ++i) {
            a[i] = nullptr;
        }

        for (size_t i = 0; i < n; ++i) {
            a[i] = new int[m];

            for (size_t j = 0; j < m; ++j) {
                if (!(std::cin >> a[i][j])) {
                    free_matrix(a, n);
                    return nullptr;
                }
            }
        }
    }
    catch (const std::bad_alloc&) {
        free_matrix(a, n);
        throw;
    }

    return a;
}

int ** concat_rows(
    const int * const * lhs, size_t n1, size_t m1,
    const int * const * rhs, size_t n2, size_t m2
) {
    size_t n = std::max(n1, n2);
    int ** res = nullptr;

    try {
        res = new int*[n];

        for (size_t i = 0; i < n; ++i) {
            res[i] = nullptr;
        }

        for (size_t i = 0; i < n; ++i) {
            size_t len = 0;

            if (i < n1) {
                len += m1;
            }
            if (i < n2) {
                len += m2;
            }

            res[i] = new int[len];

            if (i < n1) {
                for (size_t j = 0; j < m1; ++j) {
                    res[i][j] = lhs[i][j];
                }
            }

            size_t offset = 0;
            if (i < n1) {
                offset = m1;
            }

            if (i < n2) {
                for (size_t j = 0; j < m2; ++j) {
                    res[i][offset + j] = rhs[i][j];
                }
            }
        }
    }
    catch (const std::bad_alloc&) {
        free_matrix(res, n);
        throw;
    }

    return res;
}

int main() {
    size_t n1, m1, n2, m2;
    int ** a = nullptr;
    int ** b = nullptr;
    int ** r = nullptr;

    try {
        if (!(std::cin >> n1 >> m1)) {
            return 1;
        }

        a = read_matrix(n1, m1);

        if (a == nullptr) {
            return 1;
        }

        if (!(std::cin >> n2 >> m2)) {
            free_matrix(a, n1);
            return 1;
        }

        b = read_matrix(n2, m2);

        if (b == nullptr) {
            free_matrix(a, n1);
            return 1;
        }

        r = concat_rows(a, n1, m1, b, n2, m2);
    }
    catch (const std::bad_alloc&) {
        if (a != nullptr) {
            free_matrix(a, n1);
        }
        if (b != nullptr) {
            free_matrix(b, n2);
        }
        return 2;
    }

    size_t n = std::max(n1, n2);

    for (size_t i = 0; i < n; ++i) {
        size_t len = 0;

        if (i < n1) {
            len += m1;
        }
        if (i < n2) {
            len += m2;
        }

        for (size_t j = 0; j < len; ++j) {
            std::cout << r[i][j] << " ";
        }

        std::cout << std::endl;
    }

    free_matrix(a, n1);
    free_matrix(b, n2);
    free_matrix(r, n);

    return 0;
}
