#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <coroutine>
#include <iostream>
#include <optional>
#include <utility>
#include <functional>

// Generator class template to handle coroutine behavior
template<typename T>
class Generator {
public:

    // cppcheck-suppress-begin unusedFunction
    struct promise_type {
        T current_value;

        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }

        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        static std::suspend_always initial_suspend() { return {}; }
        static std::suspend_always final_suspend() noexcept { return {}; }
        static void return_void() {}
        static void unhandled_exception() { std::terminate(); }
    };
    // cppcheck-suppress-end unusedFunction

    using handle_type = std::coroutine_handle<promise_type>;

    explicit Generator(handle_type h) : coro_handle(h) {}
    ~Generator() {
        if (coro_handle) coro_handle.destroy();
    }

    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator(Generator&& other) noexcept : coro_handle(other.coro_handle) {
        other.coro_handle = nullptr;
    }

    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (coro_handle) coro_handle.destroy();
            coro_handle = other.coro_handle;
            other.coro_handle = nullptr;
        }
        return *this;
    }

    // Iterator to enable range-based for loops
    struct iterator {
        handle_type coro_handle;

        explicit iterator(handle_type h) : coro_handle(h) {}

        // Dereference to get the current value
        T operator*() const { return coro_handle.promise().current_value; }

        // Move to the next value
        iterator& operator++() {
            coro_handle.resume();
            if (coro_handle.done()) {
                coro_handle = nullptr;
            }
            return *this;
        }

        bool operator==(const iterator& other) const {
            return coro_handle == other.coro_handle;
        }

        bool operator!=(const iterator& other) const {
            return coro_handle != other.coro_handle;
        }
    };

    iterator begin() {
        if (coro_handle) {
            coro_handle.resume();
            if (coro_handle.done()) {
                return end();
            }
        }
        return iterator{coro_handle};
    }

    static iterator end() { return iterator{nullptr}; }

    // Retrieve the next value from the coroutine
    std::optional<T> next() {
        if (coro_handle.done()) {
            return std::nullopt; // No more values
        }
        coro_handle.resume();
        return coro_handle.promise().current_value;
    }

private:
    handle_type coro_handle;
};

template<typename T, typename... Args>
class ResettableGenerator {
public:
    using GenFunc = std::function<Generator<T>(Args...)>;

    explicit ResettableGenerator(GenFunc gen_func) 
        : gen_func_(gen_func), generator_(gen_func()) {}

    void reset() {
        generator_ = gen_func_();  // Reset by creating a new generator
    }

    Generator<T>& generator() {
        return generator_;
    }

private:
    GenFunc gen_func_;
    Generator<T> generator_;
};

#endif