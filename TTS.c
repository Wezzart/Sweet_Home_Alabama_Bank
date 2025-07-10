#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#define MAX_USER 100
#define MAX_LENGTH 50
#define MAKS_NASABAH 100
#define FILE_NAME "userlogin.txt"

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
} usr;

typedef struct {
    char namaDeveloper[MAX_LENGTH];
    int nim;
} dev;

typedef struct {
    char nama[50];
    float saldo;
} Nasabah;

Nasabah daftarNasabah[MAKS_NASABAH];
int jumlahNasabah = 0;

void saveUserToFile(usr newUser) {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file untuk menyimpan data!\n");
        return;
    }
    fprintf(file, "%s;%s\n", newUser.username, newUser.password);
    fclose(file);
}

void LoadUserFromFile(usr users[], int *jumlahUser){
    FILE *file = fopen(FILE_NAME,"r");
    if(file == NULL){
        printf("Tidak dapat membuka file untuk mengambil data \n");
        system("pause");
        return;
    }
    char line[MAX_LENGTH * 2 + 2];
    *jumlahUser=0;
    while (*jumlahUser < MAX_USER && fgets(line, sizeof(line), file) != NULL){
        line[strcspn(line,"\n")] = 0;

        char *username_load = strtok(line, ";");
        char *password_load = strtok(NULL, ";");

        if(username_load != NULL && password_load != NULL){
            strcpy(users[*jumlahUser].username, username_load);
            strcpy(users[*jumlahUser].password, password_load);
            (*jumlahUser)++;
        }
    }
    fclose(file);
}

void namaDev(){
    dev inputData[] = {
        {"Made Khanaya Dew Astawa", 672024085},
        {"Theodorus Satria Dwipamudya", 672024086},
        {"Driadiska Purba Hapsara", 672024088},
        {"Priwiditya Lingga Mahendra", 672024101},
        {"Mikhael Pasco Evanmada", 672024163}
    };

    for(int i = 0; i < 5; i++) {
        printf ("Developer %d \n Nama: %s \n NIM: %d \n", i+1, inputData[i].namaDeveloper, inputData[i].nim);
    }
}

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
    printf("Masukkan username baru : ");
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
    saveUserToFile(users[*jumlahUser]);
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
    fgets(daftarNasabah[jumlahNasabah].nama, sizeof(daftarNasabah[jumlahNasabah].nama), stdin);
    daftarNasabah[jumlahNasabah].nama[strcspn(daftarNasabah[jumlahNasabah].nama, "\n")] = '\0';

    daftarNasabah[jumlahNasabah].saldo = 0.0;
    jumlahNasabah++;

    printf("Nasabah berhasil ditambahkan!\n");
}

void updateNasabah() {
    if (jumlahNasabah == 0) {
        printf("Belum ada nasabah untuk diupdate.\n");
        return;
    }

    printf("Pilih nasabah yang ingin diupdate:\n");
    for (int i = 0; i < jumlahNasabah; i++) {
        printf("%d. %s\n", i + 1, daftarNasabah[i].nama);
    }

    int index;
    printf("Masukkan nomor nasabah: ");
    scanf("%d", &index);
    getchar();
    index--;

    if (index < 0 || index >= jumlahNasabah) {
        printf("Nomor tidak valid!\n");
        return;
    }

    printf("Masukkan nama baru: ");
    fgets(daftarNasabah[index].nama, sizeof(daftarNasabah[index].nama), stdin);
    daftarNasabah[index].nama[strcspn(daftarNasabah[index].nama, "\n")] = '\0';

    printf("Nama nasabah berhasil diupdate.\n");
}

void hapusNasabah() {
    if (jumlahNasabah == 0) {
        printf("Belum ada nasabah untuk dihapus.\n");
        return;
    }

    printf("Pilih nasabah yang ingin dihapus:\n");
    for (int i = 0; i < jumlahNasabah; i++) {
        printf("%d. %s\n", i + 1, daftarNasabah[i].nama);
    }

    int index;
    printf("Masukkan nomor nasabah: ");
    scanf("%d", &index);
    getchar();
    index--;

    if (index < 0 || index >= jumlahNasabah) {
        printf("Nomor tidak valid!\n");
        return;
    }

    for (int i = index; i < jumlahNasabah - 1; i++) {
        daftarNasabah[i] = daftarNasabah[i + 1];
    }
    jumlahNasabah--;

    printf("Nasabah berhasil dihapus.\n");
}

void DataNasabah() {
    if (jumlahNasabah <= 0) {
        printf("\nBelum ada data Nasabah.\n");
        system("pause");
        return;
    }

    printf("\nData Nasabah:\n");
    printf("------------------------------\n");
    for (int i = 0; i < jumlahNasabah; i++) {
        printf("Nasabah %d\n", i + 1);
        printf("Nama: %s\n", daftarNasabah[i].nama);
        printf("------------------------------\n");
    }
}

void search() {
    if (jumlahNasabah == 0) {
        printf("Belum ada nasabah untuk dicari.\n");
        return;
    }

    char cariNama[MAX_LENGTH];
    printf("Masukkan nama nasabah yang ingin dicari: ");
    fgets(cariNama, MAX_LENGTH, stdin);
    cariNama[strcspn(cariNama, "\n")] = '\0';

    bool ditemukan = false;
    printf("\nHasil pencarian untuk '%s':\n", cariNama);
    printf("------------------------------\n");
    for (int i = 0; i < jumlahNasabah; i++) {

        if (strstr(daftarNasabah[i].nama, cariNama) != NULL) {
            printf("Nasabah %d\n", i + 1);
            printf("Nama: %s\n", daftarNasabah[i].nama);
            printf("Saldo: Rp %.2f\n", daftarNasabah[i].saldo);
            printf("------------------------------\n");
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        printf("Nasabah dengan nama '%s' tidak ditemukan.\n", cariNama);
    }
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
    printf("|1. Setor Uang              |\n");
    printf("|2. Tarik Uang              |\n");
    printf("|___________________________|\n");
    printf("Pilih Transaksi: ");
    scanf("%d", &pilih);
    while (getchar() != '\n');

    switch (pilih) {
        case 1:
            printf("Jumlah setor: Rp ");
            scanf("%f", &jumlah);
            daftarNasabah[index].saldo += jumlah;
            printf("Setoran berhasil. Saldo sekarang: Rp %.2f\n", daftarNasabah[index].saldo);
            break;
        case 2:
            printf("Jumlah tarik: Rp ");
            scanf("%f", &jumlah);
            if (jumlah > daftarNasabah[index].saldo) {
                printf("Saldo tidak cukup!\n");
            } else {
                daftarNasabah[index].saldo -= jumlah;
                printf("Penarikan berhasil. Saldo sekarang: Rp %.2f\n", daftarNasabah[index].saldo);
            }
            break;
        default:
            printf("Pilihan tidak valid.\n");
    }
    system("pause");
    system("cls");
}

int menulogin(usr users[MAX_USER], int *jumlahUser);

void menuNasabah(usr users[], int *jumlahUser) {
    int pilihan;
    do {
        printf("_____________________________\n");
        printf("|__________Nasabah__________|\n");
        printf("|1. Kelola Data Nasabah     |\n");
        printf("|2. Kalkulasi               |\n");
        printf("|3. Logout                  |\n");
        printf("|___________________________|\n");
        printf("Masukkan Pilihan Anda : ");
        scanf("%d", &pilihan);
        while (getchar() != '\n');

        switch (pilihan) {
            case 1: {
                int subPilihan;
                do {
                    system("cls");
                    printf("_______________________________\n");
                    printf("|______Kelola Nasabah_________|\n");
                    printf("|1. Tambah Nasabah            |\n");
                    printf("|2. Tampilkan Nasabah         |\n");
                    printf("|3. Update Nama Nasabah       |\n");
                    printf("|4. Cari Nasabah              |\n");
                    printf("|5. Hapus Nasabah             |\n");
                    printf("|6. Kembali ke Menu Utama     |\n");
                    printf("|_____________________________|\n");
                    printf("Masukkan Pilihan Anda: ");
                    scanf("%d", &subPilihan);
                    while (getchar() != '\n');

                    switch (subPilihan) {
                        case 1:
                            system("cls");
                            tambahNasabah();
                            system("pause");
                            break;
                        case 2:
                            system("cls");
                            DataNasabah();
                            system("pause");
                            break;
                        case 3:
                            system("cls");
                            updateNasabah();
                            system("pause");
                            break;
                        case 4:
                            system("cls");
                            search();
                            system("pause");
                            break;
                        case 5:
                            system("cls");
                            hapusNasabah();
                            system("pause");
                            break;
                    }
                } while (subPilihan != 6);
                system("cls");
                break;
            }
            case 2:
                system("cls");
                kalkulasiUang();
                break;
            case 3:
                system("cls");
                printf("Terima kasih telah menggunakan program ini.\n");
                system("pause");
                menulogin(users, jumlahUser);
                break;
        }
    } while (pilihan != 3);
}

int menulogin(usr users[], int *jumlahUser) {
    int milih;
    bool ulang = 1;

    while (ulang) {
        system("cls");
        printf("__________________________\n");
        printf("|__________Menu__________|\n");
        printf("|1. Register             |\n");
        printf("|2. Login                |\n");
        printf("|3. Exit                 |\n");
        printf("|________________________|\n");
        printf("Masukkan Pilihan Anda : ");
        scanf("%d", &milih);
        while (getchar() != '\n');

        switch (milih) {
            case 1:
                system("cls");
                if (regis(users, jumlahUser)) {
                    printf("Registrasi User Baru Berhasil\n");
                } else {
                    printf("Registrasi gagal, username sudah dipakai.\n");
                }
                system("pause");
                break;
            case 2:
                system("cls");
                if (login(users, jumlahUser)) {
                    printf("Login berhasil\n");
                    system("pause");
                    system("cls");
                    ulang = 0;
                    menuNasabah(users, jumlahUser);
                } else {
                    printf("Login gagal, username atau password salah.\n");
                    system("pause");
                }
                break;
            case 3:
                printf("Keluar dari program\n");
                namaDev();
                system("pause");
                ulang = 0;
                break;
        }
    }
    return 0;
}

int main() {
    usr users[MAX_USER];
    int jumlahUser = 0;
    int jumlahNasabah = 0;
    LoadUserFromFile(users, &jumlahUser);
    menulogin(users, &jumlahUser);
    return 0;
}
