#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "sort/basic.h"
#include "sort/heap.h"
#include "sort/merge.h"
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
