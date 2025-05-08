#ifndef NODE_H
#define NODE_H

#include "Kitap.h"

// dugum sinifi
class Node {
public:
    Kitap kitap;  // kitap bilgileri
    Node* next;  // sonraki dugum
    
    // constructor
    Node(Kitap k) {
        kitap = k;
        next = NULL;  // baslangicta sonraki dugum yok
    }
    
    // destructor
    ~Node() {
        // bellek temizleme
    }
};

#endif 