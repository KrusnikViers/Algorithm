#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "sorting/mergesort.h"
#include "sorting/simplesort.h"
#include "sorting/quicksort.h"

class SortingTest : public ::testing::Test,
                    public ::testing::WithParamInterface<const char*>
{
protected:
    struct StableNode
    {
        int value;
        int order;

        bool operator< (const StableNode& other) const { return value < other.value; }
    };

    void initializeStableDataAndTimer(const char* filename)
    {
        std::ifstream input_stream(filename, std::istream::in);
        int N;
        input_stream >> N;
        ASSERT_GT(N, 0);

        std::vector<StableNode> data(N);
        for (int i = 0; i < N; ++i) {
            input_stream >> data[i].value;
            data[i].order = i;
        }
        input_stream.close();
        stable_data_.swap(data);
        start_time_ = std::chrono::steady_clock::now();
    }

    void initializeUsualDataAndTimer(const char* filename)
    {
        std::ifstream input_stream(filename, std::istream::in);
        int N;
        input_stream >> N;
        ASSERT_GT(N, 0);

        std::vector<int> data(N);
        for (int i = 0; i < N; ++i)
            input_stream >> data[i];
        input_stream.close();
        usual_data_.swap(data);
        start_time_ = std::chrono::steady_clock::now();
    }

    void checkDataAndTimer(bool is_stable)
    {
        std::cout << "Time: " <<
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::steady_clock::now() - start_time_).count() << " us" << std::endl;
        if (is_stable) {
            for (size_t i = 1; i < stable_data_.size(); ++i) {
                if (stable_data_[i - 1].value != stable_data_[i].value)
                    ASSERT_LT(stable_data_[i - 1].value, stable_data_[i].value) << i;
                else
                    ASSERT_LT(stable_data_[i - 1].order, stable_data_[i].order) << i;
            }
        } else {
            for (size_t i = 1; i < stable_data_.size(); ++i)
                ASSERT_LE(usual_data_[i - 1], usual_data_[i]) << i;
        }
    }

    std::vector<StableNode> stable_data_;
    std::vector<int>        usual_data_;

    std::chrono::steady_clock::time_point start_time_;
};

TEST_P(SortingTest, Bubble)
{
    initializeStableDataAndTimer(GetParam());
    sort::bubble(stable_data_.begin(), stable_data_.end());
    checkDataAndTimer(true);
}

TEST_P(SortingTest, Selection)
{
    initializeUsualDataAndTimer(GetParam());
    sort::selection(usual_data_.begin(), usual_data_.end());
    checkDataAndTimer(false);
}

TEST_P(SortingTest, StableSelection)
{
    initializeStableDataAndTimer(GetParam());
    sort::stableSelection(stable_data_.begin(), stable_data_.end());
    checkDataAndTimer(true);
}

TEST_P(SortingTest, Insertion)
{
    initializeStableDataAndTimer(GetParam());
    sort::insertion(stable_data_.begin(), stable_data_.end());
    checkDataAndTimer(true);
}

TEST_P(SortingTest, Merge)
{
    initializeStableDataAndTimer(GetParam());
    sort::merge(stable_data_.begin(), stable_data_.end());
    checkDataAndTimer(true);
}

TEST_P(SortingTest, Quicksort)
{
    initializeUsualDataAndTimer(GetParam());
    sort::quicksort(stable_data_.begin(), stable_data_.end());
    checkDataAndTimer(false);
}

INSTANTIATE_TEST_CASE_P(DifferentInput, SortingTest,
                        ::testing::Values("data/sorting/all_duplicates.txt",
                                          "data/sorting/highly_dispersed.txt",
                                          "data/sorting/highly_duplicated.txt",
                                          "data/sorting/rarely_duplicated.txt",
                                          "data/sorting/single_number.txt",
                                          "data/sorting/unique_1.txt",
                                          "data/sorting/unique_2.txt",
                                          "data/sorting/unique_3.txt"));
