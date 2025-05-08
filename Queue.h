#ifndef QUEUE_H
#define QUEUE_H

#include "Ogrenci.h"
#include <iostream>

// kuyruk dugumu
class QueueNode {
public:
    Ogrenci ogrenci;  // ogrenci bilgileri
    QueueNode* sonraki;  // sonraki dugum
    
    // constructor
    QueueNode(Ogrenci o) {
        ogrenci = o;
        sonraki = NULL;  // baslangicta sonraki dugum yok
    }
};

// kuyruk sinifi
class Queue {
private:
    QueueNode* bas;  // kuyrugun basi
    QueueNode* son;  // kuyrugun sonu
    
public:
    // constructor
    Queue() {
        bas = NULL;
        son = NULL;
    }
    
    // destructor
    ~Queue() {
        // bellek temizleme
    }
    
    // kuyruga ekleme
    void enqueue(Ogrenci o) {
        QueueNode* yeni = new QueueNode(o);
        
        if (son == NULL) {
            bas = son = yeni;
            return;
        }
        
        son->sonraki = yeni;
        son = yeni;
    }
    
    // kuyruktan cikarma
    Ogrenci dequeue() {
        if (bas == NULL) {
            return Ogrenci();  // bos kuyruk
        }
        
        QueueNode* temp = bas;
        Ogrenci o = bas->ogrenci;
        
        bas = bas->sonraki;
        
        if (bas == NULL) {
            son = NULL;
        }
        
        delete temp;
        return o;
    }
    
    // kuyruk bos mu?
    bool isEmpty() {
        return bas == NULL;
    }
    
    // kuyrugu goster
    void display() {
        if (isEmpty()) {
            std::cout << "Kuyruk bos!" << std::endl;
            return;
        }
        
        QueueNode* temp = bas;
        while (temp != NULL) {
            std::cout << "Ogrenci ID: " << temp->ogrenci.getOgrenciId() 
                      << " | Ad: " << temp->ogrenci.getAdSoyad()
                      << " | Kitap: " << temp->ogrenci.getKitapId() << std::endl;
            temp = temp->sonraki;
        }
    }
};

#endif 