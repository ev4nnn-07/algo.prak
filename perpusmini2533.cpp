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
    printf("Berapa banyakk buku yang ditambah?");
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
    printf("\n=== Data Buku ===\n");
    if (jumlah == 0)
    {
        printf("Data kosong!\n");
        return;
    }
    for (int i = 0; i < jumlah; i++)
    {
        printf("\nData ke-%d\n", i + 1);
        printf("Kode     : %s\n", data[i].kode);
        printf("Judul    : %s\n", data[i].judul);
        printf("Penulis  : %s\n", data[i].penulis);
        printf("Tahun    : %d\n", data[i].tahun);
        printf("Status   : %s\n", data[i].status == 0 ? "Tersedia" : "Dipinjam");
    }
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
        if(strcmp(data[i]. judul, cari)==0)
    {
        break;
    }
}

    if (i < jumlah)
    {
        printf("\nBuku ditemukan!\n");
        printf("Kode     : %s\n", data[i].kode);
        printf("Judul    : %s\n", data[i].judul);
        printf("Penulis  : %s\n", data[i].penulis);
        printf("Tahun    : %d\n", data[i].tahun);
        printf("Status   : %s\n", data[i].status == 0 ? "Tersedia" : "Dipinjam");
    }
    else
    {
        printf("Buku tidak ditemukan!\n");
    }
}

void shellsort()
{
    int gap, i, j;
    struct Buku temp;
    for (gap = jumlah / 2; gap > 0; gap /= 2){
        for (i = gap; i < jumlah; i++)
        {
            temp = data[i];
            for (j = i; j >= gap && strcmp(data[j - gap].judul, temp.judul) > 0; j -= gap){
                data[j] = data[j - gap];
            }
            data[j] = temp;
        }
    }
    simpanFile();
    printf("Data berhasil diurutkan!\n");
}

void hapusBuku()
{
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

// meminjam buku
void pinjamanBuku()
{
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

// pengembalian buku

void kembalikanbuku()
{
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

// menu utamanya
int main()
{
    loadFile();
    int pilihan;

    do
    {
        printf("\n=== SISTEM PERPUSTAKAKAN MINI ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Tampil Buku\n");
        printf("3. Cari buku\n");
        printf("4. Urutkan Buku\n");
        printf("5. Hapus Buku\n");
        printf("6. Pinjam Buku\n");
        printf("7. Kembalikan Buku\n");
        printf("8. Keluar\n");
        printf("Pilih menu:   ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan)
        {
        case 1:
            tambahBuku();
            break;
        case 2:
            tampilBuku();
            break;
        case 3:
            cariBuku();
            break;
        case 4:
            shellsort();
            break;
        case 5:
            hapusBuku();
            break;
        case 6:
            pinjamanBuku();
            break;
        case 7:
            kembalikanbuku();
            break;
        case 8:
            printf("Terima kasih!\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 8);

    return 0;
}