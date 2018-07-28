//
// Created by Tushar Tiwari on 7/28/18.
//

#include "threadsafe_stack.h"

#include <gtest/gtest.h>
#include <thread>

using namespace std;

template<typename T>
struct random_func_wrapper {
    void operator()(threadsafe_stack<T> &stack) {
        cout << this_thread::get_id() << "\tPush: 10"
             << endl;
        stack.push(10);
        cout << this_thread::get_id() << "\tStack Size: "
             << stack.size() << endl;
        cout << this_thread::get_id() << "\tPop : "
             << *stack.pop() << endl;
        cout << this_thread::get_id() << "\tStack Size: "
             << stack.size() << endl;
    }
};

TEST (Chapter_3, Threadsafe_Stack) { /* NOLINT */

    threadsafe_stack<int> stack;

    thread t1(random_func_wrapper<int>{}, ref(stack));
    thread t2(random_func_wrapper<int>{}, ref(stack));

    t1.join();
    t2.join();
    cout << "main\tFinal Stack Size: " << stack.size() << endl;
    ASSERT_EQ("", "");
}