#include <chrono>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "sort/basic.h"
#include "sort/heap.h"
#include "sort/merge.h"
#include "sort/shuffle.h"
#include "sort/statistics.h"
#include "sort/quick.h"

class SortingTest : public ::testing::Test,
                    public ::testing::WithParamInterface<const char*>
{
protected:
    void startMeasurement()
    {
        start_time_ = std::chrono::steady_clock::now();
    }

    void endMeasurement()
    {
        const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now() - start_time_).count();
        std::cout << "Input: " << GetParam() << std::endl;
        std::cout << "Time: " << duration << " us" << std::endl;
    }

    std::chrono::steady_clock::time_point start_time_;
};

// Test stable sorting
class StableSortingTest : public SortingTest
{
protected:
    struct StableNode
    {
        int value;
        int order;
        bool operator< (const StableNode& other) const { return value < other.value; }
    };

    void prepareSortingTest()
    {
        std::ifstream input_stream(GetParam(), std::istream::in);
        int N;
        input_stream >> N;
        ASSERT_GT(N, 0);

        std::vector<StableNode> data(N);
        for (int i = 0; i < N; ++i) {
            input_stream >> data[i].value;
            data[i].order = i;
        }
        input_stream.close();
        data_.swap(data);
        startMeasurement();
    }

    void checkSorting()
    {
        endMeasurement();
        for (size_t i = 1; i < data_.size(); ++i) {
            if (data_[i - 1].value != data_[i].value)
                ASSERT_LT(data_[i - 1].value, data_[i].value) << i;
            else
                ASSERT_LT(data_[i - 1].order, data_[i].order) << i;
        }
    }

    std::vector<StableNode> data_;
};

INSTANTIATE_TEST_CASE_P(IntegerInput, StableSortingTest,
                        ::testing::Values("data/sorting/all_duplicates.txt",
                                          "data/sorting/highly_dispersed.txt",
                                          "data/sorting/highly_duplicated.txt",
                                          "data/sorting/rarely_duplicated.txt",
                                          "data/sorting/single_number.txt",
                                          "data/sorting/unique_1.txt",
                                          "data/sorting/unique_2.txt",
                                          "data/sorting/unique_3.txt"));

TEST_P(StableSortingTest, Bubble)
{
    prepareSortingTest();
    sort::bubble(data_.begin(), data_.end());
    checkSorting();
}

TEST_P(StableSortingTest, StableSelection)
{
    prepareSortingTest();
    sort::stableSelection(data_.begin(), data_.end());
    checkSorting();
}

TEST_P(StableSortingTest, Insertion)
{
    prepareSortingTest();
    sort::insertion(data_.begin(), data_.end());
    checkSorting();
}

TEST_P(StableSortingTest, Merge)
{
    prepareSortingTest();
    sort::merge(data_.begin(), data_.end());
    checkSorting();
}

// Test unstable sorting (also suitable for stable algorithms)
class UnstableSortingTest : public SortingTest
{
protected:
    void prepareSortingTest()
    {
        std::ifstream input_stream(GetParam(), std::istream::in);
        int N;
        input_stream >> N;
        ASSERT_GT(N, 0);

        std::vector<int> data(N);
        for (int i = 0; i < N; ++i)
            input_stream >> data[i];
        input_stream.close();
        data_.swap(data);
        startMeasurement();
    }

    void checkSorting()
    {
        endMeasurement();
        for (size_t i = 1; i < data_.size(); ++i)
            ASSERT_LE(data_[i - 1], data_[i]) << i;
    }

    std::vector<int> data_;
};

INSTANTIATE_TEST_CASE_P(IntegerInput, UnstableSortingTest,
                        ::testing::Values("data/sorting/all_duplicates.txt",
                                          "data/sorting/highly_dispersed.txt",
                                          "data/sorting/highly_duplicated.txt",
                                          "data/sorting/rarely_duplicated.txt",
                                          "data/sorting/single_number.txt",
                                          "data/sorting/unique_1.txt",
                                          "data/sorting/unique_2.txt",
                                          "data/sorting/unique_3.txt"));

TEST_P(UnstableSortingTest, Bubble)
{
    prepareSortingTest();
    sort::bubble(data_.begin(), data_.end());
    checkSorting();
}

TEST_P(UnstableSortingTest, Selection)
{
    prepareSortingTest();
    sort::selection(data_.begin(), data_.end());
    checkSorting();
}

TEST_P(UnstableSortingTest, StableSelection)
{
    prepareSortingTest();
    sort::stableSelection(data_.begin(), data_.end());
    checkSorting();
}

TEST_P(UnstableSortingTest, Insertion)
{
    prepareSortingTest();
    sort::insertion(data_.begin(), data_.end());
    checkSorting();
}

TEST_P(UnstableSortingTest, Merge)
{
    prepareSortingTest();
    sort::merge(data_.begin(), data_.end());
    checkSorting();
}

TEST_P(UnstableSortingTest, Quicksort)
{
    prepareSortingTest();
    sort::quick(data_.begin(), data_.end());
    checkSorting();
}

TEST_P(UnstableSortingTest, Heapsort)
{
    prepareSortingTest();
    sort::heap(data_.begin(), data_.end());
    checkSorting();
}

// Test shuffle.
class ShuffleSortingTest : public SortingTest
{
protected:
    void prepareShuffleTest()
    {
        std::ifstream input_stream(GetParam(), std::istream::in);
        int N;
        input_stream >> N;
        ASSERT_GT(N, 0);

        original_data_.resize(N);
        for (int i = 0; i < N; ++i)
            input_stream >> original_data_[i];
        input_stream.close();
        data_ = original_data_;
        startMeasurement();
    }

    void checkShuffled()
    {
        endMeasurement();
        // We expect at least 90% of the elements to be not on their original places.
        size_t shuffled_count = 0;
        for (size_t i = 0; i < data_.size(); ++i)
            if (data_[i] != original_data_[i])
                ++shuffled_count;
        EXPECT_GT(shuffled_count, original_data_.size() * 0.9);
        std::cout << shuffled_count << " of " << original_data_.size() << " elements moved." << std::endl;
    }

    std::vector<int> data_;
    std::vector<int> original_data_;
};

INSTANTIATE_TEST_CASE_P(IntegerInput, ShuffleSortingTest,
                        ::testing::Values("data/sorting/highly_dispersed.txt",
                                          "data/sorting/highly_duplicated.txt",
                                          "data/sorting/rarely_duplicated.txt",
                                          "data/sorting/unique_1.txt",
                                          "data/sorting/unique_2.txt",
                                          "data/sorting/unique_3.txt"));

TEST_P(ShuffleSortingTest, Basic)
{
    // Set concrete seed to make test reproducible.
    std::srand(42u);
    prepareShuffleTest();
    sort::shuffle(data_.begin(), data_.end());
    checkShuffled();

    // Even after multiple shuffles, elements should not be corrupted.
    const int kShufflesCount = 5;
    for (int i = 0; i < kShufflesCount; ++i)
        sort::shuffle(data_.begin(), data_.end());
    sort::quick(data_.begin(), data_.end());
    sort::quick(original_data_.begin(), original_data_.end());
    EXPECT_EQ(original_data_, data_);
}

// Test shuffle.
class KStatisticsSortingTest : public SortingTest
{
protected:
    void prepareTest()
    {
        std::ifstream input_stream(GetParam(), std::istream::in);
        int N;
        input_stream >> N;
        ASSERT_GT(N, 0);

        original_data_.resize(N);
        for (int i = 0; i < N; ++i)
            input_stream >> original_data_[i];
        input_stream.close();
        data_ = original_data_;
    }

    std::vector<int> data_;
    std::vector<int> original_data_;
};

INSTANTIATE_TEST_CASE_P(IntegerInput, KStatisticsSortingTest,
                        ::testing::Values("data/sorting/highly_dispersed.txt",
                                          "data/sorting/highly_duplicated.txt",
                                          "data/sorting/rarely_duplicated.txt",
                                          "data/sorting/unique_1.txt",
                                          "data/sorting/unique_2.txt",
                                          "data/sorting/unique_3.txt"));

TEST_P(KStatisticsSortingTest, Basic)
{
    // Set concrete seed to make test reproducible.
    std::srand(42u);
    prepareTest();
    sort::quick(original_data_.begin(), original_data_.end());

    // Check minimum.
    EXPECT_EQ(original_data_[0], *sort::k_statistics(data_.begin(), data_.end(), 0u));
    sort::shuffle(data_.begin(), data_.end());

    // Check maximum.
    EXPECT_EQ(original_data_.back(), *sort::k_statistics(data_.begin(), data_.end(), data_.size() - 1));
    sort::shuffle(data_.begin(), data_.end());

    // Check random points from between.
    const size_t kSamplesCount = 9;
    const size_t fraction = data_.size() / kSamplesCount;
    for (size_t i = 1; i <= kSamplesCount; ++i) {
        EXPECT_EQ(original_data_[i * fraction], *sort::k_statistics(data_.begin(), data_.end(), i * fraction));
        sort::shuffle(data_.begin(), data_.end());
    }

    // Check, that data was not corrupted.
    sort::quick(data_.begin(), data_.end());
    EXPECT_EQ(original_data_, data_);
}
