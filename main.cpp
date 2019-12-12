#include <iostream>
#include "Singleton.h"

#define ThreadAmount 8

void* create_singleton(void *i)
{
    volatile Singleton * volatile s = Singleton::getInstance();
    std::cout << "Thread number: " << i << " has instance: " << s << std::endl;
}

int main()
{
    pthread_t threads[ThreadAmount];

    int i = 0;
    for (; i < ThreadAmount; ++i) {
        pthread_create(&threads[i], NULL, create_singleton, reinterpret_cast<void*>(i));
    }
    for (i = 0; i < ThreadAmount; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}