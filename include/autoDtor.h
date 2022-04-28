/**
 * @file autoDtor.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Autómata dinamikus foglalás-törlő
 * @version 0.1
 * @date 2022-03-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef autoDtor_H
#define autoDtor_H

#include <iostream>
#include <memtrace.h>

namespace factolog {

/**
 * @brief Automatikusan törli a megadott dinamikus memóriát ha nem hívódik meg előbb az AutoDtor::success() 
 * 
 * @tparam T A mutatott típus
 */
template<typename T>
class AutoDtor{
    T* toDelete;    ///<A dinamikusan foglalt memória
    public:
    /**
     * @brief Új AutoDtor létrehozása
     * 
     * @param t A mutatott típus
     */
    AutoDtor(T* t): toDelete(t){}

    /**
     * @brief AutoDtor felszabadítása
     */
    ~AutoDtor(){
        delete toDelete;
    }

    /**
     * @brief Jelzi, hogy a dinamikus memória törlése nem szügséges
     */
    void success(){
        toDelete = NULL;
    }

    /**
     * @brief Frissíti a törlendő címet. 
     * 
     * A korábban mutatott objektumot nem törli.
     * 
     * @param t Az új objektum
     */
    void update(T *t){
        toDelete = t;
    }
};

} //namespace factolog

#endif //autoDtor_H
