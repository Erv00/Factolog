#include "base64.h"

const char Base64::ALPHABET[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'
};

void Base64::feedChar(char c){
    switch(bitsRemaining){
        case 0:
            //First
            buf += ALPHABET[c>>2];
            remaining = (c & 3) << 4;
            bitsRemaining = 2;
            break;
        case 2:
            //Second
            buf += ALPHABET[remaining|(c>>4)];
            remaining = (c & 15) << 2;
            bitsRemaining = 4;
            break;
        case 4:
            //Third
            buf += ALPHABET[remaining|(c>>6)];
            buf += ALPHABET[c&63];
            bitsRemaining = 0;
            break;
    }
}

void Base64::encode(const char* data, size_t len){
    if(len==0) len=strlen(data);

    for(size_t i=0; i<len; i++)
        feedChar(data[i]);
}

void Base64::addPadding(){
    switch(bitsRemaining){
        case 2:
            //Need to add two =
            feedChar(0);
            buf += "==";
            bitsRemaining = 0;
            break;
        case 4:
            //Need to add one =
            feedChar(0);
            //The call above added an other char, override
            *(buf.end()-1) = '=';
            bitsRemaining = 0;
            break;
    }
}

std::ostream& operator<<(std::ostream& os, Base64& b64){
    //Add padding
    b64.addPadding();

    os << b64.getBuf();
    b64.getBuf().clear();

    return os;
}
