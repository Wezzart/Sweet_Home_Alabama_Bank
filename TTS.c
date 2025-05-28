#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#define MAX_USER      100
#define MAX_NASABAH   100
#define MAX_LENGTH    50

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
} User;

typedef struct {
    char nama[MAX_LENGTH];
    float saldo;
} Nasabah;

User users[MAX_USER];
int   userCount    = 0;

Nasabah daftarNasabah[MAX_NASABAH];
int     jumlahNasabah = 0;



void inputPassword(char password[]) {
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == '\r') {
            password[i] = '\0';
            printf("\n");
            break;
        }
        else if (ch == '\b' && i > 0) {
            i--;
            printf("\b \b");
        }
        else if (i < MAX_LENGTH - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
}


bool regis() {
    char username[MAX_LENGTH], password[MAX_LENGTH];

    if (userCount >= MAX_USER) {
        printf("Kapasitas user penuh!\n");
        return false;
    }

    printf("Masukkan username baru: ");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username sudah terdaftar!\n");
            return false;
        }
    }

    printf("Masukkan password baru: ");
    inputPassword(password);

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;
    return true;
}

bool login() {
    char username[MAX_LENGTH], password[MAX_LENGTH];

    printf("Masukkan username: ");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Masukkan password: ");
    inputPassword(password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0
         && strcmp(users[i].password, password) == 0) {
            return true;
        }
    }
    return false;
}


void tambahNasabah() {
    if (jumlahNasabah >= MAX_NASABAH) {
        printf("Kapasitas nasabah penuh!\n");
        return;
    }
    getchar();
    printf("Masukkan nama nasabah: ");
    fgets(daftarNasabah[jumlahNasabah].nama, MAX_LENGTH, stdin);
    daftarNasabah[jumlahNasabah].nama[
        strcspn(daftarNasabah[jumlahNasabah].nama, "\n")] = '\0';
    daftarNasabah[jumlahNasabah].saldo = 0.0f;
    jumlahNasabah++;
    printf("Nasabah berhasil ditambahkan!\n");
}

void kalkulasiUang() {
    if (jumlahNasabah == 0) {
        printf("Belum ada nasabah terdaftar.\n");
        return;
    }
    int idx, pilihan;
    float jumlah;
    printf("Daftar Nasabah:\n");
    for (int i = 0; i < jumlahNasabah; i++) {
        printf(" %d. %s (Saldo: Rp %.2f)\n",
               i+1, daftarNasabah[i].nama, daftarNasabah[i].saldo);
    }
    printf("Pilih nomor nasabah: ");
    scanf("%d", &idx);
    if (idx < 1 || idx > jumlahNasabah) {
        printf("Nomor tidak valid!\n");
        return;
    }
    idx--; 

    printf("1. Setor Uang\n2. Tarik Uang\nPilih: ");
    scanf("%d", &pilihan);
    printf("Jumlah: Rp ");
    scanf("%f", &jumlah);

    if (pilihan == 1) {
        daftarNasabah[idx].saldo += jumlah;
        printf("Setor berhasil. Saldo: Rp %.2f\n", daftarNasabah[idx].saldo);
    }
    else if (pilihan == 2) {
        if (jumlah > daftarNasabah[idx].saldo) {
            printf("Saldo tidak cukup!\n");
        } else {
            daftarNasabah[idx].saldo -= jumlah;
            printf("Tarik berhasil. Saldo: Rp %.2f\n", daftarNasabah[idx].saldo);
        }
    } else {
        printf("Pilihan transaksi tidak valid!\n");
    }
}


int main() {
    int menu;
    bool sesiAktif = false;

    
    do {
        system("cls");
        printf("=== APLIKASI BANK SEDERHANA ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\nPilihan: ");
        if (scanf("%d", &menu) != 1) {
            
            while (getchar() != '\n');
            menu = 0;
        }
        getchar(); 
        switch (menu) {
            case 1:
                if (regis()) printf("Registrasi berhasil!\n");
                else          printf("Registrasi gagal.\n");
                system("pause");
                break;
            case 2:
                if (login()) {
                    printf("Login berhasil!\n");
                    sesiAktif = true;
                } else {
                    printf("Login gagal!\n");
                }
                system("pause");
                break;
            case 3:
                printf("Keluar program.\n");
                return 0;
            default:
                printf("Pilihan tidak valid.\n");
                system("pause");
        }
    } while (!sesiAktif);

    
    do {
        system("cls");
        printf("=== MENU NASABAH & TRANSAKSI ===\n");
        printf("1. Tambah Nasabah\n");
        printf("2. Transaksi (Setor/Tarik)\n");
        printf("3. Logout\nPilihan: ");
        scanf("%d", &menu);
        switch (menu) {
            case 1:
                tambahNasabah();
                break;
            case 2:
                kalkulasiUang();
                break;
            case 3:
                printf("Anda telah logout.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
        system("pause");
    } while (menu != 3);

    return 0;
}
