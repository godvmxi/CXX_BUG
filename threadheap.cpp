#include <thread>
#include <atomic>
#include <unistd.h>
#include "threadheap.h"
#include <iostream>
static void ThreadLoop(void *p){
    ThreadHeap *p_thread =  (ThreadHeap *)p;
    while(p_thread->ExitFlag.load() != true){
        usleep(1000000);
      //  std::cout << "thread runing\n";
    }
    std::cout << "thread exit\n";
}
ThreadHeap::ThreadHeap(){
    this->PThread = NULL;
    std::cout << "class init\n";

}
ThreadHeap::~ThreadHeap(){
    this->Stop();
    std::cout << "thread delete\n";

}
void ThreadHeap::Start(void){
    this->ExitFlag.store(false);
    this->PThread = new std::thread(ThreadLoop, this);
    if(this->PThread == NULL){
        throw "new thread error\n";
    }
    std::cout << "thread start ok\n";

}
void ThreadHeap::Stop(void){
    if(this->PThread){
        this->ExitFlag.store(true);
        this->PThread->join();
        delete this->PThread;
        this->PThread = NULL;
        std::cout << "thread stop \n";
    }
}
void ThreadHeap::SetThreadStackSize(int size){

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
