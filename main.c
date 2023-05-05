#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_NUM 100000
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
bool *sharedResource;

void *task(void *i) {
    while(1) {
        int number = rand() % MAX_NUM;
        pthread_mutex_lock(&lock);
        printf("%ld", pthread_self());
        if (!sharedResource[number]) {
            printf(" - %d\n", number);
            sharedResource[number] = true;
        }
        else
            printf(" %d already present \n", number);
        pthread_mutex_unlock(&lock);
    }
}
bool *initSharedResource(int max) {
    bool *resource = (bool*)malloc(max);
    for (int i = 0; i < MAX_NUM; i++)
        resource[i] = false;
    return resource;
}

int main () {
    srand(time(NULL));
    sharedResource = initSharedResource(MAX_NUM);

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, task, NULL);
    pthread_create(&thread2, NULL, task, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    free(sharedResource);
    pthread_mutex_destroy(&lock);
    return 0;
}