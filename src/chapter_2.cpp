//
// Created by Tushar Tiwari on 7/27/18.
//

#include <gtest/gtest.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <future>


using namespace std;


TEST(Chapter2, Init) { /* NOLINT */

    cout << thread::hardware_concurrency() << endl;
}