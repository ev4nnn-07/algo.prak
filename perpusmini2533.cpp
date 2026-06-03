#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Buku {
    char kode[10];
    char judul[50];
    char penulis[50];
    int tahun;
    int status; 
    
    struct Buku *kiri;  
    struct Buku *kanan; 
};

struct Buku *awal = NULL;
struct Buku *akhir = NULL;

void tampilBukuFilter(int status);
void printLine();
void printHeader();
void printBook(struct Buku *buku, int nomor);

void simpanFile(){
    FILE *fp = fopen("data.dat", "wb");
    if (fp == NULL) {
        printf("\n [!] Gagal membuka file database!\n");
        return;
    }
    
    struct Buku *bantu = awal;
    while (bantu != NULL) {
        fwrite(bantu, sizeof(struct Buku), 1, fp);
        bantu = bantu->kanan;
    }
    fclose(fp);
}

void loadFile(){
    FILE *fp = fopen("data.dat", "rb");
    if (fp == NULL) return; 

    struct Buku temp;
    while (fread(&temp, sizeof(struct Buku), 1, fp) == 1) {
        struct Buku *NB = (struct Buku *)malloc(sizeof(struct Buku));
        *NB = temp;
        NB->kiri = NULL;
        NB->kanan = NULL;

        if (awal == NULL) {
            awal = NB;
            akhir = NB;
        } else {
            akhir->kanan = NB;
            NB->kiri = akhir;
            akhir = NB;
        }
    }
    fclose(fp);
}

void tambahBuku(){
    printf("\n +================================================+\n");
    printf(" |                [+] TAMBAH BUKU                 |\n");
    printf(" +================================================+\n");
    int n;
    printf("  [?] Berapa banyak buku yang ingin ditambah? : ");
    scanf("%d", &n);
    getchar();

    for(int k = 0; k < n; k++){
        printf("\n  -- Data Buku ke-%d --\n", k+1);
        struct Buku *NB = (struct Buku *)malloc(sizeof(struct Buku));
        
        printf("  >> Kode Buku    : ");
        scanf("%s", NB->kode);
        getchar();

        printf("  >> Judul Buku   : ");
        fgets(NB->judul, sizeof(NB->judul), stdin);
        NB->judul[strcspn(NB->judul, "\n")] = 0;

        printf("  >> Penulis      : ");
        fgets(NB->penulis, sizeof(NB->penulis), stdin);
        NB->penulis[strcspn(NB->penulis, "\n")] = 0;

        printf("  >> Tahun Terbit : ");
        scanf("%d", &NB->tahun);

        NB->status = 0;
        NB->kiri = NULL;
        NB->kanan = NULL;

        if (awal == NULL) {
            awal = NB;
            akhir = NB;
        } else {
            akhir->kanan = NB;
            NB->kiri = akhir;
            akhir = NB;
        }
    }
    simpanFile();
    printf("\n [✓] Mantap! %d Data buku berhasil ditambahkan ke sistem!\n", n);
}

void tampilBuku(){
    tampilBukuFilter(-1);
}

void cariBuku(){
    char cari[50];
    printf("\n +================================================+\n");
    printf(" |                 [?] CARI BUKU                  |\n");
    printf(" +================================================+\n");
    printf("  >> Masukan judul buku yang dicari: ");
    getchar();
    fgets(cari, sizeof(cari), stdin);
    cari[strcspn(cari, "\n")] = 0;

    struct Buku *bantu = awal;
    int found = 0;
    
    while (bantu != NULL) {
        if(strstr(bantu->judul, cari) != NULL) {
            found = 1;
            break;
        }
        bantu = bantu->kanan;
    }

    if (found) {
        printf("\n  [✓] BUKU DITEMUKAN!\n");
        printHeader();
        printBook(bantu, 1);
        printLine();
    } else {
        printf("\n  [!] Yah, buku dengan judul \"%s\" tidak ditemukan.\n", cari);
    }
}

void printLine() {
    printf(" +------+------------+--------------------------------+--------------------------------+--------+------------+\n");
}

void printHeader(){
    printLine();
    printf(" | %-4s | %-10s | %-30s | %-30s | %-6s | %-10s |\n", "No", "Kode", "Judul Buku", "Penulis", "Tahun", "Status");
    printLine();
}

void printBook(struct Buku *buku, int nomor){
    char tempJudul[35] = {0};
    char tempPenulis[35] = {0};
    
    strncpy(tempJudul, buku->judul, 30); // Buat motong kalimat yang lebih dari 30 menjadi 30 agar tidak merusak tabel
    tempJudul[30] = '\0'; 
    strncpy(tempPenulis, buku->penulis, 30);
    tempPenulis[30] = '\0';

    for(int i = 0; i < 30 && tempJudul[i] != '\0'; i++) {
        if((unsigned char)tempJudul[i] < 32 || (unsigned char)tempJudul[i] > 126) {// Untuk mengecek apakah ada karakter aaneh yang tersembunyi supaya tidak glitch akibat file biner menggantikannya dengan spasi biasa
            tempJudul[i] = ' '; 
        }
    }
    for(int i = 0; i < 30 && tempPenulis[i] != '\0'; i++) {
        if((unsigned char)tempPenulis[i] < 32 || (unsigned char)tempPenulis[i] > 126) {
            tempPenulis[i] = ' ';
        }
    }

    printf(" | %-4d | %-10s | %-30s | %-30s | %-6d | %-10s |\n",
           nomor, buku->kode, tempJudul, tempPenulis,
           buku->tahun, buku->status == 0 ? "Tersedia" : "Dipinjam"); // Untuk status buku apakah dipinjam atau tidak
}

void tampilBukuFilter(int status){
    if (awal == NULL) {
        printf("\n [!] Ups, Database Perpustakaan saat ini masih kosong.\n");
        return;
    }

    if (status == -1) 
        printf("\n >>> DAFTAR SELURUH BUKU PERPUSTAKAAN <<<\n");
    else if (status == 0) 
        printf("\n >>> DAFTAR BUKU YANG SIAP DIPINJAM <<<\n");
    else 
        printf("\n >>> DAFTAR BUKU YANG SEDANG DIPINJAM <<<\n");

    printHeader();// tabel
    int no = 1, found = 0; // Penomeran dari 1
    struct Buku *bantu = awal; // mulailah ia berjalan dari satu buku ke buku lainnya di dalam Linked List
    
    while (bantu != NULL) {
        if (status == -1 || bantu->status == status) { // kode pengecekan:
            printBook(bantu, no);
            no++;
            found = 1;
        }
        bantu = bantu->kanan;
    }

    if (!found) {
        printf(" | %-105s |\n", "                                         (Tidak ada data buku pada kategori ini)");
    }
    printLine(); // lansgung diatahkan ke printLine atau tabel yang sudah disiapkan
}

void swapData(struct Buku *a, struct Buku *b) {
    char tempKode[10], tempJudul[50], tempPenulis[50];
    int tempTahun, tempStatus;

    strcpy(tempKode, a->kode); strcpy(a->kode, b->kode); strcpy(b->kode, tempKode);
    strcpy(tempJudul, a->judul); strcpy(a->judul, b->judul); strcpy(b->judul, tempJudul);
    strcpy(tempPenulis, a->penulis); strcpy(a->penulis, b->penulis); strcpy(b->penulis, tempPenulis);
    
    tempTahun = a->tahun; a->tahun = b->tahun; b->tahun = tempTahun;
    tempStatus = a->status; a->status = b->status; b->status = tempStatus;
}

void bubbleSortByTitle(){
    if (awal == NULL) return;
    int swapped;
    struct Buku *ptr1;
    struct Buku *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = awal;
        while (ptr1->kanan != lptr) {
            if (strcmp(ptr1->judul, ptr1->kanan->judul) > 0) {
                swapData(ptr1, ptr1->kanan);
                swapped = 1;
            }
            ptr1 = ptr1->kanan;
        }
        lptr = ptr1; 
    } while (swapped);
}

void selectionSortByYear(int descending){
    if (awal == NULL) return;
    struct Buku *i, *j, *idx;

    for (i = awal; i->kanan != NULL; i = i->kanan) {
        idx = i;
        for (j = i->kanan; j != NULL; j = j->kanan) {
            if (descending) {
                if (j->tahun > idx->tahun) idx = j;
            } else {
                if (j->tahun < idx->tahun) idx = j;
            }
        }
        if (idx != i) {
            swapData(i, idx);
        }
    }
}

void urutkanBuku(){
    int pilihan;
    printf("\n +================================================+\n");
    printf(" |              [~] MENU URUTKAN BUKU             |\n");
    printf(" +================================================+\n");
    printf("  [1] Berdasarkan Judul (A-Z)\n");
    printf("  [2] Berdasarkan Tahun (Terlama -> Terbaru)\n");
    printf("  [3] Berdasarkan Tahun (Terbaru -> Terlama)\n");
    printf(" --------------------------------------------------\n");
    printf("  [?] Pilih gaya urutan (1-3): ");
    scanf("%d", &pilihan);
    getchar();

    if (pilihan == 1) {
        bubbleSortByTitle();
        printf("\n  [✓] Sukses! Data berhasil diurutkan berdasarkan judul abjad (A-Z).\n");
    } else if (pilihan == 2) {
        selectionSortByYear(0);
        printf("\n  [✓] Sukses! Data berhasil diurutkan berdasarkan tahun terlama.\n");
    } else if (pilihan == 3) {
        selectionSortByYear(1);
        printf("\n  [✓] Sukses! Data berhasil diurutkan berdasarkan tahun terbaru.\n");
    } else {
        printf("\n  [!] Pilihan urutan tidak valid.\n");
        return;
    }
    simpanFile();
}

void hapusBuku(){
    char kode[10];
    printf("\n +================================================+\n");
    printf(" |                 [-] HAPUS BUKU                 |\n");
    printf(" +================================================+\n");
    printf("  >> Masukkan KODE BUKU yang ingin dihapus: ");
    scanf("%s", kode);

    struct Buku *bantu = awal;
    int found = 0;

    while (bantu != NULL) {
        if (strcmp(bantu->kode, kode) == 0) {
            found = 1;
            break;
        }
        bantu = bantu->kanan;
    }

    if (found) {
        if (bantu == awal && bantu == akhir) {
            awal = NULL;
            akhir = NULL;
        } else if (bantu == awal) {
            awal = awal->kanan;
            awal->kiri = NULL;
        } else if (bantu == akhir) {
            akhir = akhir->kiri;
            akhir->kanan = NULL;
        } else {
            bantu->kiri->kanan = bantu->kanan;
            bantu->kanan->kiri = bantu->kiri;
        }
        free(bantu); 
        simpanFile();
        printf("\n  [✓] Data buku dengan kode %s berhasil dihapus selamanya!\n", kode);
    } else {
        printf("\n  [!] Data tidak ditemukan, pastikan kode buku sudah benar!\n");
    }
}

void pinjamanBuku(){
    char kode[10];
    printf("\n +================================================+\n");
    printf(" |               [>] PINJAM BUKU                  |\n");
    printf(" +================================================+\n");
    printf("  >> Masukkan KODE BUKU yang ingin dipinjam: ");
    scanf("%s", kode);

    struct Buku *bantu = awal;
    int found = 0;
    while (bantu != NULL) {
        if (strcmp(bantu->kode, kode) == 0) {
            found = 1; break;
        }
        bantu = bantu->kanan;
    }

    if (found) {
        if (bantu->status == 0) {
            bantu->status = 1;
            simpanFile();
            printf("\n  [✓] BERHASIL! Buku \"%s\" kini berstatus dipinjam.\n", bantu->judul);
        } else {
            printf("\n  [!] MAAF! Buku \"%s\" saat ini sedang dipinjam orang lain.\n", bantu->judul);
        }
    } else {
        printf("\n  [!] Buku dengan kode tersebut tidak ditemukan!\n");
    }
}

void kembalikanbuku(){
    char kode[10];
    printf("\n +================================================+\n");
    printf(" |             [<] KEMBALIKAN BUKU                |\n");
    printf(" +================================================+\n");
    printf("  >> Masukkan KODE BUKU yang ingin dikembalikan: ");
    scanf("%s", kode);

    struct Buku *bantu = awal;
    int found = 0;
    while (bantu != NULL) {
        if (strcmp(bantu->kode, kode) == 0) {
            found = 1; break;
        }
        bantu = bantu->kanan;
    }

    if (found) {
        if (bantu->status == 1) {
            bantu->status = 0;
            simpanFile();
            printf("\n  [✓] TERIMA KASIH! Buku \"%s\" telah dikembalikan ke rak.\n", bantu->judul);
        } else {
            printf("\n  [!] Buku \"%s\" berstatus tersedia, tidak sedang dipinjam.\n", bantu->judul);
        }
    } else {
        printf("\n  [!] Buku dengan kode tersebut tidak ditemukan!\n");
    }
}

int main(){
    loadFile();
    int pilihan;
    do {
        printf("\n=================================================================\n");
        printf("||                   SISTEM PERPUSTAKAAN MINI                  ||\n");
        printf("=================================================================\n");
        printf("  [1] Tambah Buku Baru             [6] Urutkan Daftar Buku\n");
        printf("  [2] Tampilkan Semua Buku         [7] Hapus Buku dari Sistem\n");
        printf("  [3] Tampilkan Buku Tersedia      [8] Pinjam Buku\n");
        printf("  [4] Tampilkan Buku Dipinjam      [9] Kembalikan Buku\n");
        printf("  [5] Cari Judul Buku              [0] Keluar & Simpan\n");
        printf("-----------------------------------------------------------------\n");
        printf("  [?] Masukkan Pilihan Menu (1-10) : ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1: tambahBuku(); break;
            case 2: tampilBukuFilter(-1); break;
            case 3: tampilBukuFilter(0); break;
            case 4: tampilBukuFilter(1); break;
            case 5: cariBuku(); break;
            case 6: urutkanBuku(); break;
            case 7: hapusBuku(); break;
            case 8: pinjamanBuku(); break;
            case 9: kembalikanbuku(); break;
            case 0: 
                printf("\n  [✓] Data telah disimpan. Terima kasih telah menggunakan sistem ini!\n\n"); 
                break;
            default: 
                printf("\n  [!] Pilihan tidak valid! Silakan pilih nomor 1 sampai 10.\n");
        }
    } while (pilihan != 0);
    return 0;
}