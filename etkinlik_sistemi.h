#ifndef ETKINLIK_SISTEMI_H
#define ETKINLIK_SISTEMI_H

struct Katilimci {

  char isim[50];
  char soyisim[50];
  char email[100];
};

// struct EtkinlikKayitSistemi {
  // is there any need of using struct here
  // struct Katilimci katilimcilar;
  // int katilimci_sayisi;
// };

void veriyi_kaydet(const struct Katilimci *sistem);
void kayit_ekle(struct Katilimci *sistem, const char *isim,
                const char *soyisim, const char *email);
void kayit_iptal(struct EtkinlikKayitSistemi *sistem, const char *isim,
                 const char *soyisim);
void katilimci_listesi_goruntule(const struct EtkinlikKayitSistemi *sistem);
void show_menu();
// extras
void numarayla_silme(struct Katilimci *sistem, int delete_line);
void show();
int total_lines();
void main_menu();

void main_veriyi_kaydet();
#endif /* ETKINLIK_SISTEMI_H */
