#include<iostream>
#include<vector>
#include <algorithm>
#include <cassert>
#include <cmath>

typedef std::vector<int> V;
typedef std::vector<std::vector<int>> M;

typedef std::pair<size_t, size_t> P;
typedef std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> PP;

void fill(M& m, size_t y, size_t x, int val) {
    m = M(y);
    std::for_each(m.begin(), m.end(), 
        [&](V& v) -> void {
            v.resize(x, val);
        }
    );
}

void print(std::string name, M m) {
    std::cout << name << ": " << std::endl;

    std::for_each(m.begin(), m.end(), 
        [](V v) -> void {
            std::for_each(v.begin(), v.end(), 
                [](size_t s_i) -> void {
                    std::cout << s_i << " ";
                }
            );
            std::cout << std::endl;
        }
    );
} 

size_t max_submatrix(M m) {
    size_t y = m.size();
    assert(y > 0);

    size_t x = m[0].size();
    assert(x > 0);

    print("M", m);

    M s;
    fill(s, y + 1, x + 1, 0);

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

    print("S", s);

    return max_s_ij;
}

void main() {
    size_t y; 
    size_t x;
    std::cin >> y >> x;

    M m = M(y);
    for(size_t i = 0; i < y; ++i) {
        V& v = m[i] = V(x);
        for(size_t j = 0; j < x; ++j) {
            std::cin >> v[j];
        }
    }

    size_t size_max = max_submatrix(m);

    std::cout << "max submatrix size: " << size_max << std::endl;

    system("pause");
}
