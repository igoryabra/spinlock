#include "spinlock.hpp"

bool spinlock::try_lock()
{
    bool false_ = false;
    return spin_lock.compare_exchange_weak(false_, true, std::memory_order_acquire);
}

void spinlock::lock()
{
    bool false_ = false;
    while(!spin_lock.compare_exchange_weak(false_, true, std::memory_order_acquire))
        false_ = false;
}

void spinlock::unlock()
{
    spin_lock.store(false, std::memory_order_release);
}
