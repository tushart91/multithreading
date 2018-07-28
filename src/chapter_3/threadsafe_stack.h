//
// Created by Tushar Tiwari on 7/28/18.
//

#ifndef MULTITHREADING_THREADSAFE_STACK_H
#define MULTITHREADING_THREADSAFE_STACK_H

#include <stack>
#include <mutex>
#include <exception>
#include <memory>

struct empty_stack : std::exception {
    const char *what() const noexcept override {
        return "empty stack detected\n";
    }
};

template<typename T>
class threadsafe_stack {
    std::stack<T> d_data;
    mutable std::mutex d_lock;

public:
    threadsafe_stack() = default;

    threadsafe_stack(const threadsafe_stack &other) {
        std::lock_guard<std::mutex> _1(d_lock);
        d_data = other.d_data;
    }

    void push(T elem) {
        std::lock_guard<std::mutex> _1(d_lock);
        d_data.push(elem);
    }

    std::shared_ptr<T> pop() {
        // Returning the shared_ptr to the value is safer than returning the
        // value itself, because when returning the value, the copy constructor
        // can fail, causing the program to loose the value after already
        // modifying the stack (pop). If the copy constructor fails when
        // creating the shared_ptr the operation can be marked as a failure
        // leaving the stack untouched and the top safe. Also, the shared_ptr's
        // copy constructor is a relatively safer operation.

        std::lock_guard<std::mutex> _1(d_lock);
        if (d_data.empty())
            throw empty_stack();
        std::shared_ptr<T> ret(std::make_shared<T>(d_data.top()));
        d_data.pop();
        return ret;
    }

    void pop(T& ret) {
        // Assigning the value to a reference variable is safer than returning
        // the value itself, because when returning the value, the copy
        // constructor can fail, causing the program to loose the value after
        // already modifying the stack (pop). If the copy constructor fails
        // when assigning it to the passed in argument, the operation can be
        // marked as a failure leaving the stack untouched and the top safe.

        std::lock_guard<std::mutex> _1(d_lock);
        if (d_data.empty)
            throw empty_stack();
        ret = d_data.top();
        d_data.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> _1(d_lock);
        return d_data.empty();
    }

    unsigned long size() const {
        std::lock_guard<std::mutex> _1(d_lock);
        return d_data.size();
    }

};


#endif //MULTITHREADING_THREADSAFE_STACK_H
