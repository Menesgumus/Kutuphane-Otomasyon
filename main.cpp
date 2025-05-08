#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Kitap.h"
#include "Ogrenci.h"
#include "Node.h"
#include "Queue.h"
#include "Stack.h"

// kutuphane sinifi
class Kutuphane {
private:
    Node* bas;  // baslangic dugumu
    Queue kuyruk;  // odunc alma kuyrugu
    Stack yigin;   // iade edilen kitaplar
    
public:
    // constructor
    Kutuphane() {
        bas = NULL;  // baslangicta bos
    }
    
    // kitap ekleme
    void kitapEkle(Kitap k) {
        Node* yeni = new Node(k);
        
        if (bas == NULL) {
            bas = yeni;
            return;
        }
        
        Node* temp = bas;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = yeni;
    }
    
    // kitaplari listele
    void kitaplariListele() {
        if (bas == NULL) {
            std::cout << "Kutuphanede kitap yok!" << std::endl;
            return;
        }
        
        Node* temp = bas;
        while (temp != NULL) {
            std::cout << "ID: " << temp->kitap.getKitapId() 
                      << " | Kitap: " << temp->kitap.getKitapAdi()
                      << " | Yazar: " << temp->kitap.getYazar()
                      << " | Stok: " << temp->kitap.getKitapAdet() << std::endl;
            temp = temp->next;
        }
    }
    
    // kitap arama
    Kitap* kitapAra(int id) {
        Node* temp = bas;
        while (temp != NULL) {
            if (temp->kitap.getKitapId() == id) {
                return &(temp->kitap);
            }
            temp = temp->next;
        }
        return NULL;
    }
    
    // odunc alma
    void oduncAl(int ogrenci_id, int kitap_id) {
        Kitap* k = kitapAra(kitap_id);
        
        if (k == NULL) {
            std::cout << "Kitap yok!" << std::endl;
            return;
        }
        
        // ogrenci bilgilerini oku
        std::ifstream dosya("Ogrenciler.txt");
        if (!dosya.is_open()) {
            std::cout << "Dosya acilamadi!" << std::endl;
            return;
        }
        
        std::string satir;
        std::getline(dosya, satir);  // baslik satirini atla
        std::string ad;
        bool bulundu = false;
        
        while (std::getline(dosya, satir)) {
            std::stringstream ss(satir);
            int id;
            ss >> id;
            if (id == ogrenci_id) {
                ss >> ad;
                bulundu = true;
                break;
            }
        }
        dosya.close();
        
        if (!bulundu) {
            std::cout << "Ogrenci yok!" << std::endl;
            return;
        }
        
        if (k->getKitapAdet() > 0) {
            k->setKitapAdet(k->getKitapAdet() - 1);
            Ogrenci o(ogrenci_id, ad, kitap_id, 1);
            kuyruk.enqueue(o);
            std::cout << "Kitap verildi!" << std::endl;
            std::cout << "Ogrenci: " << ad << " (ID: " << ogrenci_id << ")" << std::endl;
            std::cout << "Kitap: " << k->getKitapAdi() << " (ID: " << kitap_id << ")" << std::endl;
            std::cout << "Stok: " << k->getKitapAdet() << std::endl;
        } else {
            std::cout << "Stok yok, kuyruga ekleniyor..." << std::endl;
            Ogrenci o(ogrenci_id, ad, kitap_id, 1);
            kuyruk.enqueue(o);
            std::cout << "Kuyruga eklendi!" << std::endl;
        }
    }
    
    // iade etme
    void iadeEt(int ogrenci_id, int kitap_id) {
        Kitap* k = kitapAra(kitap_id);
        
        if (k == NULL) {
            std::cout << "Kitap yok!" << std::endl;
            return;
        }
        
        k->setKitapAdet(k->getKitapAdet() + 1);
        Ogrenci o(ogrenci_id, "", kitap_id, 0);
        yigin.push(o);
        std::cout << "Kitap iade edildi!" << std::endl;
        
        if (!kuyruk.isEmpty()) {
            Ogrenci bekleyen = kuyruk.dequeue();
            if (bekleyen.getKitapId() == kitap_id) {
                k->setKitapAdet(k->getKitapAdet() - 1);
                std::cout << "Bekleyen ogrenciye verildi!" << std::endl;
            }
        }
    }
    
    // kuyruk goster
    void oduncKuyrukGoster() {
        std::cout << "\nOdunc Alma Kuyrugu:" << std::endl;
        kuyruk.display();
    }
    
    // yigin goster
    void iadeYiginGoster() {
        std::cout << "\nSon Iade Edilen Kitaplar:" << std::endl;
        yigin.display();
    }
};

// ana program
int main() {
    Kutuphane k;
    
    // kitaplari yukle
    std::ifstream dosya("Kitaplar.txt");
    if (!dosya.is_open()) {
        std::cout << "Dosya acilamadi!" << std::endl;
        return 1;
    }
    
    std::string satir;
    std::getline(dosya, satir);  // baslik satirini atla
    
    while (std::getline(dosya, satir)) {
        std::stringstream ss(satir);
        int id, adet;
        std::string ad, yazar;
        
        ss >> id >> ad >> yazar >> adet;
        k.kitapEkle(Kitap(id, ad, yazar, adet));
    }
    dosya.close();
    
    std::cout << "Sistem baslatildi.\n\n";
    
    int secim;
    while (1) {  // sonsuz dongu
        std::cout << "\nKutuphane Sistemi\n";
        std::cout << "1. Kitaplari Listele\n";
        std::cout << "2. Kitap Ara\n";
        std::cout << "3. Kitap Odunc Al\n";
        std::cout << "4. Kitap Iade Et\n";
        std::cout << "5. Odunc Alma Kuyrugu\n";
        std::cout << "6. Iade Edilen Kitaplar\n";
        std::cout << "0. Cikis\n";
        std::cout << "Secim: ";
        std::cin >> secim;
        
        if (secim == 0) break;
        
        switch (secim) {
            case 1:
                k.kitaplariListele();
                break;
            case 2: {
                int id;
                std::cout << "Kitap ID: ";
                std::cin >> id;
                Kitap* kitap = k.kitapAra(id);
                if (kitap != NULL) {
                    std::cout << "\nKitap Bilgileri:" << std::endl;
                    std::cout << "ID: " << kitap->getKitapId() << std::endl;
                    std::cout << "Ad: " << kitap->getKitapAdi() << std::endl;
                    std::cout << "Yazar: " << kitap->getYazar() << std::endl;
                    std::cout << "Stok: " << kitap->getKitapAdet() << std::endl;
                } else {
                    std::cout << "Kitap yok!" << std::endl;
                }
                break;
            }
            case 3: {
                int ogrenci_id, kitap_id;
                std::cout << "Ogrenci ID: ";
                std::cin >> ogrenci_id;
                std::cout << "Kitap ID: ";
                std::cin >> kitap_id;
                k.oduncAl(ogrenci_id, kitap_id);
                break;
            }
            case 4: {
                int ogrenci_id, kitap_id;
                std::cout << "Ogrenci ID: ";
                std::cin >> ogrenci_id;
                std::cout << "Kitap ID: ";
                std::cin >> kitap_id;
                k.iadeEt(ogrenci_id, kitap_id);
                break;
            }
            case 5:
                k.oduncKuyrukGoster();
                break;
            case 6:
                k.iadeYiginGoster();
                break;
            default:
                std::cout << "Hatali secim!\n";
        }
    }
    
    return 0;
} 