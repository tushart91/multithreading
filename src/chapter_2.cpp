//
// Created by Tushar Tiwari on 7/27/18.
//

#include <gtest/gtest.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <numeric>


using namespace std;

namespace {
    const int MIN_PER_THREAD = 25;
}


//template<typename InputIt, typename T>
//struct block_parallel {
//    void operator()(InputIt first, InputIt last, T init) {
//        accumulate(first, last, init);
//    }
//};

template<typename InputIt, typename T>
T parallel_accumulate(InputIt first, InputIt last, T init) {
    // Perform accumulate in parallel by using threads.
    // The no of threads used will come from
    // thread::hardware_concurrency()

}

TEST(Chapter2, Init) { /* NOLINT */

}
