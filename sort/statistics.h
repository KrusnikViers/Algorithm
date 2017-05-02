#pragma once

#include "quick.h"

namespace sort {
namespace impl {

template<class RandomAccessIterator, class Compare>
RandomAccessIterator k_statistics(RandomAccessIterator begin, RandomAccessIterator end,
                                  typename std::iterator_traits<RandomAccessIterator>::difference_type k,
                                  Compare comp)
{
    if (begin + 1 == end)
        return begin;
    RandomAccessIterator equals_begin, greater_begin;
    threeWaySplit(begin, end, comp, equals_begin, greater_begin);
    if (k < (equals_begin - begin))
        return k_statistics(begin, equals_begin, k, comp);
    else if (k < (greater_begin - begin))
        return equals_begin;
    else
        return k_statistics(greater_begin, end, k - (greater_begin - begin), comp);
}

}  // namespace impl

template<class RandomAccessIterator, class Compare>
RandomAccessIterator k_statistics(RandomAccessIterator begin, RandomAccessIterator end,
                                  typename std::iterator_traits<RandomAccessIterator>::difference_type k,
                                  Compare comp)
{
    if (k >= (end - begin) || end == begin)
        return end;
    return impl::k_statistics(begin, end, k, comp);
}

template<class RandomAccessIterator>
RandomAccessIterator k_statistics(RandomAccessIterator begin, RandomAccessIterator end,
                                  typename std::iterator_traits<RandomAccessIterator>::difference_type k)
{
    return k_statistics(begin, end, k,
                        std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

}  // namespace sort
