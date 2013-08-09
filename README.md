Readers-Writer-Lock
===================
Version 1.1
integrate RWLock with std::unique_lock. e.g. std::unique_lock ul(RWLock); ...

Version 1.0
Provide implementation of Readers-Writer lock. Reader lock is shared among readers 
while writer lock is mutally exclusive. It utilizes condition variables for writers to efficiently wait 
for exclusive access.
