#ifndef SPINLOCK_SPINLOCK_HPP
#define SPINLOCK_SPINLOCK_HPP

#include <atomic>

using std::atomic;

class spinlock{
public:
    explicit spinlock() : spin_lock(false) {}
    ~spinlock() = default;

    void lock();
    bool try_lock();
    void unlock();
protected:
    std::atomic_bool spin_lock;
};

#endif //SPINLOCK_SPINLOCK.HPP

