#pragma once

#include <algorithm>
#include <random>

namespace sort {

template<class RandomAccessIterator, class Compare>
void impl_heapify(RandomAccessIterator begin, RandomAccessIterator end,
                  RandomAccessIterator target, Compare comp)
{
    const auto heap_size = end - begin;
    auto left_offset = (target - begin + 1) * 2 - 1;
    RandomAccessIterator left = left_offset < heap_size ? begin + left_offset : end;
    RandomAccessIterator right = left != end && left + 1 != end ? begin + left_offset + 1 : end;
    
    RandomAccessIterator parent_value = target;
    if (right != end && comp(*target, *right))
        parent_value = (left != end && comp(*right, *left)) ? left : right;
    else if (left != end && comp(*target, *left))
        parent_value = left;
    
    if (parent_value != target) {
        std::iter_swap(target, parent_value);
        impl_heapify(begin, end, parent_value, comp);
    }
}

template<class RandomAccessIterator, class Compare>
void heap(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    if (end - begin < 2u)
        return;

    // Building heap.
    auto processed = begin + (end - begin) / 2;
    for (auto it = processed; it != begin; --it)
        impl_heapify(begin, end, it, comp);
    impl_heapify(begin, end, begin, comp);

    // Sorting, based on prebuilt heap.
    processed = end;
    while (processed != begin) {
        std::iter_swap(begin, processed - 1);
        --processed;
        impl_heapify(begin, processed, begin, comp);
    }
}

template<class RandomAccessIterator>
void heap(RandomAccessIterator begin, RandomAccessIterator end)
{
    return heap(begin, end, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

}  // namespace sort
