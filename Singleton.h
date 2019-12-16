//
// Created by hadasswittow on 12/12/19.
//

#ifndef TREADSAFEDSINGLETON_SINGLETON_H
#define TREADSAFEDSINGLETON_SINGLETON_H

#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>

pthread_mutex_t instance_mutex;

class Singleton {
public:
    static Singleton *getInstance();

    static Singleton *getDeadBeef();

    static void Deleter();

private:
    static bool m_isInit;
    static bool m_isReady;
    static Singleton *pInstance;
};

bool Singleton::m_isInit = false;
bool Singleton::m_isReady = false;
Singleton *Singleton::pInstance = NULL;


inline Singleton *Singleton::getInstance() {

    assert(getDeadBeef() != pInstance);
    if (!m_isReady) {

        if (!__sync_fetch_and_or(reinterpret_cast<int *>(&m_isInit), true)) {

            pInstance = new Singleton();

            atexit(Singleton::Deleter); // delete pInstance after main
            m_isReady = true;
        } else { // for that when other threads come when we are in the middle of initializing the ptr they should
            while (!m_isInit)
                sleep(0);
        }

    }
    return pInstance;

}

inline void Singleton::Deleter() {
    delete (pInstance);
    pInstance = getDeadBeef();

}

inline Singleton *Singleton::getDeadBeef() {

    return reinterpret_cast<Singleton *>(0xdeadbeef);
}

#endif //TREADSAFEDSINGLETON_SINGLETON_H
