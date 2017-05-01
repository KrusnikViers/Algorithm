#pragma once

#include <algorithm>
#include <random>

namespace sort {

// Three-way splitting quicksort: begin:equal_it - elements, lesser than base, equal_it:greater_it - equal,
// greater_it:end - greater.
template<class RandomAccessIterator, class Compare>
void impl_quick(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    if (end - begin < 2u)
        return;
    auto greater_it = begin;
    auto equal_it = begin;
    auto base = begin + rand() % (end - begin);
    for (auto it = begin; it != end; ++it) {
        if (comp(*it, *base)) {
            if (equal_it != greater_it) {
                if (greater_it != it)
                    std::iter_swap(equal_it, greater_it);
                if (equal_it == base)
                    base = greater_it;
                std::iter_swap(it, equal_it);
            } else {
                std::iter_swap(it, greater_it);
            }
            ++equal_it;
            ++greater_it;
        } else if (!comp(*base, *it)) {
            if (it == base)
                base = greater_it;
            std::iter_swap(it, greater_it);
            ++greater_it;
        }
    }
    impl_quick(begin, equal_it, comp);
    impl_quick(greater_it, end, comp);
}

template<class RandomAccessIterator, class Compare>
void quick(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    impl_quick(begin, end, comp);
}

template<class RandomAccessIterator>
void quick(RandomAccessIterator begin, RandomAccessIterator end)
{
    return quick(begin, end, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

}  // namespace sort
