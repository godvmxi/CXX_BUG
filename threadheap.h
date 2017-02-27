#include <thread>
#include <atomic>
#include <unistd.h>

class ThreadHeap{
    public :
        ThreadHeap();
        ~ThreadHeap();
        void Create(void);
        void Delete(void);
        std::atomic_bool ExitFlag;
    private:
        std::thread *PThread;
};
