#include "etkinlik_sistemi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_SIZE 1024
#define MAX_LINE 2048
#define MAX_LINE_SIZE 256

void veriyi_kaydet(const struct Katilimci *sistem, char *file) {
  char event[30];
  strcpy(event, file);
  strcat(event, ".txt"); // açılacak dosyanın ismine .txt eklenmesi.
  FILE *dosya = fopen(event, "a+"); // .txt uzantılı olan stringimizle dosya açılması.
  if (dosya == NULL) {
    perror("Dosya acilirken hata olustu"); // klasik error kodu.
    exit(EXIT_FAILURE);
  }
  // dosyaya girilen verilerin eklenmesi.
  fprintf(dosya, "%s,%s - %s\n", sistem->isim, sistem->soyisim, sistem->email);

  fclose(dosya); // dosyayı kapat. 
}

void kayit_ekle(struct Katilimci *sistem, const char *isim, const char *soyisim,
                const char *email, char *file) {

  struct Katilimci yeni_katilimci; // kurulan yapıyla yeni değişken oluşturulması.
  strcpy(yeni_katilimci.isim, isim);
  strcpy(yeni_katilimci.soyisim, soyisim); // verilerin değişkenlere atanması.
  strcpy(yeni_katilimci.email, email);

  sistem = &yeni_katilimci;
  veriyi_kaydet(sistem, file); // üstte tanımlanılan dosyaya kaydetme fonksiyonu
  
}

void show_menu(char *file) {
  printf("\n-----------------------------------------------\n");
  printf("|   Etkinlik ismi:  %s                        |\n", file);
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
void show_file(char *file_input) {
  FILE *file;
  int lines = total_lines();
  char event[30];
  strcpy(event, file_input);
  strcat(event, ".txt");

  file= fopen(event, "r");

  if (file != NULL) {
    // read each character of the file one at a time until end of file (EOF) is
    // returned to signify the end of the file, output each char to the console
    char c;
    int i = 1;

    // printf("%d ", 1);
    while ((c = fgetc(file)) != EOF) {
      putchar(c); // Print each character

      if (c == '\n') {

        printf("%d ", i); // Print the line number
        i++;
      }
    }

    fclose(file);

  } else {
    printf("Error opening file.\n");
  }
}

void numarayla_silme(int delete_line, char *file_name) {

  char event[30];
  strcpy(event, file_name);
  strcat(event, ".txt");

  FILE *file, *temp;
  char filename[FILENAME_SIZE];
  strcpy(filename, event);
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

void etkinlik_ekleme() {

  char etkinlik_ismi[30];
  printf("Ekleyeceginiz etkinligin ismini giriniz.\n");
  // scanf("%s",etkinlik_ismi);
  fgets(etkinlik_ismi, sizeof(etkinlik_ismi), stdin);

  char etkinlikdosyasi[33];
  strcpy(etkinlikdosyasi, etkinlik_ismi);
  strcat(etkinlikdosyasi, ".txt");

  FILE *dosya = fopen(etkinlikdosyasi, "a+");
  if (dosya == NULL) {
    perror("Dosya Acilirken Hata Olustu.\n");
    exit(EXIT_FAILURE);
  } else {
    fclose(dosya);
  }

  FILE *dosya2 = fopen("etkinlik_listesi.txt", "a+");
  if (dosya2 == NULL) {
    perror("Etkinlik Listesi Acilirken Hata Olustu.\n");
    exit(EXIT_FAILURE);
  } else {
    fprintf(dosya2, "%s\n", etkinlik_ismi);
    fclose(dosya2);
  }
}

// trial things

// void etkinlik_show(char *lineBuffer) {
//   FILE *file;
//   int lines = total_lines();
//   char event[30];
//   strcpy(event, lineBuffer);
//   strcat(event, ".txt");

//   file= fopen(event, "r");

//   if (file != NULL) {
//     // read each character of the file one at a time until end of file (EOF) is
//     // returned to signify the end of the file, output each char to the console
//     char c;
//     int i = 1;

//     // printf("%d ", 1);
//     while ((c = fgetc(file)) != EOF) {
//       putchar(c); // Print each character

//       if (c == '\n') {

//         printf("%d ", i); // Print the line number
//         i++;
//       }
//     }

//     fclose(file);

//   } else {
//     printf("Error opening file.\n");
//   }
// }

void ana_menu() {
  
  printf("\n----------------------------------------------\n");
  printf("|          Etkinlik Menu:                      |\n\n");
  printf("|       1. Etkinlik Ekle                       |\n");
  printf("|       2. Etkinlik Kaldir                     |\n");
  printf("|       3. Etkinlik Listesi Goruntule          |\n");
  printf("|       0. Cikis                               |\n");
  printf("------------------------------------------------\n");
  printf("seciminiz yapin: ");
}

void etkinlik_liste_goruntuleme() {
  FILE *etkinlikler = fopen("etkinlik_listesi.txt", "r");

  if (etkinlikler != NULL) {
    char c;
    int line_number = 2;
    int char_position = 0;
    printf("%d ", 1);

    while ((c = fgetc(etkinlikler)) != EOF) {
      putchar(c);

      if (c == '\n') {
        printf("%d ",
               line_number); // Print the line number at the end of each line
        line_number++;
        char_position = 0; // Reset the character position for the new line
      } else {
        char_position++;
      }
    }

    fclose(etkinlikler);
  } else {
    printf("Error opening file.\n");
  }
}

int copy_line_to_variable(const char *filename, int lineNumber,
                          char *file_name) {

  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    perror("Error opening file");
    return 0;
  }

  int currentLine = 1;

  // Read lines from the file
  while (fgets(file_name, MAX_LINE_SIZE, file) != NULL) {
    if (currentLine == lineNumber) {
      fclose(file);
      return 1; // Line found and copied to lineBuffer
    }

    currentLine++;
  }

  fclose(file);
  return 0; // Line not found or file couldn't be opened
}

void etkinlik_sil(char *etkinlik_name) {
  int ret;
  char event[30];
  strcpy(event, etkinlik_name);
  strcat(event, ".txt");

  FILE *fp;
  char filename[100];
  strcpy(filename, event);

  fp = fopen(filename, "w");

  fprintf(fp, "%s", "This is tutorialspoint.com");
  fclose(fp);

  ret = remove(filename);

  if (ret == 0) {
    printf("File deleted successfully");
  } else {
    printf("Error: unable to delete the file");
  }
}

// void etkinlik_ismi_sil()
void delete_line(const char *filename, int line_number) {
  FILE *file, *temp;
  int current_line = 1;
  char buffer[1024];

  file = fopen(filename, "r");
  temp = fopen("temp_file.txt", "w");

  if (file == NULL || temp == NULL) {
    perror("Error opening file");
    return;
  }

  // Read each line from the file
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    // Skip the line to be deleted
    if (current_line != line_number) {
      fputs(buffer, temp);
    }
    current_line++;
  }

  fclose(file);
  fclose(temp);

  // Remove the original file
  remove(filename);

  // Rename the temporary file to the original filename
  rename("temp_file.txt", filename);
}
