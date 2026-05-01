#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
struct Buku
{
    char kode[10];
    char judul[50];
    char penulis[50];
    int tahun;
    int status;
};

struct Buku data[MAX] int jumlah = 0;

void simpanFile()
{
    FILE *fp = fopen("data.dat", "wb");
    if (fp == NULL)
    {
        printf("Gagal membuka file!\n");
        return;
    }
    fwrite(% jumalah, sizeof(int), 1, fp);
    fwrite(data, sizeof(struct Buku), jumlah, fp);
    fclose(fp);
}

vodi loadFile()
{
    FILE *fp = fopen("data.dat", "rb");
    if (fp != NULL)
    {
        fread(&jumalah, sizeof(int), 1, fp);
        fread(data, sizeof(struct Buku), jumlah, fp);
        fclose(fp);
    }
}

void tambahBuku()
{
    printf("\n==== Tambah Buku ====\n");
    printf("Kode Buku    : ");
    scanf("%s", data[jumlah].kode);
    getchar();

    printf("Judul Buku   : ");
    fget(data[jumlah].judul, sizeof(data[jumlah].judul), stdin);
    data[jumlah].judul[strcpn(data[jumlah].judul, "\n")] = 0;

    printf("Penulis      : ");
    fget(data[jumlah].penulis, sizeof(data[jumlah].penulis), stdin);
    data[jumlah].penulis[strcpn(data[jumlah].penulis, "\n")] = 0;

    printf("Tahun Terbit :");
    scanf("%d", &data[jumlah].tahun);

    data[jumlah].status = 0;
    jumlah++;
    simpanFile();
    printf("Data berhasil ditambahkan!\n");
}

void tampilBuku()
{
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
        printf("Tahun    : %s\n", data[i].tahun);
        printf("Status   : %s\n", data[i].status == 0 ? "Tersedia" : "Dipinjam");
    }
}

void cariBuku()
{
    char cari[50];
    printf("\nMasukan judul buku: ");
    getchar();
    fget(cari, sizeof(cari), stdin);
    cari[strcspn(cari, "\n")] = 0;

    strcpy(data[jumlah].judul, cari);
    int i = 0;
    while (strcmp(data[i].judul, cari) != 0)
    {
        i++;
    }

    if (i < jumlah)
    {
        printf("\nBuku ditemukan!\n");
        printf("Kode     : %s\n", data[i].kode);
        printf("Judul    : %s\n", data[i].judul);
        printf("Penulis  : %s\n", data[i].penulis);
        printf("Tahun    : %s\n", data[i].tahun);
        printf("Status   : %s\n", data[i].status == 0 ? "Tersedia" : "Dipinjam");
    }
    else
    {
        printf("buku tidak ditemukan!\n");
    }
}

void shellsort()
{
    int gap, i, j;
    struct Buku temp;
    for (gap = jumlah / 2; gap > 0; gap /= 2)
    {
        for (i = gap; i < jumlah; i++)
        {
            temp = data[i];
            for (j = i; j >= gap && strcmp(data[j - gap].judul, temp.judul) > 0; j -= gap)
            {
                data[j] = data[j - gap];
            }
            data[j] = temp;
        }
    }
    simpanFile();
    printf("data berhasil diurutkan!\n");
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
void pinjamanBuku()
{
    char kode[10];
    printf("\nmasukkan kode buku:");
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
        if (data[i].status == 0)
        {
            data[i].status = 1;
            simpanFile();
            printf("buku berhasil dipinjam!!\n");
        }
    }
    else
    {
        printf("buku tidak ditemukan1\n")
    }

    void kembalikanbuku()
    {
        char kode[10];
        printf("\nmasukkan kode buku yang ingin dikembalikan:");
    }
}