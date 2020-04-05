#include <gtest/gtest.h>
#include "spinlock.hpp"
#include <functional>
#include <thread>
#include "omp.h"
#include <list>

using std::list;

//Testing lock
namespace spinlock_test
{
    // Fixture for testing spinlock with a usage of lock and try_lock
    class spinlock_test : public testing::TestWithParam<int> {
    protected:
        int N = 100;
        spinlock locker;
        list<int> *expected = initialize_expected();

        // Expected list initializer
        list<int>* initialize_expected() {
            auto *input = new list<int>;
            for (size_t i = 0; i < N; i++)
                (*input).push_back(i + 1);

            return input;
        }

    public:
	void lock_add_thread_id(int id, list<int> &input) {
            locker.lock();
            input.push_back(id);
            locker.unlock();
        }

        void try_lock_add_thread_id(int id, list<int> &input) {
            while (!locker.try_lock());
            input.push_back(id);
            locker.unlock();
        }
    };

    // Test lock function with std::thread
    TEST_F(spinlock_test, std_thread_lock_test) {
        auto *input = new list<int>[N];


        std::thread threads[N];

        for (int i = 0; i < N; ++i)
            threads[i] = std::thread(std::bind(&spinlock_test::lock_add_thread_id, this, i + 1, std::ref(*input)));

        for (auto& thread: threads)
            thread.join();

        (*input).sort();
        EXPECT_EQ(*input, *expected) << "Error in lock function with std::thread";
    }

    //Test lock_test function with std::thread
    TEST_F(spinlock_test, std_thread_try_lock_test) {
        auto *input = new list<int>[N];

        std::thread threads[N];

        for (int i = 0; i < N; ++i)
            threads[i] = std::thread(std::bind(&spinlock_test::try_lock_add_thread_id, this, i + 1, std::ref(*input)));

        for (auto& thread: threads)
            thread.join();

        (*input).sort();
        EXPECT_EQ(*input, *expected) << "Error in try_lock function with std::thread";
    }

    //Test lock function with OpenMP
    TEST_F(spinlock_test, omp_lock_test) {
        auto *input = new list<int>[N];

        omp_set_num_threads(N);

        #pragma omp parallel shared(locker)
        {
            lock_add_thread_id(omp_get_thread_num() + 1, *input);
        }

        (*input).sort();
        EXPECT_EQ(*input, *expected) << "Error in lock function with OpenMP";
    }

    //Test try_lock function with OpenMP
    TEST_F(spinlock_test, omp_try_lock_test) {
        auto *input = new list<int>[N];

        omp_set_num_threads(N);

        #pragma omp parallel shared(locker)
        {
            lock_add_thread_id(omp_get_thread_num() + 1, *input);
        }

        (*input).sort();
        EXPECT_EQ(*input, *expected) << "Error in try_lock function with OpenMP";
    }
}
