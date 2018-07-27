//
// Created by Tushar Tiwari on 7/26/18.
//

#include <gtest/gtest.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <future>


using namespace std;


TEST (Chapter_1, Init) { /* NOLINT */

    mutex lock;

    auto func = [](mutex &lock, string &ret) -> void {
        lock.lock();
        cout << this_thread::get_id() << " func thread" << endl;
        lock.unlock();
        ret = "HELLO FROM THREAD";
    };

    string ret;
    thread t(func, ref(lock), ref(ret));
    lock.lock();
    cout << this_thread::get_id() << " main thread" << endl;
    lock.unlock();
    t.join();
    cout << this_thread::get_id() << " thread returned " << ret << endl;
}
