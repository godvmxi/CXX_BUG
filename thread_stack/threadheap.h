#include <thread>
#include <atomic>
#include <unistd.h>

class ThreadHeap{
    public :
        ThreadHeap();
        ~ThreadHeap();
        void SetThreadStackSize(int size);
        void Start(void);
        void Stop(void);
        std::atomic_bool ExitFlag;
        pthread_attr_t ThreadAttr;
    private:
        std::thread *PThread;
        pthread_t ThreadId;
};
