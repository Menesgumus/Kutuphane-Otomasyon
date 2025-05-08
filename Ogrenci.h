#ifndef OGRENCI_H
#define OGRENCI_H

#include <string>

// ogrenci sinifi
class Ogrenci {
private:
    int id;  // ogrenci numarasi
    std::string ad;  // ogrenci adi
    int kitap_no;  // alinan kitap numarasi
    int durum;  // 0=iade edildi, 1=alindi
    
public:
    // constructor
    Ogrenci(int i = 0, std::string a = "", int k = 0, int d = 0) {
        id = i;
        ad = a;
        kitap_no = k;
        durum = d;
    }
    
    // getter fonksiyonlari
    int getOgrenciId() {
        return id;
    }
    
    std::string getAdSoyad() {
        return ad;
    }
    
    int getKitapId() {
        return kitap_no;
    }
    
    int getDurum() {
        return durum;
    }
    
    // setter fonksiyonu
    void setDurum(int d) {
        durum = d;
    }
    
    // destructor
    ~Ogrenci() {
        // bellek temizleme
    }
};

#endif 