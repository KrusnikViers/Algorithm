#pragma once

#include <algorithm>
#include <random>

namespace sort {
namespace impl {

// Three-way splitting: divide elements on lesser, equal and greater than the base element parts.
template<class RandomAccessIterator, class Compare>
void threeWaySplit(RandomAccessIterator begin, RandomAccessIterator end, Compare comp,
                   RandomAccessIterator& equal_begin, RandomAccessIterator& greater_begin)
{
    // Randomized base element selection should improve performance for a data, that was already in bad order.
    auto base = begin + rand() % (end - begin);
    greater_begin = begin;
    equal_begin = begin;

    // Dividing data.
    for (auto it = begin; it != end; ++it) {
        // Element is lesser, than base.
        if (comp(*it, *base)) {
            // If there are any equal elements, we should move the first equal element on the place of the first
            // greater, and swap the first greater and the current elements.
            if (equal_begin != greater_begin) {
                // Do not swap the first equal and the first greater elements, if there are no greater elements.
                if (greater_begin != it)
                    std::iter_swap(equal_begin, greater_begin);
                // Equal element could be the base one: update base element iterator in that case.
                if (equal_begin == base)
                    base = greater_begin;
                std::iter_swap(it, equal_begin);
            } else {
                std::iter_swap(it, greater_begin);
            }
            ++equal_begin;
            ++greater_begin;
            // Element is equal to the base one.
        } else if (!comp(*base, *it)) {
            if (it == base)
                base = greater_begin;
            std::iter_swap(it, greater_begin);
            ++greater_begin;
        }
        // Leave element in the end of the greater elements interval, if it is greater than the base one.
    }
}

template<class RandomAccessIterator, class Compare>
void quick(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    if (end - begin < 2u)
        return;
    RandomAccessIterator equal_begin, greater_begin;
    // Divide elements on subarrays.
    threeWaySplit(begin, end, comp, equal_begin, greater_begin);
    // Sorting subarrays with elements, that are lesser or greater than the base one.
    quick(begin, equal_begin, comp);
    quick(greater_begin, end, comp);
}

}  // namespace impl

template<class RandomAccessIterator, class Compare>
void quick(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    impl::quick(begin, end, comp);
}

template<class RandomAccessIterator>
void quick(RandomAccessIterator begin, RandomAccessIterator end)
{
    return quick(begin, end, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

}  // namespace sort
