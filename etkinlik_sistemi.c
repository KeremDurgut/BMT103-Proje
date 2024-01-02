#include "etkinlik_sistemi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_SIZE 1024
#define MAX_LINE 2048

void veriyi_kaydet(const struct Katilimci *sistem) {
  FILE *dosya = fopen("etkinlik_kayit.txt", "a+");
  if (dosya == NULL) {
    perror("Dosya acilirken hata olustu");
    exit(EXIT_FAILURE);
  }

  // for (int i = 0; i < sistem->katilimci_sayisi; i++) {
    fprintf(dosya, "\n%s,%s - %s", sistem->isim,
            sistem->soyisim, sistem->email);
  // }

  fclose(dosya);
}

void kayit_ekle(struct Katilimci *sistem, const char *isim,
                const char *soyisim, const char *email) {
  // if (sistem->katilimci_sayisi < 100) {
    struct Katilimci yeni_katilimci;
    strcpy(yeni_katilimci.isim, isim);
    strcpy(yeni_katilimci.soyisim, soyisim);
    strcpy(yeni_katilimci.email, email);

    sistem = &yeni_katilimci;
    veriyi_kaydet(sistem);
  // } else {
  //   printf("Katilimci limitine ulastiniz!\n");
  // }
}

// void kayit_silme(struct Katilimci *sistem, const char *isim,
//                  const char *soyisim) {
//   int lines=total_lines();
//   for (int i = 0; i < lines; i++) {
//     if (strcmp(sistem->isim, isim) == 0 &&
//         strcmp(sistem->soyisim, soyisim) == 0) {
//       // Shift the elements to remove the canceled participant
//       for (int j = i; j < lines- 1; j++) {
//         sistem->katilimcilar[j] = sistem->katilimcilar[j + 1];
//       }
//       // sistem->katilimci_sayisi--;
//       printf("Kayit iptal edildi.\n");
//       veriyi_kaydet(sistem);
//       return;
//     }
//   }

//   printf("Katilimci bulunamadi.\n");
// }

// void katilimci_listesi_goruntule(const struct EtkinlikKayitSistemi *sistem) {
//   printf("Katilimcilar Listesi:\n");
//   for (int i = 0; i < sistem->katilimci_sayisi; i++) {
//     printf("%d %s %s - %s\n", i + 1, sistem->katilimcilar[i].isim,
//            sistem->katilimcilar[i].soyisim, sistem->katilimcilar[i].email);
//   }
// }

void show_menu() {
  printf("\n-----------------------------------------------\n");
  printf("|   Etkinlik Kayit Sistemi Menu:              |\n");
  printf("|       1. Kayit Ekle                         |\n");
  printf("|       2. Kayit Iptal Et                     |\n");
  printf("|       3. Katilimci Listesi Goruntule        |\n");
  printf("|       0. Cikis                              |\n");
  printf("-----------------------------------------------\n");
  printf("seciminiz yapin: ");
}

int total_lines() {
  FILE *file;

  char filename[1024] = "etkinlik_kayit.txt";

  file = fopen(filename, "r");

  if (file == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  // c will store each char in the file
  //
  int current_line = 1;
  char c;
  do {
    // read the next character from the file
    c = fgetc(file);

    if (c == '\n')
      current_line++;

    // continue until the special end of file value is returned from fgetc
  } while (c != EOF);

  // close the file since we are done with it
  fclose(file);

  // print out the number of lines found
  // printf("lines: %d\n", current_line);
  return current_line;
}

// lets use show function inplace of katilimci listesi goruntuleme
void show() {
  FILE *fh;
  int lines = total_lines();

  fh = fopen("etkinlik_kayit.txt", "r");

  if (fh != NULL) {
    // read each character of the file one at a time until end of file (EOF) is
    // returned to signify the end of the file, output each char to the console
    char c;
    int i = 1;

    // printf("%d ", 1);
    while ((c = fgetc(fh)) != EOF) {
      putchar(c); // Print each character

      if (c == '\n') {

        printf("%d ", i); // Print the line number
        i++;
      }
    }

    fclose(fh);

  } else {
    printf("Error opening file.\n");
  }
}

void numarayla_silme(struct Katilimci*sistem, int delete_line) {
  FILE *file, *temp;
  char filename[FILENAME_SIZE] = "etkinlik_kayit.txt";
  char temp_filename[FILENAME_SIZE];

  char buffer[MAX_LINE];

  strcpy(temp_filename, "temp____");
  strcat(temp_filename, filename);

  file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file for reading");
    return;
  }

  temp = fopen(temp_filename, "w");
  if (temp == NULL) {
    perror("Error opening temp file for writing");
    fclose(file);
    return;
  }

  bool keep_reading = true;
  int current_line = 1;

  do {
    fgets(buffer, MAX_LINE, file);

    if (feof(file)) {
      keep_reading = false;
    } else if (current_line != delete_line) {
      fputs(buffer, temp);
    }

    current_line++;

  } while (keep_reading);

  fclose(file);
  fclose(temp);

  remove(filename);
  rename(temp_filename, filename);
}

void main_menu() {
  printf("what do you want to do\n");
  printf("1. create another etkinlik\n");
  printf("2. make changes to the existing one");
  // this is used at the end of the sentence 0/
}

// void main_veriyi_kaydet(char *event) {
//   // char event[100];
//   printf("ente the name of the Event: ");
//   scanf("%s",event);
//   strcat(event,".txt");
//   // printf(event);
//   FILE *dosya = fopen(event, "a+");
//   if (dosya == NULL) {
//     perror("Dosya acilirken hata olustu");
//     return;
//   }
// }


void etkinlik_ekleme() {
    
    char etkinlik_ismi[30];
    printf("Ekleyeceginiz etkinligin ismini giriniz.\n");
    scanf("%s",&etkinlik_ismi);

    char etkinlikdosyasi[33];
    strcpy(etkinlikdosyasi,etkinlik_ismi);
    strcat(etkinlikdosyasi, ".txt");

    FILE* dosya = fopen(etkinlikdosyasi, "a+");
    if (dosya == NULL) {
        perror("Dosya Acilirken Hata Olustu.\n");
        exit(EXIT_FAILURE);
    } else {
        fclose(dosya);
    }

    FILE* dosya2 = fopen("etkinlik_listesi.txt", "a+");
    if (dosya2 == NULL) {
        perror("Etkinlik Listesi Acilirken Hata Olustu.\n");
        exit(EXIT_FAILURE);
    } else {
        fprintf(dosya2, "%s\n", etkinlik_ismi);
        fclose(dosya2); 
    }
}
