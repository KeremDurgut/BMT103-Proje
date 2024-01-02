#include "etkinlik_sistemi.h"
#include <stdio.h>

int main() {
  struct Katilimci etkinlik_sistemi;
  int choice;

  do {
    ana_menu();
    scanf("%d", &choice);
    getchar(); // Clear the newline from the buffer

    switch (choice) {
      case 1:
        etkinlik_ekleme();
        break;

      case 2: {
        char etkinlik_listesi[30]="etkinlik_listesi.txt";
        int islem;
        etkinlik_liste_goruntuleme();
        printf("Hangi etkinlikle işlem yapmak istiyorsunuz: ");
        scanf("%d", &islem);
        const char *filename = "etkinlik_listesi.txt";
        int lineNumber = islem;
        char lineBuffer[256];

        if (copy_line_to_variable(filename, lineNumber, lineBuffer)) {
          printf("Line %d: %s", lineNumber, lineBuffer);
        } else {
          printf("Line %d not found or file couldn't be opened.\n", lineNumber);
        }

        etkinlik_sil(lineBuffer);
        numarayla_silme(lineNumber,etkinlik_listesi );
        break;
      }

      case 3: {
        int islem;
        etkinlik_liste_goruntuleme();
        printf("Hangi etkinlikle işlem yapmak istiyorsunuz: ");
        scanf("%d", &islem);
        const char *filename = "etkinlik_listesi.txt";
        int lineNumber = islem;
        char lineBuffer[256];

        if (copy_line_to_variable(filename, lineNumber, lineBuffer)) {
          printf("Line %d: %s", lineNumber, lineBuffer);
        } else {
          printf("Line %d not found or file couldn't be opened.\n", lineNumber);
        }
        int secim;
        do {
          show_menu(lineBuffer);
          // int secim;
          scanf("%d", &secim);

          switch (secim) {
            case 1: {
              char isim[50], soyisim[50], email[100];
              printf("Enter Name: ");
              scanf("%49s", isim);
              printf("Enter Surname: ");
              scanf("%49s", soyisim);
              printf("Enter Email: ");
              scanf("%99s", email);
              kayit_ekle(&etkinlik_sistemi, isim, soyisim, email, lineBuffer);
              break;
            }

            case 2: {
              int line_to_delete;
              do {
                printf("Write the line number that you want to delete: ");
                printf("Menu'ye geri dönmek için 0: ");
                scanf("%d", &line_to_delete);

                numarayla_silme(line_to_delete, lineBuffer);
              } while (line_to_delete != 0);

              break;
            }

            case 3:
              show(lineBuffer);
              break;

            default:
              printf("Invalid choice. Please choose again.\n");
              break;
          }

        } while (secim != 0);

        break;
      }

      case 0:
        printf("Exiting...\n");
        break;

      default:
        printf("Invalid choice. Please choose again.\n");
        break;
    }
  } while (choice != 0);

  return 0;
}
