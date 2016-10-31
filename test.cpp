#include "lru_cache.h"

#include <iostream>
#include <cassert>
#include <string>

int main() {
    util::lru_cache<std::string, std::string> map(1);

    {
        auto it = map.find("aa");
        assert(it == map.end());
    }

    {

        auto p = map.insert(std::make_pair("aa", "bb"));
        assert(p.second);

        auto it = map.find("aa");
        assert(it != map.end());
        assert(it->first == "aa");
        assert(it->second.first == "bb");
    }

    {
        auto p = map.insert(std::make_pair("aa", "BB"));
        assert(!p.second);

        auto it = map.find("aa");
        assert(it != map.end());
        assert(it->first == "aa");
        assert(it->second.first == "BB");
    }

    {
        auto p = map.insert(std::make_pair("cc", "dd"));
        assert(p.second);

        auto it = map.find("aa");
        assert(it == map.end());
    }

    {
        auto it = map.find("cc");
        assert(it != map.end());
        assert(it->first == "cc");
        assert(it->second.first == "dd");
    }

    return 0;
}
