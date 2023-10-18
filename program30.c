#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("Hello from the new thread!\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread_function, NULL);
    
    printf("Hello from the main thread!\n");
    
    pthread_join(tid, NULL);  // Wait for the new thread to finish
    return 0;
}
#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("Hello from the new thread!\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread_function, NULL);
    
    printf("Hello from the main thread!\n");
    
    pthread_join(tid, NULL);  // Wait for the new thread to finish
    printf("New thread has finished.\n");
    return 0;
}
#include <stdio.h>
#include <pthread.h>

int main() {
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, NULL, NULL);
    pthread_create(&tid2, NULL, NULL, NULL);

    if (pthread_equal(tid1, tid2)) {
        printf("Threads are equal.\n");
    } else {
        printf("Threads are not equal.\n");
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg) {
    printf("Child thread is doing some work...\n");
    sleep(2);  // Simulate work
    pthread_exit(NULL);  // Terminate the thread
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread_function, NULL);
    
    printf("Main thread waiting for child thread to finish...\n");
    
    pthread_join(tid, NULL);  // Wait for the child thread to finish
    
    printf("Child thread has finished.\n");
    return 0;
}
