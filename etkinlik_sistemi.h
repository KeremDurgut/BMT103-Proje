#ifndef ETKINLIK_SISTEMI_H
#define ETKINLIK_SISTEMI_H

struct Katilimci {

  char isim[50];
  char soyisim[50];
  char email[100];
};

void veriyi_kaydet(const struct Katilimci *sistem, char *lineBuffer);
void kayit_ekle(struct Katilimci *sistem, const char *isim, const char *soyisim,
                const char *email, char *lineBuffer);
void kayit_iptal(struct EtkinlikKayitSistemi *sistem, const char *isim,
                 const char *soyisim);
void katilimci_listesi_goruntule(const struct EtkinlikKayitSistemi *sistem);
void show_menu(char *lineBuffer);
// extras
void numarayla_silme(int delete_line, char *lineBuffer);
void show(char *lineBuffer);
int total_lines();
void main_menu();
void ana_menu();

void etkinlik_sil(char *lineBuffer);

void delete_line(const char *filename, int line_number);

void etkinlik_liste_goruntuleme();

void main_veriyi_kaydet();

void etkinlik_ekleme();

void read_line(int line_num);
int copy_line_to_variable(const char *filename, int lineNumber,
                          char *lineBuffer);

#endif /* ETKINLIK_SISTEMI_H */
