//
// Created by Tushar Tiwari on 7/27/18.
//

#include <gtest/gtest.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <numeric>
#include <algorithm>
#include <vector>

using namespace std;

namespace {
    unsigned long const MIN_PER_THREAD = 25;
}

template <typename InputIter, typename T>
struct ref_accumulate {
    // Need struct so we can instantiate the template object and then pass it
    // to the thread, because a function's reference cannot be
    // determined if it uses templates
    void operator ()(InputIter first, InputIter last, T& init) {
        // accumulate function, returns by reference
        init = accumulate(first, last, init);
    }
};

template <typename InputIter, typename T>
T parallel_accumulate(InputIter first, InputIter last, T init) {
    // Perform accumulate in parallel by using threads.
    // The no of threads used will come from thread::hardware_concurrency()
    // and each thread will at least contain 25 elements.
    // So less than 25 elements will use a single thread.

    const long length = distance(first, last);

    if (!length)
        return init;

    unsigned long const req_threads =
            (length - 1 + MIN_PER_THREAD) / MIN_PER_THREAD;

    unsigned long const num_threads =
            min((unsigned long)thread::hardware_concurrency(), req_threads);

    unsigned long const block_size = length / num_threads;

    cout << "Num Threads: " << num_threads << endl;

    vector<thread> threads(num_threads);
    vector<T> results(num_threads);

    InputIter block_start = first;
    InputIter block_end;
    for (size_t i = 0; i < num_threads - 1; ++i) {
        block_end = block_start;
        advance(block_end, block_size);
        threads[i] = thread(ref_accumulate<InputIter, T>{},
                block_start, block_end, ref(results[i]));
        block_start = block_end;
    }

    threads.back() = thread(ref_accumulate<InputIter, T>{},
            block_start, last, ref(results.back()));

    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

    T ret = accumulate(results.begin(), results.end(), init);

    cout << "Accumulate: " << ret << endl;

    return ret;
}

TEST(Chapter_2, ParallelAccumulate_Regular) { /* NOLINT */
    vector<int> buckets(100);
    iota(buckets.begin(), buckets.end(), 1);
    ASSERT_EQ(parallel_accumulate(buckets.begin(), buckets.end(), 0),
            accumulate(buckets.begin(), buckets.end(), 0));
}

TEST(Chapter_2, ParallelAccumulate_1_Thread) { /* NOLINT */
    vector<int> buckets(10);
    iota(buckets.begin(), buckets.end(), 1);
    ASSERT_EQ(parallel_accumulate(buckets.begin(), buckets.end(), 0),
              accumulate(buckets.begin(), buckets.end(), 0));
}

TEST(Chapter_2, ParallelAccumulate_1_Thread_Exact) { /* NOLINT */
    vector<int> buckets(25);
    iota(buckets.begin(), buckets.end(), 1);
    ASSERT_EQ(parallel_accumulate(buckets.begin(), buckets.end(), 0),
              accumulate(buckets.begin(), buckets.end(), 0));
}
