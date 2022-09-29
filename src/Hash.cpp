#include "Hash.h"


Hash::Hash(int m) { mod = m; }

int Hash::operator()(std::string str) {
    unsigned long long h = 0;
    for (char c : str) {
        int x = (int)(c - 'a' + 1);
        h = (h * k + x) % mod;
    }
    return h;
}

void Hash::set_range(unsigned int m) { mod = m; }

