#ifndef ETKINLIK_SISTEMI_H
#define ETKINLIK_SISTEMI_H

struct Katilimci {
    char isim[50];
    char soyisim[50];
    char email[100];
};

struct EtkinlikKayitSistemi {
    struct Katilimci katilimcilar[100];
    int katilimci_sayisi;
};

void veriyi_kaydet(struct EtkinlikKayitSistemi* sistem);
void kayit_ekle(struct EtkinlikKayitSistemi* sistem, const char* isim, const char* soyisim, const char* email);
void katilimci_listesi_goruntule(const struct EtkinlikKayitSistemi* sistem);
void show_menu();

#endif /* ETKINLIK_SISTEMI_H */
