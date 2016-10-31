lru_cache
================

A very simple LRU cache

Usage
=====

````cpp

#include "lru_cache.h"

#include <iostream>
#include <cassert>
#include <string>

int main() {
    util::lru_cache<std::string, std::string> map(1);

    auto p = map.insert(std::make_pair("aa", "bb"));
    assert(p.second);

    auto it = map.find("aa");
    assert(it != map.end());
    assert(it->first == "aa");
    assert(it->second.first == "bb");

    return 0;
}

```
