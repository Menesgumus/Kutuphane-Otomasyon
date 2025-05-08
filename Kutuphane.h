#ifndef KUTUPHANE_H
#define KUTUPHANE_H

#include <iostream>
#include <vector>
#include <map>
#include "Kitap.h"
#include "Ogrenci.h"
#include "Queue.h"
#include "Stack.h"

// kutuphane sinifi
class Kutuphane {
private:
    std::vector<Kitap> kitaplar;  // kitap listesi
    std::map<int, std::string> ogrenciler;  // ogrenci listesi
    Queue kuyruk;  // odunc alma kuyrugu
    Stack yigin;   // iade edilen kitaplar

public:
    Kutuphane() {}  // constructor
    
    // kitap ekleme
    void kitapEkle(Kitap k) {
        kitaplar.push_back(k);
    }
    
    // ogrenci ekleme
    void ogrenciEkle(int id, std::string ad) {
        ogrenciler[id] = ad;
    }
    
    // kitap arama
    Kitap* kitapAra(int id) {
        for (auto& k : kitaplar) {
            if (k.getKitapId() == id) return &k;
        }
        return nullptr;
    }
    
    // kitaplari listele
    void kitaplariListele() {
        for (auto& k : kitaplar) {
            std::cout << "ID: " << k.getKitapId() 
                      << " | Kitap: " << k.getKitapAdi()
                      << " | Yazar: " << k.getYazar()
                      << " | Stok: " << k.getKitapAdet() << std::endl;
        }
    }
    
    // odunc alma
    bool oduncAl(int ogrenci_id, int kitap_id) {
        // ogrenci kontrolu
        if (ogrenciler.find(ogrenci_id) == ogrenciler.end()) {
            std::cout << "Ogrenci yok!" << std::endl;
            return false;
        }
        
        // kitap kontrolu
        Kitap* k = kitapAra(kitap_id);
        if (k == nullptr) {
            std::cout << "Kitap yok!" << std::endl;
            return false;
        }
        
        // stok kontrolu
        if (k->getKitapAdet() > 0) {
            k->azaltStok();
            Ogrenci o(ogrenci_id, ogrenciler[ogrenci_id], kitap_id, 1);
            kuyruk.enqueue(o);
            std::cout << "Kitap verildi!" << std::endl;
            return true;
        }
        
        std::cout << "Stok yok!" << std::endl;
        return false;
    }
    
    // iade etme
    bool iadeEt(int ogrenci_id, int kitap_id) {
        // ogrenci kontrolu
        if (ogrenciler.find(ogrenci_id) == ogrenciler.end()) {
            std::cout << "Ogrenci yok!" << std::endl;
            return false;
        }
        
        // kitap kontrolu
        Kitap* k = kitapAra(kitap_id);
        if (k == nullptr) {
            std::cout << "Kitap yok!" << std::endl;
            return false;
        }
        
        // iade islemi
        k->arttirStok();
        Ogrenci o(ogrenci_id, ogrenciler[ogrenci_id], kitap_id, 0);
        yigin.push(o);
        std::cout << "Kitap iade edildi!" << std::endl;
        return true;
    }
    
    // kuyruk goster
    void oduncAlmaKuyrugu() {
        kuyruk.display();
    }
    
    // yigin goster
    void iadeEdilenKitaplar() {
        yigin.display();
    }
};

#endif 