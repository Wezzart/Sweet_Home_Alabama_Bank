#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#define MAX_USER 100
#define MAX_LENGTH 50
#define MAKS_NASABAH 100


struct user {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
};
typedef struct user usr;


typedef struct {
    char nama[50];
    float saldo;
} Nasabah;

Nasabah daftarNasabah[MAKS_NASABAH];
int jumlahNasabah = 0;


void inputPassword(char password[]) {
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == '\r') {
            password[i] = 0;
            printf("\n");
            break;
        } else if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < MAX_LENGTH - 1) {
            password[i] = ch;
            i++;
            printf("*");
        }
    }
}


bool regis(usr users[], int *jumlahUser) {
    if (*jumlahUser >= MAX_USER) return 0;

    char username[MAX_LENGTH], password[MAX_LENGTH];
    printf("Masukkan username baru: ");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    for (int i = 0; i < *jumlahUser; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username sudah ada!\n");
            return 0;
        }
    }

    printf("Masukkan password baru: ");
    inputPassword(password);
    password[strcspn(password, "\n")] = '\0';

    strcpy(users[*jumlahUser].username, username);
    strcpy(users[*jumlahUser].password, password);
    (*jumlahUser)++;
    return 1;
}

bool login(usr users[], int *jumlahUser) {
    char username[MAX_LENGTH], password[MAX_LENGTH];
    printf("Masukkan username: ");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Masukkan password: ");
    inputPassword(password);

    for (int i = 0; i < *jumlahUser; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}


void tambahNasabah() {
    if (jumlahNasabah >= MAKS_NASABAH) {
        printf("Kapasitas penuh!\n");
        return;
    }

    printf("Masukkan nama nasabah: ");
    getchar();
    fgets(daftarNasabah[jumlahNasabah].nama, sizeof(daftarNasabah[jumlahNasabah].nama), stdin);
    daftarNasabah[jumlahNasabah].nama[strcspn(daftarNasabah[jumlahNasabah].nama, "\n")] = '\0';

    daftarNasabah[jumlahNasabah].saldo = 0.0;
    jumlahNasabah++;

    printf("Nasabah berhasil ditambahkan!\n");
}

void kalkulasiUang() {
    if (jumlahNasabah == 0) {
        printf("Belum ada nasabah terdaftar.\n");
        return;
    }

    int index;
    printf("Pilih nasabah berdasarkan nomor:\n");
    for (int i = 0; i < jumlahNasabah; i++) {
        printf("%d. %s (Saldo: Rp %.2f)\n", i + 1, daftarNasabah[i].nama, daftarNasabah[i].saldo);
    }

    printf("Masukkan nomor nasabah: ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= jumlahNasabah) {
        printf("Nomor tidak valid!\n");
        return;
    }

    int pilih;
    float jumlah;

    system("cls");
    printf("_____________________________\n");
        printf("|_________Transaksi_________|\n");
        printf("|                           |\n");
        printf("|1. Setor Uang              |\n");
        printf("|2. Tarik Uang              |\n");
        printf("|___________________________|\n");
    printf("Pilih Transaksi: ");
    scanf("%d", &pilih);

    switch (pilih) {
        case 1:
            system("cls");
            printf("(       Setor Uang      )\n");
            printf(" Jumlah setor: Rp ");
            scanf("%f", &jumlah);
            daftarNasabah[index].saldo += jumlah;
            printf("Setoran berhasil. Saldo sekarang: Rp %.2f\n", daftarNasabah[index].saldo);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            printf("(       Tarik Uang      )\n");
            printf(" Jumlah tarik: Rp ");
            scanf("%f", &jumlah);
            if (jumlah > daftarNasabah[index].saldo) {
                printf("Saldo tidak cukup!\n");
            } else {
                daftarNasabah[index].saldo -= jumlah;
                printf("Penarikan berhasil. Saldo sekarang: Rp %.2f\n", daftarNasabah[index].saldo);
            }
            system("pause");
            system("cls");
            break;
        default:
            printf("Pilihan tidak valid.\n");
    }
}


void menuNasabah() {
    int pilihan;
    do {
        printf("_____________________________\n");
        printf("|__________Nasabah__________|\n");
        printf("|1. Tambah Nama Nasabah     |\n");
        printf("|2. Kalkulasi               |\n");
        printf("|3. Logout                  |\n");
        printf("|___________________________|\n");
        printf("Masukkan PIlihan Anda : ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                system("cls");
                tambahNasabah();
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                kalkulasiUang();
                system("cls");
                break;
            case 3:
            system("cls");
            printf("|__________________________________________________|\n");
            printf("|Terimakasih Sudah Melakukan Transaksi Bersama Kami|\n");
            printf("|__________________________________________________|\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 3);
}


int menulogin() {
    usr users[MAX_USER];
    int jumlahUser = 0;
    int milih;
    bool ulang = true;

    while (ulang) {
        system("cls");
        printf("__________________________\n");
        printf("|__________Menu__________|\n");
        printf("|1. Register             |\n");
        printf("|2. Login                |\n");
        printf("|3. Exit                 |\n");
        printf("|________________________|\n");
        printf("Masukkan PIlihan Anda : ");
        if (scanf("%d", &milih) == 0) {
            printf("Input salah, silahkan input 1-3\n");
            milih = 0;
            system("pause");
        }
        while (getchar() != '\n');

        switch (milih) {
            case 1:
            system("cls");
                if (regis(users, &jumlahUser)) {
                    printf("Registrasi User Baru Berhasil\n");
                } else {
                    printf("Registrasi gagal, username sudah dipakai.\n");
                }
                system("pause");
                break;
            case 2:
            system("cls");
                if (login(users, &jumlahUser)) {
                    printf("Login berhasil\n");
                    system("pause");
                    system("cls");
                    ulang = false;
                    menuNasabah();
                } else {
                    printf("Login gagal, username atau password salah.\n");
                    system("pause");
                    system("cls");
                }
                break;
            case 3:
                printf("Keluar dari program\n");
                ulang = false;
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }

    return 0;
}

int main() {
    menulogin();
    return 0;
}