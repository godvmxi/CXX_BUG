#include <thread>
#include <atomic>
#include <unistd.h>
#include "threadheap.h"
#include <iostream>
//#define USING_CXX_THREAD
#ifdef USING_CXX_THREAD
static void ThreadLoop(void *p){
    ThreadHeap *p_thread =  (ThreadHeap *)p;
    while(p_thread->ExitFlag.load() != true){
        usleep(1000000);
      //  std::cout << "thread runing\n";
    }
    std::cout << "thread exit\n";
}
#else
static void *Thread2Loop(void *p){
    ThreadHeap *p_thread =  (ThreadHeap *)p;
    while(p_thread->ExitFlag.load() != true){
        usleep(1000000);
      //  std::cout << "thread runing\n";
    }
    std::cout << "thread exit\n";
    return NULL;
}
#endif
ThreadHeap::ThreadHeap(){
    this->PThread = NULL;
    this->ThreadId = -1;
    std::cout << "class init\n";

}
ThreadHeap::~ThreadHeap(){
    this->Stop();
    std::cout << "thread delete\n";

}
void ThreadHeap::Start(void){
    this->ExitFlag.store(false);
#ifdef USING_CXX_THREAD 
    this->PThread = new std::thread(ThreadLoop, this);
    if(this->PThread == NULL){
        throw "new thread error\n";
    }
    std::cout << "thread start ok->" << this->PThread <<std::endl;
#else 
    int ret;
    ret = pthread_create(&this->ThreadId, NULL, Thread2Loop, this);
    if(ret != 0){
        std::cout << "thread create error\n";
    }
    std::cout << "thread start ok ->" << this->ThreadId << std::endl;
#endif

}
void ThreadHeap::Stop(void){
    this->ExitFlag.store(true);
#ifdef USING_CXX_THREAD
    if(this->PThread != NULL)
        this->PThread->join();
        delete this->PThread;
    this->PThread = NULL;
#else
    pthread_join(this->ThreadId, NULL);
    this->ThreadId = -1;
#endif
    std::cout << "thread stop \n";
}
void ThreadHeap::SetThreadStackSize(int size){
    int ret;
    pthread_attr_t attr;
    ret = pthread_attr_init(&attr);
    if(ret != 0){
        std::cout << "thread attr init error\n";
    }
    ret = pthread_attr_setstacksize(&attr, size);
    if(ret != 0){
        std::cout << "thread set  attr error\n";
    }
    //create 
    //
    ret = pthread_attr_destroy(&attr);
    if(ret != 0){
        std::cout << "delete attr error\n";
    }


}
int main(int argc, char **argv){
    printf("hello heap\n");
    ThreadHeap *p_thread = NULL;
    char c = '0';
    std::cout << "Press any key to contiue\n";
    
    while(1){
        c = getchar();
        switch(c){
            case 'b':
                p_thread->Start();
                break;
            case 'e':
                p_thread->Stop();
                break;
            case 'n':
                p_thread  = new ThreadHeap() ;
                break;
            case 'd':
                delete p_thread;
                p_thread = NULL;
                break;
            default :
                if(c != '\n')
                    std::cout << "input cmd ->" << c <<std::endl;

        }

    }

}
