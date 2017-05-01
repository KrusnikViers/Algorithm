#pragma once

#include <iterator>

namespace sort {

// Bubble sort.
template<class RandomAccessIterator>
void bubble(RandomAccessIterator begin, RandomAccessIterator end)
{
    return bubble(begin, end, std::less<std::iterator_traits<RandomAccessIterator>::value_type>());
}

template<class RandomAccessIterator, class Compare>
void bubble(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    // Use end iterator as an indicator of already sorted elements.
    while (end != begin) {
        for (auto it = begin; it + 1 != end; ++it) {
            if (comp(*(it + 1), *it))
                std::iter_swap(it + 1, it);
        }
        // After each inner iterations, last element will be placed on it's position.
        --end;
    }
}


// Selection sort.
template<class RandomAccessIterator>
void selection(RandomAccessIterator begin, RandomAccessIterator end)
{
    return selection(begin, end, std::less<std::iterator_traits<RandomAccessIterator>::value_type>());
}

template<class RandomAccessIterator, class Compare>
void selection(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    // Use begin iterator as an indicator of already sorted elements.
    while (end != begin) {
        auto best = begin;
        for (auto it = begin + 1; it != end; ++it) {
            if (comp(*it, *best))
                best = it;
        }
        if (best != begin)
            std::iter_swap(best, begin);
        ++begin;
    }
}


// Stable selection sort.
template<class RandomAccessIterator>
void stableSelection(RandomAccessIterator begin, RandomAccessIterator end)
{
    return stableSelection(begin, end, std::less<std::iterator_traits<RandomAccessIterator>::value_type>());
}

template<class RandomAccessIterator, class Compare>
void stableSelection(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    // Use begin iterator as an indicator of already sorted elements.
    while (end != begin) {
        auto best = begin;
        for (auto it = begin + 1; it != end; ++it) {
            if (comp(*it, *best))
                best = it;
        }
        while (best != begin) {
            std::iter_swap(best - 1, best);
            --best;
        }
        ++begin;
    }
}


// Insertion sort.
template<class RandomAccessIterator>
void insertion(RandomAccessIterator begin, RandomAccessIterator end)
{
    return insertion(begin, end, std::less<std::iterator_traits<RandomAccessIterator>::value_type>());
}

template<class RandomAccessIterator, class Compare>
void insertion(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    auto sorted = begin;
    while (sorted != end) {
        auto current = sorted;
        while (current != begin && comp(*current, *(current - 1))) {
            std::iter_swap(current - 1, current);
            --current;
        }
        ++sorted;
    }
}

}  // namespace sort
