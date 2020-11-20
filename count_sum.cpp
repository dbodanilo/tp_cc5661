#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>

template<class a>
using V = std::vector<a>;

template<class a>
using M = std::vector<std::vector<a>>;

template<class a>
void fill(M<a>& m, size_t y, size_t x, a val) {
    m = M<a>(y);
    std::for_each(m.begin(), m.end(), 
        [&](V<a>& v) -> void {
            v.resize(x, val);
        }
    );
}

template<class a>
void print(std::string name, V<a> v) {
    std::cout << name << ": " << std::endl;

    std::for_each(v.begin(), v.end(), 
        [](a x) -> void {
            std::cout << x << " ";
        }
    );

    std::cout << std::endl;
}

template<class a>
void print(std::string name, M<a> m) {
    std::cout << name << ": " << std::endl;

    std::for_each(m.begin(), m.end(), 
        [](V<a> v) -> void {
            std::for_each(v.begin(), v.end(), 
                [](a x) -> void {
                    std::cout << x << " ";
                }
            );
            std::cout << std::endl;
        }
    );
}

// todo: tratar sums negativas (normalizar)
// fazer para números reais? (de acordo com precisão desejada)
size_t count_sum(V<int> arr, int x) {
    size_t n = arr.size();
    assert(n > 0);

    print("arr", arr);

    M<size_t> s;
    fill<size_t>(s, n + 1, x + 1, 0);

    size_t i;
    int j;
    for(i = 1; i <= n; ++i) {
        // exists when sum equals current element
        s[i][arr[i - 1]] += 1;

        for(j = 0; j <= x; ++j) {
            // sum j attainable in [0..i]
            s[i][j] += s[i - 1][j];

            int j_minus_arr_i = std::max(j - arr[i - 1], 0);
            s[i][j] += s[i - 1][j_minus_arr_i];
        }
    }

    print("S", s);

    return s[n][x];
}

void main() {
    size_t n;
    int x;
    std::cin >> n >> x;

    auto arr = V<int>(n);
    for(size_t j = 0; j < n; ++j) {
        std::cin >> arr[j];
    }

    size_t count = count_sum(arr, x);

    std::cout << "subsets with sum " << x << ": " 
              << count << std::endl;

    system("pause");
}
