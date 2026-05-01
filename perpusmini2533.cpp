#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
struct Buku{
    char kode[10];
    char judul[50];
    char penulis[50];
    int tahun;
    int status;
};

struct Buku data[MAX]
int jumlah = 0;

void simpanFile(){
    FILE *fp = fopen("data.dat", "wb");
    if(fp == NULL){
        printf("Gagal membuka file!\n");
        return;
    }
    fwrite(%jumalah, sizeof(int), 1, fp);
    fwrite(data, sizeof(struct Buku), jumlah, fp);
    fclose(fp);
}

vodi loadFile(){
    FILE *fp = fopen("data.dat", "rb");
    if(fp ! = NULL){
        fread(&jumalah, sizeof(int), 1, fp);
        fread(data,sizeof(struct Buku), jumlah, fp);
        fclose(fp);

    }
}

void tambahBuku(){
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

void tampilBuku(){
    printf("\n=== Data Buku ===\n");
    if(jumlah == 0){
        printf("Data kosong!\n");
        return;
    }
    for(int i = 0; i <jumlah; i++){
        printf("\nData ke-%d\n", i+1);
        printf("Kode     : %s\n", data[i].kode);
        printf("Judul    : %s\n", data[i].judul);
        printf("Penulis  : %s\n", data[i].penulis);
        printf("Tahun    : %s\n", data[i].tahun);
        printf("Status   : %s\n", data[i].status == 0 ? "Tersedia" : "Dipinjam");
    }
}