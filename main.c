
#include "etkinlik_sistemi.h"
#include <stdio.h>

int main() {
  struct Katilimci etkinlik_sistemi;
  // etkinlik_sistemi.katilimci_sayisi = 0;

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
    case 2: {
      int silme_turu;
      show();
      printf("1. isim ile kayit silmek\n");
      printf("2. numara ile kayit silmek\n");
      scanf("%d", &silme_turu);

      switch (silme_turu) {
      case 1: {
        char isim[50], soyisim[50], email[100];
        printf("Enter Name: ");
        scanf("%49s", isim);
        printf("Enter Surname: ");
        scanf("%49s", soyisim);
        // kayit_silme(&etkinlik_sistemi, isim, soyisim);
        break;
      }
      case 2: {
        int delete_line;
        printf("Delete Line: ");
        scanf("%d", &delete_line);
        numarayla_silme(&etkinlik_sistemi, delete_line);
        break;

        break;
      }
      }
    }
    case 3:
      show();
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
