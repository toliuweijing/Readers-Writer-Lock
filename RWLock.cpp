include"RWLock.hpp"


using namespace std;


RWLock::RWLock() {
}

RWLock::~RWLock() {

}

void RWLock::acquireReader() {
    lock(mtx_writer_, mtx_numReaders_);
    numReaders_++;
    mtx_writer_.unlock();
    mtx_numReaders_.unlock();
}

void RWLock::releaseReader() {
    unique_lock<mutex> _(mtx_numReaders_);

    numReaders_--;
    if (numReaders_ == 0)
        cv_numReaders_.notify_one();
}

void RWLock::acquireWriter() {
    lock(mtx_writer_, mtx_numReaders_);
    cv_numReaders_.wait(mtx_numReaders_, [&]{ return numReaders_ == 0; });
}

void RWLock::releaseWriter() {
    cv_numReaders_.notify_one();
    mtx_writer_.unlock();
    mtx_numReaders_.unlock();
}
