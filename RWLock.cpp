#include"RWLock.hpp"


using namespace std;


RWLock::RWLock() {
}

RWLock::~RWLock() {

}

void RWLock::acquireReader() {
    unique_lock<mutex> _(mtx_numReaders_);
    numReaders_++;
}

void RWLock::releaseReader() {
    unique_lock<mutex> _(mtx_numReaders_);

    numReaders_--;
    if (numReaders_ == 0)
        cv_numReaders_.notify_one();
}

// @brief block client thread until there's no reader exist
// @post r_lock is hold to exclude any upcoming clients
void RWLock::acquireWriter() {
    // wait for existing readers finish.
    mtx_numReaders_.lock();
    cv_numReaders_.wait(mtx_numReaders_, [&]{ return numReaders_ == 0; });
}

void RWLock::releaseWriter() {
    mtx_numReaders_.unlock();
    // wakeup next writer if any.
    cv_numReaders_.notify_one();
}
