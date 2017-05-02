#pragma once

#include <iterator>

namespace sort {

// Bubble sort.
template<class RandomAccessIterator, class Compare>
void bubble(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    // Begin iterator is moved one position backwards on each step.
    while (end != begin) {
        for (auto it = begin; it + 1 != end; ++it) {
            // Swap elements, if they are inversed.
            if (comp(*(it + 1), *it))
                std::iter_swap(it, it + 1);
        }
        --end;
    }
}

template<class RandomAccessIterator>
void bubble(RandomAccessIterator begin, RandomAccessIterator end)
{
    return bubble(begin, end, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}


// Unstable selection sort.
template<class RandomAccessIterator, class Compare>
void selection(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    // Begin iterator is moved one position forward on each step.
    while (end != begin) {
        // Selecting unsorted element, that should be first.
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

template<class RandomAccessIterator>
void selection(RandomAccessIterator begin, RandomAccessIterator end)
{
    return selection(begin, end, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}


// Stable selection sort.
template<class RandomAccessIterator, class Compare>
void stableSelection(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    // Begin iterator is moved one position forward on each step.
    while (end != begin) {
        // Selecting unsorted element, that should be first.
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

template<class RandomAccessIterator>
void stableSelection(RandomAccessIterator begin, RandomAccessIterator end)
{
    return stableSelection(begin, end, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}


// Insertion sort.
template<class RandomAccessIterator, class Compare>
void insertion(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    auto sorted = begin;
    while (sorted != end) {
        auto current = sorted;
        // Move current element through already sorted data, until it will be placed correctly.
        while (current != begin && comp(*current, *(current - 1))) {
            std::iter_swap(current - 1, current);
            --current;
        }
        ++sorted;
    }
}

template<class RandomAccessIterator>
void insertion(RandomAccessIterator begin, RandomAccessIterator end)
{
    return insertion(begin, end, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

}  // namespace sort
