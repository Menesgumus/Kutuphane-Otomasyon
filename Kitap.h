#ifndef KITAP_H
#define KITAP_H

#include <string>

// Kitap sinifi - kutuphane sistemindeki kitaplari temsil eder
class Kitap {
private:
    int kitap_id;  // kitabin benzersiz numarasi
    std::string kitapAdi;  // kitabin adi
    std::string yazar;     // yazarin adi
    int stok;             // stok miktari
    
public:
    // constructor
    Kitap(int id = 0, std::string ad = "", std::string y = "", int adet = 0) {
        kitap_id = id;
        kitapAdi = ad;
        yazar = y;
        stok = adet;
    }
    
    // getter fonksiyonlari
    int getKitapId() const { 
        return kitap_id; 
    }
    
    std::string getKitapAdi() const { 
        return kitapAdi; 
    }
    
    std::string getYazar() const { 
        return yazar; 
    }
    
    int getKitapAdet() const { 
        return stok; 
    }
    
    // setter fonksiyonlari
    void setKitapAdet(int adet) { 
        stok = adet; 
    }
    
    // stok islemleri
    void azaltStok() { 
        if (stok > 0) {
            stok = stok - 1;  // stok miktarini 1 azalt
        }
    }
    
    void arttirStok() { 
        stok = stok + 1;  // stok miktarini 1 arttir
    }
    
    // ekstra fonksiyon - aslinda kullanilmiyor ama olsun
    void stokGuncelle(int yeni_stok) {
        if (yeni_stok >= 0) {
            stok = yeni_stok;
        }
    }
};

#endif 