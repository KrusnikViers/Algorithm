#pragma once

#include <algorithm>
#include <vector>

namespace sort {
namespace impl {

template<class RandomAccessIterator, class ValueType, class Compare>
void merge(RandomAccessIterator begin, RandomAccessIterator end, Compare comp, std::vector<ValueType>& buffer)
{
    if (end - begin < 2u)
        return;

    // Sorting begin-middle and middle-end subarrays.
    RandomAccessIterator middle = begin + (end - begin) / 2;
    merge(begin, middle, comp, buffer);
    merge(middle, end, comp, buffer);

    // Merging results.
    RandomAccessIterator merged_left = begin, merged_right = middle;
    auto merged_in_buffer = buffer.begin();
    while (merged_left != middle && merged_right != end) {
        if (comp(*merged_right, *merged_left)) {
            *merged_in_buffer = std::move(*merged_right);
            ++merged_right;
        } else {
            *merged_in_buffer = std::move(*merged_left);
            ++merged_left;
        }
        ++merged_in_buffer;
    }

    // There can be elements left in right or left subarray. While rest of right subarray elements is already in the
    // end of the sorted data, left subarray tail should be moved directly.
    if (merged_left != middle)
        std::move_backward(merged_left, middle, end);
    std::move(buffer.begin(), merged_in_buffer, begin);
}

}  // namespace impl

template<class RandomAccessIterator, class Compare>
void merge(RandomAccessIterator begin, RandomAccessIterator end, Compare comp)
{
    if (end - begin < 2u)
        return;
    std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type> buffer(end - begin);
    impl::merge(begin, end, comp, buffer);
}

template<class RandomAccessIterator>
void merge(RandomAccessIterator begin, RandomAccessIterator end)
{
    return merge(begin, end, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

}  // namespace sort
