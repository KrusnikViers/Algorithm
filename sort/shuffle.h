#pragma once

#include <random>
#include <utility>

namespace sort {

template <class RandomAccessIterator>
void shuffle(RandomAccessIterator begin, RandomAccessIterator end)
{
    const auto size = end - begin;
    if (size < 2u)
        return;

    auto shuffled_count = (begin + 1) - begin;
    while (shuffled_count != size) {
        const auto random_offset = std::rand() % (shuffled_count + 1);
        std::iter_swap(begin + shuffled_count, begin + random_offset);
        ++shuffled_count;
    }
}

}  //namespace sort