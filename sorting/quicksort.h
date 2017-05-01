#pragma once

#include <algorithm>
#include <random>

namespace sort {

// Three-way splitting quicksort: begin:equal_it - elements, lesser than base, equal_it:greater_it - equal,
// greater_it:end - greater.
template<class RandomAccessIterator, class Compare>
void impl_quicksort(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    if (end - begin < 2u)
        return;
    auto greater_it = begin;
    auto equal_it = begin;
    auto base = begin + rand() % (end - begin);
    for (auto it = begin; it != end; ++it) {
        if (comp(*it, *base)) {
            std::iter_swap(equal_it, greater_it);
            std::iter_swap(it, equal_it);
            ++equal_it;
            ++greater_it;
        } else if (!comp(*base, *it)) {
            if (it == base)
                base = greater_it;
            std::iter_swap(it, greater_it);
            ++greater_it;
        }
    }
    impl_quicksort(begin, equal_it, comp);
    impl_quicksort(greater_it, end, comp);
}

template<class RandomAccessIterator, class Compare>
void quicksort(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    impl_quicksort(begin, end, comp);
}

template<class RandomAccessIterator>
void quicksort(RandomAccessIterator begin, RandomAccessIterator end)
{
    return quicksort(begin, end, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

}  // namespace sort
