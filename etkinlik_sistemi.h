#ifndef ETKINLIK_SISTEMI_H
#define ETKINLIK_SISTEMI_H

struct Katilimci {

  char isim[50];
  char soyisim[50];
  char email[100];
};

void veriyi_kaydet(const struct Katilimci *sistem, char *file);
void kayit_ekle(struct Katilimci *sistem, const char *isim, const char *soyisim,
                const char *email, char *file);

void show_menu(char *file);

void numarayla_silme(int delete_line, char *file_name);
void show_file(char *file_input);
int total_lines();

void ana_menu();

void etkinlik_sil(char *etkinlik_name);

void delete_line(const char *filename, int line_number);

void etkinlik_liste_goruntuleme();



void etkinlik_ekleme();


int copy_line_to_variable(const char *filename, int lineNumber,
                          char *lineBuffer);

#endif /* ETKINLIK_SISTEMI_H */
