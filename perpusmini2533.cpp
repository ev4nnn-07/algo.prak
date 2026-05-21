#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =================================================================
// [MODUL I & MODUL VI]: POINTER & LINKED LIST GANDA
// Struct Buku dimodifikasi menjadi Node Doubly Linked List
// =================================================================
struct Buku {
    char kode[10];
    char judul[50];
    char penulis[50];
    int tahun;
    int status; // 0 = Tersedia, 1 = Dipinjam
    
    struct Buku *kiri;  // Pointer ke node sebelumnya (Prev)
    struct Buku *kanan; // Pointer ke node setelahnya (Next)
};

// Deklarasi Pointer Global untuk Linked List Ganda
struct Buku *awal = NULL;
struct Buku *akhir = NULL;

void tampilBukuFilter(int status);
void printLine();
void printHeader();
void printBook(struct Buku *buku, int nomor);

// =================================================================
// [MODUL IV]: OPERASI FILE PADA LINKED LIST GANDA
// =================================================================
void simpanFile(){
    FILE *fp = fopen("data.dat", "wb");
    if (fp == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
    
    // Menelusuri linked list dari awal sampai akhir untuk direkam
    struct Buku *bantu = awal;
    while (bantu != NULL) {
        fwrite(bantu, sizeof(struct Buku), 1, fp);
        bantu = bantu->kanan;
    }
    fclose(fp);
}

void loadFile(){
    FILE *fp = fopen("data.dat", "rb");
    if (fp == NULL) return; // Jika file tidak ada, lewati

    struct Buku temp;
    // Membaca per blok Node dari file biner
    while (fread(&temp, sizeof(struct Buku), 1, fp) == 1) {
        // [MODUL I]: Alokasi memori dinamis menggunakan Pointer
        struct Buku *NB = (struct Buku *)malloc(sizeof(struct Buku));
        *NB = temp;
        NB->kiri = NULL;
        NB->kanan = NULL;

        // Proses Sisip Belakang (Insert Last) pada Linked List Ganda
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
    printf("\n==== Tambah Buku ====\n");
    int n;
    printf("Berapa banyak buku yang ditambah? ");
    scanf("%d", &n);
    getchar();

    for(int k = 0; k < n; k++){
        struct Buku *NB = (struct Buku *)malloc(sizeof(struct Buku));
        
        printf("Kode Buku    : ");
        scanf("%s", NB->kode);
        getchar();

        printf("Judul Buku   : ");
        fgets(NB->judul, sizeof(NB->judul), stdin);
        NB->judul[strcspn(NB->judul, "\n")] = 0;

        printf("Penulis      : ");
        fgets(NB->penulis, sizeof(NB->penulis), stdin);
        NB->penulis[strcspn(NB->penulis, "\n")] = 0;

        printf("Tahun Terbit :");
        scanf("%d", &NB->tahun);

        NB->status = 0;
        NB->kiri = NULL;
        NB->kanan = NULL;

        // [MODUL VI]: Logika penyisipan simpul baru di ujung Kanan (Insert Last)
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
    printf("Data berhasil ditambahkan!\n");
}

void tampilBuku(){
    tampilBukuFilter(-1);
}

// =================================================================
// [MODUL II]: PENCARIAN DATA (Sequential Search pada Linked List)
// =================================================================
void cariBuku(){
    char cari[50];
    printf("\nMasukan judul buku: ");
    getchar();
    fgets(cari, sizeof(cari), stdin);
    cari[strcspn(cari, "\n")] = 0;

    struct Buku *bantu = awal;
    int found = 0;
    
    // Penelusuran Linked List
    while (bantu != NULL) {
        if(strstr(bantu->judul, cari) != NULL) {
            found = 1;
            break;
        }
        bantu = bantu->kanan;
    }

    if (found) {
        printf("\n=== Hasil Pencarian Buku ===\n");
        printHeader();
        printBook(bantu, 1);
        printLine();
    } else {
        printf("\nBuku tidak ditemukan!\n");
    }
}

void printLine() {
    printf("======================================================================\n");
}

void printHeader(){
    printLine();
    printf("%-4s %-8s %-20s %-18s %-6s %-10s\n", "No", "Kode", "Judul", "Penulis", "Tahun", "Status");
    printLine();
}

void printBook(struct Buku *buku, int nomor){
    printf("%-4d %-8s %-20.20s %-18.18s %-6d %-10s\n",
           nomor, buku->kode, buku->judul, buku->penulis,
           buku->tahun, buku->status == 0 ? "Tersedia" : "Dipinjam");
}

void tampilBukuFilter(int status){
    if (awal == NULL) {
        printf("\nData kosong!\n");
        return;
    }

    if (status == -1) printf("\n=== Daftar Semua Buku ===\n");
    else if (status == 0) printf("\n=== Daftar Buku Tersedia ===\n");
    else printf("\n=== Daftar Buku Dipinjam ===\n");

    printHeader();
    int no = 1, found = 0;
    struct Buku *bantu = awal;
    
    while (bantu != NULL) {
        if (status == -1 || bantu->status == status) {
            printBook(bantu, no);
            no++;
            found = 1;
        }
        bantu = bantu->kanan;
    }

    if (!found) printf("Tidak ada buku pada kategori ini.\n");
    printLine();
}

// Fungsi Bantuan untuk menukar isi Data antar Node (Tanpa memutus pointer)
void swapData(struct Buku *a, struct Buku *b) {
    char tempKode[10], tempJudul[50], tempPenulis[50];
    int tempTahun, tempStatus;

    strcpy(tempKode, a->kode); strcpy(a->kode, b->kode); strcpy(b->kode, tempKode);
    strcpy(tempJudul, a->judul); strcpy(a->judul, b->judul); strcpy(b->judul, tempJudul);
    strcpy(tempPenulis, a->penulis); strcpy(a->penulis, b->penulis); strcpy(b->penulis, tempPenulis);
    
    tempTahun = a->tahun; a->tahun = b->tahun; b->tahun = tempTahun;
    tempStatus = a->status; a->status = b->status; b->status = tempStatus;
}

// =================================================================
// [MODUL III]: PENGURUTAN DATA (Bubble Sort pada Linked List)
// =================================================================
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
        lptr = ptr1; // Optimasi Bubble Sort
    } while (swapped);
}

// =================================================================
// [MODUL III]: PENGURUTAN DATA (Selection Sort pada Linked List)
// =================================================================
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
    printf("\n=== Menu Urut Buku ===\n");
    printf("1. Urutkan Judul (A-Z)\n");
    printf("2. Urutkan Tahun (Terlama -> Terbaru)\n");
    printf("3. Urutkan Tahun (Terbaru -> Terlama)\n");
    printf("Pilih jenis urutan: ");
    scanf("%d", &pilihan);
    getchar();

    if (pilihan == 1) {
        bubbleSortByTitle();
        printf("Data berhasil diurutkan berdasarkan judul.\n");
    } else if (pilihan == 2) {
        selectionSortByYear(0);
        printf("Data berhasil diurutkan berdasarkan tahun (terlama -> terbaru).\n");
    } else if (pilihan == 3) {
        selectionSortByYear(1);
        printf("Data berhasil diurutkan berdasarkan tahun (terbaru -> terlama).\n");
    } else {
        printf("Pilihan urutan tidak valid.\n");
        return;
    }
    simpanFile();
}

void hapusBuku(){
    char kode[10];
    printf("\nMasukkan kode buku: ");
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
        // [MODUL VI]: Logika Penghapusan Node pada Linked List Ganda
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
        free(bantu); // Dealokasi memori Pointer
        simpanFile();
        printf("Data berhasil dihapus!\n");
    } else {
        printf("Data tidak ditemukan!\n");
    }
}

void pinjamanBuku(){
    char kode[10];
    printf("\nMasukkan kode buku yang ingin di pinjam:");
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
            printf("Buku berhasil dipinjam!!\n");
        } else {
            printf("Buku sedang dipinjam!!\n");
        }
    } else {
        printf("Buku tidak ditemukan!\n");
    }
}

void kembalikanbuku(){
    char kode[10];
    printf("\nMasukkan kode buku yang ingin dikembalikan:");
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
            printf("Buku berhasil dikembalikan!\n");
        } else {
            printf("Buku tidak sedang dipinjam!\n");
        }
    } else {
        printf("Buku tidak ditemukan!\n");
    }
}

int main(){
    loadFile();
    int pilihan;
    do {
        printf("\n==============================================================\n");
        printf("                 SISTEM PERPUSTAKAAN MINI                  \n");
        printf("==============================================================\n");
        printf("1. Tambah Buku\n");
        printf("2. Tampil Semua Buku\n");
        printf("3. Tampil Buku Tersedia\n");
        printf("4. Tampil Buku Dipinjam\n");
        printf("5. Cari Buku\n");
        printf("6. Urutkan Buku\n");
        printf("7. Hapus Buku\n");
        printf("8. Pinjam Buku\n");
        printf("9. Kembalikan Buku\n");
        printf("10. Keluar\n");
        printf("==============================================================\n");
        printf("Pilih menu: ");
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
            case 10: printf("Terima kasih!\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 10);
    return 0;
}