//
// Created by hadasswittow on 12/12/19.
//

#ifndef TREADSAFEDSINGLETON_SINGLETON_H
#define TREADSAFEDSINGLETON_SINGLETON_H

#include <pthread.h>

pthread_mutex_t instance_mutex;

class Singleton {
public:
    static volatile Singleton* volatile getInstance();

private:

    static volatile Singleton* volatile pInstance;
};


volatile Singleton* volatile Singleton::pInstance = NULL;

inline volatile Singleton* volatile Singleton::getInstance()
{
    if (!pInstance)
    {
        pthread_mutex_lock(&instance_mutex);

        if (!pInstance)
        {
            __sync_fetch_and_or(&pInstance, new Singleton);
        }

        pthread_mutex_unlock(&instance_mutex);
    }

    return pInstance;
}


#endif //TREADSAFEDSINGLETON_SINGLETON_H
