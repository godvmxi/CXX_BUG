#include <thread>
#include <atomic>
#include <unistd.h>
using namespace std;
typedef struct {
    thread *p_thread;
    atomic_bool *exit_flag;
}thread_handler_t;
static void threadloop(void  *p , void *flag){
    atomic_bool *exit = (atomic_bool *)p; 
    while(exit->load() == false){
        sleep(1);
        printf("thread runing\n");
    }
}

thread_handler_t *create_thread(void *p){ 
    thread_handler_t *handler = (thread_handler_t *) malloc(sizeof(thread_handler_t));
    if(handler == NULL){
        printf("create handler errror\n");
        return NULL;
    }
    atomic_bool *flag = new atomic_bool();
    handler->exit_flag =  flag;
    flag->store(false);
    thread *p_thread= new thread(p, flag);
    if(p_thread == NULL){
        return NULL;
    }
    handler->p_thread = p_thread;
    return handler;
}
void delete_thread(thread_handler_t **p){
    thread_handler_t *p_thread = *p;
    p_thread->exit_flag->store(true);
    p_thread->p_thread->join();
    delete p_thread->exit_flag;
    free(p_thread);
    *p = NULL;
}

int main(int argc, char **argv){
    printf("hello heap\n");
    thread_handler_t  *p_thread_1;
    p_thread_1 =  create_thread((void *)threadloop);
    printf("thread create result ->%p\n", p_thread_1);
    sleep(5);
    delete_thread(&p_thread_1);
    printf("thread delete result ->%p\n", p_thread_1);
    sleep(5);
    
    p_thread_1 =  create_thread((void *)threadloop);
    printf("thread create result ->%p\n", p_thread_1);
    sleep(5);
    delete_thread(&p_thread_1);
    printf("thread delete result ->%p\n", p_thread_1);
    sleep(5);

    p_thread_1 =  create_thread((void *)threadloop);
    printf("thread create result ->%p\n", p_thread_1);
    sleep(5);
    delete_thread(&p_thread_1);
    printf("thread delete result ->%p\n", p_thread_1);
    sleep(5);
    return 1;
}
