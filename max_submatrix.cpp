#include<iostream>
#include<vector>
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

size_t max_submatrix(M<int> m) {
    size_t y = m.size();
    assert(y > 0);

    size_t x = m[0].size();
    assert(x > 0);

    print("M", m);

    M<size_t> s;
    fill<size_t>(s, y + 1, x + 1, 0);

    size_t i, j, max_s_ij = 0;
    // i < y and j < x required due to unsigned overflow
    for(i = y - 1; i >= 0 && i < y; --i) {
        for(j = x - 1; j >= 0 && j < x; --j) {
            // std::cout << "gets here" << std::endl;
            int m_ij = m[i][j];

            if(m_ij == 1) {
                size_t s_ij = s[i][j] = std::min(s[i][j+1], std::min(s[i+1][j], s[i+1][j+1])) + 1;
                if(s_ij > max_s_ij) max_s_ij = s_ij;
            }
            else {
                s[i][j] = 0;
            }
        }
    }

    // print("S", s);

    return max_s_ij;
}

void main() {
    size_t n;
    std::cin >> n;

    for(size_t i = 0; i < n; ++i) {
        size_t y; 
        size_t x;
        std::cin >> y >> x;

        auto m = M<int>(y);
        for(size_t i = 0; i < y; ++i) {
            auto& v = m[i] = V<int>(x);
            for(size_t j = 0; j < x; ++j) {
                std::cin >> v[j];
            }
        }

        size_t size_max = max_submatrix(m);

        std::cout << "max submatrix size: " << size_max << std::endl;
    }

    system("pause");
}
