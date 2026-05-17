#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
struct Buku {
    char kode[10];
    char judul[50];
    char penulis[50];
    int tahun;
    int status;
};

struct Buku data[MAX];
int jumlah = 0;

void tampilBukuFilter(int status);
void printLine();
void printHeader();
void printBook(struct Buku *buku, int nomor);

void simpanFile(){
    FILE *fp = fopen("data.dat", "wb");
    if (fp == NULL)
    {
        printf("Gagal membuka file!\n");
        return;
    }
    fwrite(& jumlah, sizeof(int), 1, fp);
    fwrite(data, sizeof(struct Buku), jumlah, fp);
    fclose(fp);
}

void loadFile(){
    FILE *fp = fopen("data.dat", "rb");
    if (fp != NULL)
    {
        fread(&jumlah, sizeof(int), 1, fp);
        fread(data, sizeof(struct Buku), jumlah, fp);
        fclose(fp);
    }
}

void tambahBuku(){
    printf("\n==== Tambah Buku ====\n");
    int n;
    printf("Berapa banyakk buku yang ditambah? ");
    scanf("%d", &n);
    getchar();

    for(int k = 0; k < n; k++){
    printf("Kode Buku    : ");
    scanf("%s", data[jumlah].kode);
    getchar();

    printf("Judul Buku   : ");
    fgets(data[jumlah].judul, sizeof(data[jumlah].judul), stdin);
    data[jumlah].judul[strcspn(data[jumlah].judul, "\n")] = 0;

    printf("Penulis      : ");
    fgets(data[jumlah].penulis, sizeof(data[jumlah].penulis), stdin);
    data[jumlah].penulis[strcspn(data[jumlah].penulis, "\n")] = 0;

    printf("Tahun Terbit :");
    scanf("%d", &data[jumlah].tahun);

    data[jumlah].status = 0;
    jumlah++;
    }
    simpanFile();
    printf("Data berhasil ditambahkan!\n");
}

void tampilBuku(){
    tampilBukuFilter(-1);
}

void cariBuku(){
    char cari[50];
    printf("\nMasukan judul buku: ");
    getchar();
    fgets(cari, sizeof(cari), stdin);
    cari[strcspn(cari, "\n")] = 0;

    int i = 0;
    for(i=0; i<jumlah;i++)
    {
        if(strstr(data[i].judul, cari) != NULL)
        {
            break;
        }
    }

    if (i < jumlah)
    {
        printf("\n=== Hasil Pencarian Buku ===\n");
        printHeader();
        printBook(&data[i], 1);
        printLine();
    }
    else
    {
        printf("\nBuku tidak ditemukan!\n");
    }
}

void printLine()
{
    printf("======================================================================\n");
}

void printHeader(){
    printLine();
    printf("%-4s %-8s %-20s %-18s %-6s %-10s\n", "No", "Kode", "Judul", "Penulis", "Tahun", "Status");
    printLine();
}

void printBook(struct Buku *buku, int nomor){
    printf("%-4d %-8s %-20.20s %-18.18s %-6d %-10s\n",
           nomor,
           buku->kode,
           buku->judul,
           buku->penulis,
           buku->tahun,
           buku->status == 0 ? "Tersedia" : "Dipinjam");
}

void tampilBukuFilter(int status){
    int found = 0;
    int no = 1;
    struct Buku *p = data;

    if (jumlah == 0)
    {
        printf("\nData kosong!\n");
        return;
    }

    if (status == -1)
        printf("\n=== Daftar Semua Buku ===\n");
    else if (status == 0)
        printf("\n=== Daftar Buku Tersedia ===\n");
    else
        printf("\n=== Daftar Buku Dipinjam ===\n");

    printHeader();
    for (int i = 0; i < jumlah; i++, p++)
    {
        if (status == -1 || p->status == status)
        {
            printBook(p, no);
            no++;
            found = 1;
        }
    }

    if (!found)
    {
        printf("Tidak ada buku pada kategori ini.\n");
    }
    printLine();
}

void bubbleSortByTitle(){
    for (int i = 0; i < jumlah - 1; i++)
    {
        for (int j = 0; j < jumlah - 1 - i; j++)
        {
            if (strcmp(data[j].judul, data[j + 1].judul) > 0)
            {
                struct Buku temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void selectionSortByYear(int descending){
    for (int i = 0; i < jumlah - 1; i++)
    {
        int idx = i;
        for (int j = i + 1; j < jumlah; j++)
        {
            if (descending)
            {
                if (data[j].tahun > data[idx].tahun)
                    idx = j;
            }
            else
            {
                if (data[j].tahun < data[idx].tahun)
                    idx = j;
            }
        }
        if (idx != i)
        {
            struct Buku temp = data[i];
            data[i] = data[idx];
            data[idx] = temp;
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

    if (pilihan == 1)
    {
        bubbleSortByTitle();
        printf("Data berhasil diurutkan berdasarkan judul.\n");
    }
    else if (pilihan == 2)
    {
        selectionSortByYear(0);
        printf("Data berhasil diurutkan berdasarkan tahun (terlama -> terbaru).\n");
    }
    else if (pilihan == 3)
    {
        selectionSortByYear(1);
        printf("Data berhasil diurutkan berdasarkan tahun (terbaru -> terlama).\n");
    }
    else
    {
        printf("Pilihan urutan tidak valid.\n");
        return;
    }

    simpanFile();
}

void hapusBuku(){
    char kode[10];
    printf("\nMasukkan kode buku: ");
    scanf("%s", kode);

    int i, found = 0;
    for (i = 0; i < jumlah; i++)
    {
        if (strcmp(data[i].kode, kode) == 0)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        for (int j = i; j < jumlah - 1; j++)
        {
            data[j] = data[j + 1];
        }
        jumlah--;
        simpanFile();
        printf("Data berhasil dihapus!\n");
    }
    else
    {
        printf("Data tidak ditemukan!\n");
    }
}
void pinjamanBuku(){
    char kode[10];
    printf("\nMasukkan kode buku yang ingin di pinjam:");
    scanf("%s", kode);

    int i, found = 0;
    for (i = 0; i < jumlah; i++)
    {
        if (strcmp(data[i].kode, kode) == 0)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        if (data[i].status == 0){
            data[i].status = 1;
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

    int i, found = 0;
    for (i = 0; i < jumlah; i++)
    {
        if (strcmp(data[i].kode, kode) == 0)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        if (data[i].status == 1)
        {
            data[i].status = 0;
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
    do
    {
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

        switch (pilihan)
        {
        case 1:
            tambahBuku();
            break;
        case 2:
            tampilBukuFilter(-1);
            break;
        case 3:
            tampilBukuFilter(0);
            break;
        case 4:
            tampilBukuFilter(1);
            break;
        case 5:
            cariBuku();
            break;
        case 6:
            urutkanBuku();
            break;
        case 7:
            hapusBuku();
            break;
        case 8:
            pinjamanBuku();
            break;
        case 9:
            kembalikanbuku();
            break;
        case 10:
            printf("Terima kasih!\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 10);
    return 0;
}