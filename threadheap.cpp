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

}
ThreadHeap::~ThreadHeap(){
    this->Delete();

}
void ThreadHeap::Create(void){
    this->ExitFlag.store(false);
    this->PThread = new std::thread(ThreadLoop, this);
    if(this->PThread == NULL){
        throw "new thread error\n";
    }
    std::cout << "thread create ok\n";

}
void ThreadHeap::Delete(void){
    if(this->PThread){
        this->ExitFlag.store(true);
        this->PThread->join();
        delete this->PThread;
        this->PThread = NULL;
        std::cout << "thread delete \n";
    }
}
int main(int argc, char **argv){
    printf("hello heap\n");
    ThreadHeap threadtest ;
    getchar();

    while(1){
        threadtest.Create();
        sleep(5);
        threadtest.Delete();
        sleep(5);

    }

}
