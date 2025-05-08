#ifndef STACK_H
#define STACK_H

#include "Ogrenci.h"
#include <iostream>

// yigin dugumu
struct StackNode {
    Ogrenci ogrenci;  // ogrenci bilgileri
    StackNode* sonraki;  // sonraki dugum
    
    // constructor
    StackNode(Ogrenci o) {
        ogrenci = o;
        sonraki = NULL;  // baslangicta sonraki dugum yok
    }
};

// yigin sinifi
class Stack {
private:
    StackNode* ust;  // yiginin ustu
    
public:
    // constructor
    Stack() {
        ust = NULL;
    }
    
    // destructor
    ~Stack() {
        // bellek temizleme
    }
    
    // yigina ekleme
    void push(Ogrenci o) {
        StackNode* yeni = new StackNode(o);
        yeni->sonraki = ust;
        ust = yeni;
    }
    
    // yigindan cikarma
    Ogrenci pop() {
        if (isEmpty()) {
            return Ogrenci();  // bos yigin
        }
        
        StackNode* temp = ust;
        Ogrenci o = ust->ogrenci;
        
        ust = ust->sonraki;
        delete temp;
        
        return o;
    }
    
    // yigin bos mu?
    bool isEmpty() {
        return ust == NULL;
    }
    
    // yigini goster
    void display() {
        if (isEmpty()) {
            std::cout << "Yigin bos!" << std::endl;
            return;
        }
        
        StackNode* temp = ust;
        while (temp != NULL) {
            std::cout << "Ogrenci ID: " << temp->ogrenci.getOgrenciId() 
                      << " | Ad: " << temp->ogrenci.getAdSoyad()
                      << " | Kitap: " << temp->ogrenci.getKitapId() << std::endl;
            temp = temp->sonraki;
        }
    }
};

#endif 