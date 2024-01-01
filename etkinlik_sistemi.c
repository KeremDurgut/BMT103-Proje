#include "etkinlik_sistemi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void veriyi_kaydet(struct EtkinlikKayitSistemi* sistem) {
    FILE *dosya = fopen("etkinlik_kayit.txt", "a+");
    if (dosya == NULL) {
        perror("Dosya acilirken hata olustu");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < sistem->katilimci_sayisi; i++) {
        fprintf(dosya, "%s,%s,%s\n", sistem->katilimcilar[i].isim, sistem->katilimcilar[i].soyisim, sistem->katilimcilar[i].email);
    }

    fclose(dosya);
}


void kayit_ekle(struct EtkinlikKayitSistemi* sistem, const char* isim, const char* soyisim, const char* email) {
    if (sistem->katilimci_sayisi < 100) {
        struct Katilimci yeni_katilimci;
        strcpy(yeni_katilimci.isim, isim);
        strcpy(yeni_katilimci.soyisim, soyisim);
        strcpy(yeni_katilimci.email, email);

        sistem->katilimcilar[sistem->katilimci_sayisi++] = yeni_katilimci;
        veriyi_kaydet(sistem);
    } else {
        printf("Katilimci limitine ulastiniz!\n");
    }
}

void katilimci_listesi_goruntule(const struct EtkinlikKayitSistemi* sistem) {
    printf("Katilimcilar Listesi:\n");
    for (int i = 0; i < sistem->katilimci_sayisi; i++) {
        printf("%s %s - %s\n", sistem->katilimcilar[i].isim, sistem->katilimcilar[i].soyisim, sistem->katilimcilar[i].email);
    }
}

void show_menu() {
    printf("Welcome to the Kayit Sistemi\n");
    printf("1. Kayit Ekle\n");
    printf("2. Katilimci Listesi Goruntule\n");
    printf("0. Cikis\n");
    printf("Choose an option: ");
}
