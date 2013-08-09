#ifndef RWLOCK_HPP
#define RWLOCK_HPP


#include<mutex>
#include<condition_variable>




class RWLock {
public:
    RWLock();
    ~RWLock();


    void acquireReader();
    void releaseReader();


    void acquireWriter();
    void releaseWriter();


private:
    int numReaders_;
    std::mutex mtx_numReaders_;
    std::mutex mtx_writer_;
    std::condition_variable_any cv_numReaders_;
};


#endif
