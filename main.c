#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Define structure for student data
typedef struct {
    char nomorRegistrasi[20];
    char nama[50];
    int umur;
} Siswa;

// Function to add student data
void tambahDataSiswa() {
    FILE *file = fopen("database_siswa.txt", "a"); // Open file in append mode
    if (file == NULL) {
        printf("Gagal membuka file\n");
        return; // Return if file cannot be opened
    }

    Siswa siswa;
    printf("Masukan nomor registrasi: ");
    scanf("%s", siswa.nomorRegistrasi);
    printf("Masukan nama siswa: ");
    scanf(" %[^\n]s", siswa.nama);  // Use ' %[^\n]s' to read string with spaces
    printf("Masukan umur siswa: ");
    scanf("%d", &siswa.umur);

    // Write student data to file
    fprintf(file, "%s,%s,%d\n", siswa.nomorRegistrasi, siswa.nama, siswa.umur);
    fclose(file);

    printf("Data siswa berhasil ditambahkan.\n");
}

// Function to delete student data
void hapusDataSiswa() {
    char nomorRegistrasi[20];
    printf("Masukan nomor registrasi siswa yang ingin dihapus: ");
    scanf("%s", nomorRegistrasi);

    FILE *file = fopen("database_siswa.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file for storing remaining data
    if (file == NULL || tempFile == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    Siswa siswa;
    int found = 0;

    // Read data from the old file and copy to the temporary file
    while (fscanf(file, "%[^,],%[^,],%d\n", siswa.nomorRegistrasi, siswa.nama, &siswa.umur) != EOF) {
        if (strcmp(siswa.nomorRegistrasi, nomorRegistrasi) != 0) {
            fprintf(tempFile, "%s,%s,%d\n", siswa.nomorRegistrasi, siswa.nama, siswa.umur);
        } else {
            found = 1; // Found the student to delete
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace old file with temporary file if data was found
    if (found) {
        remove("database_siswa.txt");
        rename("temp.txt", "database_siswa.txt");
        printf("Data siswa berhasil dihapus.\n");
    } else {
        remove("temp.txt"); // Corrected from "temp.text" to "temp.txt"
        printf("Data siswa tidak ditemukan.\n");
    }
}

// Function to search for student data
void cariDataSiswa() {
    char kriteriaPencarian[50];
    printf("Masukan nomor registrasi atau nama siswa yang ingin dicari: ");
    scanf(" %[^\n]s", kriteriaPencarian); // Use ' %[^\n]s' to read string with spaces

    FILE *file = fopen("database_siswa.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    Siswa siswa;
    int found = 0;

    // Read each entry from the file and search for matching data
    while (fscanf(file, "%[^,],%[^,],%d\n", siswa.nomorRegistrasi, siswa.nama, &siswa.umur) != EOF) {
        if (strcmp(siswa.nomorRegistrasi, kriteriaPencarian) == 0 ||
            strcmp(siswa.nama, kriteriaPencarian) == 0) {
            printf("Data ditemukan: %s, %s, %d\n", siswa.nomorRegistrasi, siswa.nama, siswa.umur);
            found = 1;
        }
    }

    if (!found) {
        printf("Data siswa tidak ditemukan.\n");
    }

    fclose(file);
}

int main() {

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }

    int pilihan;

    do {
        printf("\nManajemen File Siswa\n");
        printf("1. Tambah Data Siswa\n");
        printf("2. Hapus Data Siswa\n");
        printf("3. Cari Data Siswa\n");
        printf("4. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahDataSiswa();
                break;
            case 2:
                hapusDataSiswa();
                break;
            case 3:
                cariDataSiswa();
                break;
            case 4:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                break;
        }
    } while (pilihan != 4);

    return 0;
}
