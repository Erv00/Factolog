/**
 * @file signals.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Jelek
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 * A kapcsolatokban terjedő jelek.
 * 
 */
#ifndef signals_H
#define signals_H

#include <ostream>
#include "color.h"
#include <memtrace.h>

/**
 * @brief Adat körbevevése "-lel
 * 
 * @tparam T Az adat típusa
 * @param s Az adat
 * @return std::string "adat"
 */
template <typename T>
std::string esc(const T& s){
    std::string ret = "\"";
    ret += s;
    ret += "\"";
    return ret;
}

/**
 * @brief Kapcsoaltban terjedő jel(ek)
 * 
 * Kiíráshoz használt osztály.
 * 
 * @tparam LEN A kapcsolatok száma
 */
template<int LEN>
class Signal {
    public:
    Color sig[LEN];  ///< A kapcsolatok színei, vagy konstans esteén az értékük
    bool isConst[LEN];      ///< Igaz, ha a jel konstans
    bool out;               ///< Igaz, ha a kapcsolatok kimenetiek

    /**
     * @brief Új Signal létrehozása
     * 
     * @param _sig A kapcsolatok színei, vagy konstans esetén az értékük
     * @param _isConst Igaz, ha az adott jel konstans
     * @param out Igaz, ha a jelek kimenetiek
     */
    Signal(const Color _sig[LEN], const bool _isConst[LEN], bool out = false):out(out){
        for(int i=0; i<LEN; i++){
            sig[i] = _sig[i];
            isConst[i] = _isConst[i];
        }
    }

    /**
     * @brief Visszaadja az idx. jelet
     * 
     * @param idx Index
     * @return Color A jel színe/értéke
     */
    Color getSig(int idx) const {return sig[idx];}

    /**
     * @brief Visszaadja, hogy az idx. jel konstans-e
     * 
     * @param idx Index
     * @return true Ha a jel konstans
     * @return false Egyébként
     */
    bool getConst(int idx) const {return isConst[idx];}
};

/**
 * @brief Signal specializálásra 1 hosszra kényelem érdekében
 * 
 * @tparam  
 */
template<>
class Signal<1>{
    public:
    Color sig;  ///< A kapcsolat színe, vagy konstans esetén az értéke
    bool isConst;      ///< Igaz, ha a jel konstans
    bool out;               ///< Igaz, ha a kapcsolatok kimenetiek

    /**
     * @brief Új Signal létrehozása
     * 
     * @param sig A kapcsolat színe, vagy konstans esetén az értéke
     * @param isConst Igaz, ha a jel konstans
     * @param out Igaz, ha a jel kimeneti
     */
    Signal(const Color sig, const bool isConst, bool out = false):
    sig(sig), isConst(isConst), out(out){}

    /**
     * @brief Visszaadja az idx. jelet
     * 
     * @param idx Index
     * @return Color A jel színe/értéke
     */
    Color getSig(int idx) const {return sig;}

    /**
     * @brief Visszaadja, hogy az idx. jel konstans-e
     * 
     * @param idx Index
     * @return true Ha a jel konstans
     * @return false Egyébként
     */
    bool getConst(int idx) const {return isConst;}
};

/**
 * @brief Jelek kiírása JSON formában
 * 
 * @tparam LEN A jelek száma
 * @param os A kimeneti stream
 * @param s A kiírandó jelek
 * @return std::ostream& A kimeneti stream
 */
template<int LEN>
std::ostream& operator<<(std::ostream& os, const Signal<LEN>& s){
    static const char* NAMES[] = {
        "first",
        "second"
    };

    if(s.out){
        return os << esc("output_signal") << ":{" <<
        esc("type") << ":" << esc("virtual") << "," <<
        esc("name") << ":\"" << s.getSig(0) << "\"}";
    }else{
        for(int i=0; i<LEN; i++){
            if(!s.getConst(i)){
                os << "\"" << NAMES[i] << "_signal\":{" <<
                esc("type") << ":" << esc("virtual") << "," <<
                esc("name") << ":\"" << s.getSig(i) << "\"}";
            }else{
                os << "\"" << NAMES[i] << "_constant\":" << s.getSig(i).toConst();
            }
            if(i+1 < LEN) os << ',';
        }
    }
    return os;

}

#endif //signals_H
