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
  FILE *dosya = fopen(event, "a+");// .txt uzantılı olan stringimizle dosya açılması.
  if (dosya == NULL) {
    perror("Dosya acilirken hata olustu");// klasik error kodu.
    exit(EXIT_FAILURE);
  }
  // dosyaya girilen verilerin eklenmesi.
  fprintf(dosya, "%s %s - %s\n", sistem->isim, sistem->soyisim, sistem->email);

  fclose(dosya);// dosyayı kapat. 
}

void kayit_ekle(struct Katilimci *sistem, const char *isim, const char *soyisim,
                const char *email, char *file) {

  struct Katilimci yeni_katilimci; // kurulan yapıyla yeni değişken oluşturulması.
  strcpy(yeni_katilimci.isim, isim);
  strcpy(yeni_katilimci.soyisim, soyisim);// verilerin değişkenlere atanması.
  strcpy(yeni_katilimci.email, email);

  sistem = &yeni_katilimci;
  veriyi_kaydet(sistem, file);// üstte tanımlanılan dosyaya kaydetme fonksiyonu
}

void show_menu(char *file) {
  printf("\n-----------------------------------------------\n");
  printf("\n");
  printf("       Etkinlik ismi:  %s                    \n", file);
  printf(" _____________________________________________\n");
  printf("|                                             |\n");
  printf("|   Etkinlik Kayit Sistemi Menu:              |\n");
  printf("|       1. Kayit Ekle                         |\n");
  printf("|       2. Kayit Iptal Et                     |\n");
  printf("|       3. Katilimci Listesi Goruntule        |\n");
  printf("|       0. Cikis                              |\n");
  printf("|_____________________________________________|\n");
  printf("seciminiz yapin: ");
}

int total_lines() {
  FILE *file;

  char filename[1024] = "etkinlik_kayit.txt";

  file = fopen(filename, "r");

  if (file == NULL) {
    printf("Dosya acilirken hata olustu.\n");
    return 1;
  }

  // c dosya daki her karakter 
  //
  int current_line = 1;
  char c;
  do {
    // file dan sonraki karakteri okuyour
    c = fgetc(file);

    if (c == '\n')
      current_line++;

    // file in sonuna kadar devam ediyour
  } while (c != EOF);


  fclose(file);

  //toplam satir sayisi veriyour

  return current_line;
}

// lets use show function inplace of katilimci listesi goruntuleme
void show_file(char *file_input) {
  FILE *file;
  int lines = total_lines();
  char event[30];
  strcpy(event, file_input);
  strcat(event, ".txt");
  printf("*********************************\n);
  file= fopen(event, "r");

  if (file != NULL) {
    // dosyanın sonuna kadar (EOF) dosyanın her karakterini birer birer okuyun.
      // dosyanın sonunu belirtmek için geri döndü, her karakteri konsola çıktı olarak gönderdi
    char c;
    int i = 2;

    printf("%d ", 1);
    while ((c = fgetc(file)) != EOF) {
      putchar(c); // her karakteri print yap

      if (c == '\n') {

        printf("%d ", i); // satir numaraini print yap
        i++;


      }
    }

    fclose(file);
  printf("*********************************\n);
    
  } else {
    printf("Error opening file.\n");
  }
}


void numarayla_silme(int delete_line, char *file_name) {

  char event[30];
  strcpy(event, file_name);// açılacak dosya ismine .txt eklenmesi.
  strcat(event, ".txt");

  FILE *file, *temp;
  char filename[FILENAME_SIZE];
  strcpy(filename, event); // filname isminde dosya ismi tutan değişken yapılması.
  char temp_filename[FILENAME_SIZE];

  char buffer[MAX_LINE];

  strcpy(temp_filename, "temp____");
  strcat(temp_filename, filename);

  file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file for reading");
    return;// jenerik dosya açma kontorlleri.
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
      keep_reading = false;// dosya sonuna gelene kadar verilerin diğer dosyaya aktarımı
    } else if (current_line != delete_line) {
      fputs(buffer, temp);
    }

    current_line++;

  } while (keep_reading);

  fclose(file);// dosyaların kapanması
  fclose(temp);

  remove(filename); // içi boşaltılan ana dosyanın kapanması
  rename(temp_filename, filename); // temp dosyasının kapanması
}

void etkinlik_ekleme() {

  char etkinlik_ismi[30];
  printf("Ekleyeceginiz etkinligin ismini giriniz: ");
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
    fprintf(dosya2, "%s", etkinlik_ismi);
    fclose(dosya2);
  }
}



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
               line_number); // her satirin sonunda yeni satir ekliyor
        line_number++;
        char_position = 0; // yeni satir icin character pozisyonu 0 yapar 
      } else {
        char_position++;
      }
    }

    fclose(etkinlikler);
  } else {
    printf("Hic bir etkinlik bulunmamaktadir\n");

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

  // dosyadan satiri okuyor
  while (fgets(file_name, MAX_LINE_SIZE, file) != NULL) {
    if (currentLine == lineNumber) {
      fclose(file);
      return 1; // satir bulunca file'ye ekliyor
    }

    currentLine++;
  }

  fclose(file);
  return 0; //Satır bulunamadı veya dosya açılamadı
}



/*Etkinlikleri silmek icin*/

/*bu fonksiyon etkinligin ismini alip o isimdeki dosyayi siliyor*/
void etkinlik_sil(char *etkinlik_name) {
  int ret;
  char event[30];   //satirdan veriyi alip .txt formatina ceviriyor
  strcpy(event, etkinlik_name);
  strcat(event, ".txt"); 

  FILE *file;
  char filename[100];
  strcpy(filename, event);  //ismi kopyaliyor ve baska bir degiskene atiyor

  file = fopen(filename, "w");



  ret = remove(filename);

  if (ret == 0) {
    printf("etkinliginiz silindi");
  } else {
    printf("Error:etkinliginiz bulunmadi");
  }
}

/*bu fonksiyon kisinin sectigi dosyayi alip ve  satiri alip  o dosyadaki o satiri siliyor*/
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

  // her satiri okuyor
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    // silmek istedigimiz satiri atliyor
    if (current_line != line_number) {
      fputs(buffer, temp);
    }
    current_line++;
  }

  fclose(file);
  fclose(temp);

  // orijinal dosyayi siliyor
  remove(filename);

  // temporary dosyanin ismini degistiriyor
  rename("temp_file.txt", filename);
}
