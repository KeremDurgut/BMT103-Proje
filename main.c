
#include <stdio.h>
#include "etkinlik_sistemi.h"




int main() {
    struct EtkinlikKayitSistemi etkinlik_sistemi;
    etkinlik_sistemi.katilimci_sayisi = 0;

    int choice;
    do {
        show_menu();
        scanf("%d", &choice);
        getchar(); // Clear the newline from the buffer

        switch (choice) {
            case 1: {
                char isim[50], soyisim[50], email[100];
                printf("Enter Name: ");
                scanf("%49s", isim);
                printf("Enter Surname: ");
                scanf("%49s", soyisim);
                printf("Enter Email: ");
                scanf("%99s", email);
                kayit_ekle(&etkinlik_sistemi, isim, soyisim, email);
                break;
            }
            case 2:
                katilimci_listesi_goruntule(&etkinlik_sistemi);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please choose again.\n");
        }
    } while (choice != 0);

    return 0;
}
