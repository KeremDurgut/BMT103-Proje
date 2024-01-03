#include "etkinlik_sistemi.h"
#include <stdio.h>

int main() {
  struct Katilimci etkinlik_sistemi;
  int choice;

  do {
    ana_menu();
    scanf("%d", &choice);
    getchar(); // yeni satiri bufferdan siliyor

    switch (choice) {
    case 1:
      etkinlik_ekleme();
      break;

    case 2: {
      char etkinlik_listesi[30] = "etkinlik_listesi.txt";
      int islem;
      
      etkinlik_liste_goruntuleme();
      
      printf("\nHangi etkinlikle işlem yapmak istiyorsunuz: ");
      scanf("%d", &islem);
      
      const char *filename = "etkinlik_listesi.txt";
      int lineNumber = islem;
      char file[256];

      if (copy_line_to_variable(filename, lineNumber, file)) { 

      } else {
        printf("girdiginiz etkinlik bulunmamaktadir.\n", lineNumber);
      }

      etkinlik_sil(file);

      // we have to edit this
      delete_line(etkinlik_listesi, lineNumber);
      break;
    }

    case 3: {
      int islem;
      etkinlik_liste_goruntuleme();
      printf("\nHangi etkinlikle işlem yapmak istiyorsunuz:\n ");
      scanf("%d", &islem);
      const char *filename = "etkinlik_listesi.txt";
      int lineNumber = islem;
      char file[256];

      if (copy_line_to_variable(filename, lineNumber, file)) {
        printf("%d: %s", lineNumber, file);
      } else {
        printf("%d satir bulunmadi.\n", lineNumber);
      }

      int secim;
          do {
              show_menu(file);

              scanf("%d", &secim);

          switch (secim) {
                case 1: {
                       char isim[50], soyisim[50], email[100];
                        printf("Isim giriniz: ");
                         scanf("%49s", isim);
                         printf("soy isim giriniz: ");
                        scanf("%49s", soyisim);
                         printf("Email giriniz: ");
                         scanf("%99s", email);
                         kayit_ekle(&etkinlik_sistemi, isim, soyisim, email, file);
                          break;
                                }

                case 2: {

          // isim silmek icin index kullaniyouruz
                          int line_to_delete;
                       do {
                            printf("silmek istediginiz indeksi yaziniz ya da ");
                            printf("Menu'ye geri dönmek için 0: ");
                            scanf("%d", &line_to_delete);

                             numarayla_silme(line_to_delete, file);
                           } while (line_to_delete != 0);

                          break;
                                   }

                 case 3:{ 
                          show_file(file);
                          break;
                        } 


        }

      } while (secim != 0);

      break;
    }

    case 0:
      printf("Exiting...\n");
      break;

    default:
      printf("hatali secim\n");
      break;
    }
  } while (choice != 0);

  return 0;
}
