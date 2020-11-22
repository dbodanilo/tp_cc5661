#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>

template<class a>
using V = std::vector<a>;

template<class a>
using M = std::vector<std::vector<a>>;

typedef std::string S;

template<class a>
void fill(M<a>& m, size_t y, size_t x, a val) {
    m = M<a>(y);
    std::for_each(m.begin(), m.end(), 
        [&](V<a>& v) -> void {
            v.resize(x, val);
        }
    );
}

void print(S name, S s) {
    std::cout << name << ": \"" << s << "\"" << std::endl;
}

template<class a>
void print(S name, V<a> v) {
    std::cout << name << ": " << std::endl;

    std::for_each(v.begin(), v.end(), 
        [](a x) -> void {
            std::cout << x << " ";
        }
    );

    std::cout << std::endl;
}

template<class a>
void print(S name, M<a> m) {
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

size_t longest_palindrome(S s) {
    size_t n = s.size();
    assert(n > 0);

    // print("S", s);

    M<size_t> m;
    fill<size_t>(m, n, n, 0);

    for(size_t i = 0; i < n; ++i) {
        m[i][i] = 1;

        if(i < n - 1 && s[i] == s[i + 1]) {
            m[i][i + 1] = 2;
        }
    }

    for(size_t i = n - 1; i < n; --i) {
        for(size_t j = i + 1; j < n; ++j) {
            // assert(j >= i);

            if(s[i] == s[j] && j > i + 1) {
                m[i][j] = m[i + 1][j - 1] + 2;
            }
            else if(s[i] != s[j]) {
                m[i][j] = std::max(m[i][j - 1], m[i + 1][j]);
            }
        }
    }

    // print("M", m);

    return m[0][n - 1];
}

void main() {
    size_t n;
    std::cin >> n;

    for(size_t i = 0; i < n; ++i) {
        S s;
        std::cin >> s;

        size_t len = longest_palindrome(s);

        std::cout << "length of the longest palindrome in \"" << s << "\": " 
                  << len << std::endl;
    }

    system("pause");
}
