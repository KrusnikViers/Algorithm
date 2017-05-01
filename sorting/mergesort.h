#pragma once

#include <algorithm>

namespace sort {

// Stable selection sort.
template<class RandomAccessIterator>
void merge(RandomAccessIterator begin, RandomAccessIterator end)
{
    return merge(begin, end, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

template<class RandomAccessIterator, class Compare>
void merge(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    if (end - begin < 2u)
        return;
    std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type> buffer(end - begin);
    impl_merge(begin, end, comp, buffer);
}

template<class RandomAccessIterator, class ValueType, class Compare>
void impl_merge(RandomAccessIterator begin, RandomAccessIterator end, Compare comp, std::vector<ValueType>& buffer)
{
    if (end - begin < 2u)
        return;

    // Sorting subarrays.
    auto middle = begin + (end - begin) / 2;
    impl_merge(begin, middle, comp, buffer);
    impl_merge(middle, end, comp, buffer);

    // Merging.
    auto l_it = begin, r_it = middle;
    size_t b_index = 0;
    while (l_it != middle && r_it != end) {
        if (comp(*r_it, *l_it)) {
            buffer[b_index] = std::move(*r_it);
            r_it++;
        } else {
            buffer[b_index] = std::move(*l_it);
            l_it++;
        }
        ++b_index;
    }

    // Moving tail of left subarray (if any) and merged data.
    if (l_it != middle)
        std::move_backward(l_it, middle, end);
    std::move(buffer.begin(), buffer.begin() + b_index, begin);
}

}  // namespace sort
