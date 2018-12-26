#ifndef thread_pool_h
#define thread_pool_h

#include <iostream>
#include <vector>
#include <thread>
#include <cmath>

class ThreadPool {
public:
    template<typename Index, typename Callable>
    static void ParallelFor(Index start, Index end, Callable func) {
        const static unsigned count = std::thread::hardware_concurrency();
        
        std::cout << "Thread count: " << count << std::endl;

        // Size of a slice for the range functions
        Index n = end - start + 1;
        Index slice = (Index) std::round(n / static_cast<double>(count));
        slice = std::max(slice, Index(1));
        
        // [Helper] Inner loop
        auto launch_range = [&func] (int k1, int k2) {
            for (Index k = k1; k < k2; ++k) {
                func(k);
            }
        };
        
        // Create pool and launch jobs
        std::vector<std::thread> pool;
        pool.reserve(count);
        Index i1 = start;
        Index i2 = std::min(start + slice, end);
        for (unsigned i = 0; i < count && i1 < end; ++i) {
            pool.emplace_back(launch_range, i1, i2);
            i1 = i2;
            i2 = std::min(i2 + slice, end);
        }
        if (i1 < end) {
            pool.emplace_back(launch_range, i1, end);
        }
        
        // Wait for jobs to finish.
        for (std::thread& t : pool) {
            if (t.joinable()) {
                t.join();
            }
        }
    }
    
    template<typename Index, typename Callable>
    static void SequentialFor(Index start, Index end, Callable func) {
        for (Index i = start; i < end; ++i) {
            func(i);
        }
    }
};

#endif /* thread_pool_h */
