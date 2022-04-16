#ifndef signals_H
#define signals_H

#include <ostream>

template <typename T>
std::string esc(const T& s){
    std::string ret = "\"";
    ret += s;
    ret += "\"";
    return ret;
}

template<int LEN>
class Signal {
    public:
    unsigned int sig[LEN];
    bool isConst[LEN];
    bool out;

    Signal(const unsigned int _sig[LEN], const bool _isConst[LEN], bool out = false):out(out){
        for(int i=0; i<LEN; i++){
            sig[i] = _sig[i];
            isConst[i] = _isConst[i];
        }
    }

    unsigned int getSig(int idx) const {return sig[idx];}
    bool getConst(int idx) const {return isConst[idx];}
};

template<>
class Signal<1>{
    public:
    const unsigned int sig;
    const bool isConst;
    bool out;

    Signal(const unsigned int sig, const bool isConst, bool out = false):
    sig(sig), isConst(isConst), out(out){}

    unsigned int getSig(int idx) const {return sig;}
    bool getConst(int idx) const {return isConst;}
};

template<int LEN>
std::ostream& operator<<(std::ostream& os, const Signal<LEN>& s){
    static const char* NAMES[] = {
        "first",
        "second"
    };

    if(s.out){
        return os << esc("output_signal") << ":{" <<
        esc("type") << ":" << esc("virtual") << "," <<
        esc("name") << ":\"signal-" << (char)('A'+s.getSig(0)-1) << "\"}";
    }else{
        for(int i=0; i<LEN; i++){
            if(!s.getConst(i)){
                os << "\"" << NAMES[i] << "_signal\":{" <<
                esc("type") << ":" << esc("virtual") << "," <<
                esc("name") << ":\"signal-" << (char)('A'+s.getSig(i)-1) << "\"}";
            }else{
                os << "\"" << NAMES[i] << "_constant\":" << s.getSig(i);
            }
            if(i+1 < LEN) os << ',';
        }
    }
    return os;

}

#endif //signals_H
