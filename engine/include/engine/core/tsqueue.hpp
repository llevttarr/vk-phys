#ifndef TS_QUEUE_HPP
#define TS_QUEUE_HPP

#include <deque>
#include <mutex>
#include <condition_variable>
#include <optional>
#include <utility>

template <typename T>
class ThreadsafeQueue {
public:
    explicit ThreadsafeQueue(size_t max_size = 99999)
        : q_limit(max_size) {}

    void enque(T value) {
        {
            std::unique_lock lock(mtx_);
            cv_limit_.wait(lock, [this] { return deque_.size() < q_limit || done_; });
            if (done_) {
                return;
            }
            deque_.push_back(std::move(value));
        }
        cv_.notify_one();
    }

    std::optional<T> deque() {
        std::unique_lock lock(mtx_);
        cv_.wait(lock, [this] { return !deque_.empty() || done_; });
        if (deque_.empty()) {
            return std::nullopt;
        }
        T value = std::move(deque_.front());
        deque_.pop_front();
        cv_limit_.notify_one();
        return value;
    }

    bool try_deque_two(T& first, T& second) {
        std::unique_lock lock(mtx_);
        cv_.wait(lock, [this] { return deque_.size() >= 2 || (done_ && !deque_.empty()) || (done_ && deque_.empty()); });
        if (deque_.size() >= 2) {
            first = std::move(deque_.front());
            deque_.pop_front();
            second = std::move(deque_.front());
            deque_.pop_front();
            cv_limit_.notify_all();
            return true;
        }
        return false;
    }

    bool try_deque(T& value) {
        std::lock_guard lock(mtx_);
        if (deque_.empty()) {
            return false;
        }
        value = std::move(deque_.front());
        deque_.pop_front();
        cv_limit_.notify_one();
        return true;
    }

    void set_done() {
        {
            std::lock_guard lock(mtx_);
            done_ = true;
        }
        cv_.notify_all();
        cv_limit_.notify_all();
    }

    bool is_done() const {
        std::lock_guard lock(mtx_);
        return done_;
    }

    bool empty() const {
        std::lock_guard lock(mtx_);
        return deque_.empty();
    }

    size_t size() const {
        std::lock_guard lock(mtx_);
        return deque_.size();
    }

private:
    mutable std::mutex mtx_;
    std::condition_variable cv_;
    std::condition_variable cv_limit_;
    std::deque<T> deque_;
    bool done_ = false;
    size_t q_limit;
};

#endif //THREADSAFE_QUEUE_HPP
