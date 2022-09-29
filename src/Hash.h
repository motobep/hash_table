#ifndef HASH_FUNC
#define HASH_FUNC

#include <string>

class Hash {
    int mod;
    const int k = 31;

    public:
        Hash(int m = 57);
        int operator()(std::string str);
        void set_range(unsigned int m);
};

#endif

