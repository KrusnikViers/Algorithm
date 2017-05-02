#pragma once

#include <algorithm>
#include <random>

namespace sort {
namespace impl {

template<class RandomAccessIterator, class Compare>
void heapify(RandomAccessIterator begin, RandomAccessIterator end,
             RandomAccessIterator node_root, Compare comp)
{
    RandomAccessIterator selected_as_root = node_root;
    const auto first_child_offset = ((node_root - begin + 1) << 1) - 1;
    if (first_child_offset < (end - begin)) {
        // Check first child.
        RandomAccessIterator child = begin + first_child_offset;
        if (comp(*selected_as_root, *child))
            selected_as_root = child;
        // Check second child.
        ++child;
        if (child != end && comp(*selected_as_root, *child))
            selected_as_root = child;

        // If root value should be changed, update it and heapify selected child.
        if (selected_as_root != node_root) {
            std::iter_swap(selected_as_root, node_root);
            heapify(begin, end, selected_as_root, comp);
        }
    }
}

}  // namespace impl

template<class RandomAccessIterator, class Compare>
void heap(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    if (end - begin < 2u)
        return;

    // Building heap.
    for (auto it = begin + (end - begin) / 2; it != begin; --it)
        impl::heapify(begin, end, it, comp);
    impl::heapify(begin, end, begin, comp);

    // Sorting, based on previously built heap. End iterator moving backwards during sorting.
    while (end != begin) {
        std::iter_swap(begin, end - 1);
        --end;
        impl::heapify(begin, end, begin, comp);
    }
}

template<class RandomAccessIterator>
void heap(RandomAccessIterator begin, RandomAccessIterator end)
{
    return heap(begin, end, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

}  // namespace sort
