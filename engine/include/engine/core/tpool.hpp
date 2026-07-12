#ifndef TPOOL_HPP
#define TPOOL_HPP
#include "tsqueue.hpp"
#include <functional>
#include <vector>
#include <thread>
#include <future>

class ThreadPool{
public:
    explicit ThreadPool(uint16_t n_thr){
        n_threads=n_thr;
        for (size_t i=0;i<n_thr;++i){
            thread_v.emplace_back(&ThreadPool::get_thread_loop,this);
        }
    }
    ~ThreadPool(){
        queue.set_done();
        for (std::thread& t : thread_v){
            t.join();
        }
    }
    template<typename F, typename R = std::invoke_result_t<F>>
    std::future<R> submit(F&& taskf){
        auto task=std::make_shared<std::packaged_task<R()>>(std::forward<F>(taskf));
        auto future=task->get_future();
        queue.enque(
            [task]{(*task)();}
        );
        return future;
    }
private:
    std::vector<std::thread> thread_v;
    ThreadsafeQueue<std::function<void()>> queue;
    std::uint16_t n_threads;
    void get_thread_loop(){
        while(true){
            auto task=queue.deque();
            if(!task.has_value()){
                return;
            }
            (*task)();
        }
    }
};

#endif // THREAD_POOL_HPP
