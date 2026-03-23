#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int MAX_KERETA = 50;

struct Kereta {
    string nomorKereta;
    string namaKereta;
    string asal;
    string tujuan;
    string jamBerangkat;
    string jamTiba;
    int    hargaTiket;
    int    kursiTersedia;
};

Kereta daftarKereta[MAX_KERETA];
int    jumlahKereta = 0;

void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void garis(char c = '=', int len = 45) {
    for (int i = 0; i < len; i++) cout << c;
    cout << "\n";
}

void judulBox(const string& s) {
    garis();
    cout << "  " << s << "\n";
    garis();
}

void tekanEnter() {
    cout << "\n  Tekan Enter untuk melanjutkan...";
    cin.get();
}

void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void inisialisasiData() {
    daftarKereta[0] = {"KA001", "Argo Wilis",   "Bandung",  "Surabaya",      "08:00", "16:30", 450000, 40};
    daftarKereta[1] = {"KA002", "Pasundan",     "Surabaya", "Bandung",       "17:00", "04:30", 380000, 35};
    daftarKereta[2] = {"KA003", "Harina",       "Bandung",  "Semarang",      "17:30", "07:00", 420000, 30};
    daftarKereta[3] = {"KA004", "Progo",        "Jakarta",  "Yogyakarta",    "09:00", "17:00", 250000, 50};
    daftarKereta[4] = {"KA005", "Putri Deli",   "Medan",    "Tanjung Balai", "09:30", "16:00", 350000, 45};
    jumlahKereta = 5;
}

void tampilkanSemua(Kereta* arr, int n) {
    string batasLuar = "+------+----------+------------------------+----------------+------------------+------------+---------+--------------+---------+";

    if (n == 0) {
        cout << "  [!] Belum ada data kereta.\n";
        garis();
        return;
    }

    cout << batasLuar << "\n";
    cout << "| " << left << setw(4)  << "No"
         << " | " << setw(8)  << "No.KA"
         << " | " << setw(22) << "Nama Kereta"
         << " | " << setw(14) << "Asal"
         << " | " << setw(16) << "Tujuan"
         << " | " << setw(10)  << "Berangkat"
         << " | " << setw(7)  << "Tiba"
         << " | " << setw(12) << "Harga(Rp)"
         << " | " << setw(7)  << "Kursi"
         << " |\n";
    cout << batasLuar << "\n";

    for (int i = 0; i < n; i++) {
        cout << "| " << left << setw(4)  << (i + 1)
             << " | " << setw(8)  << (arr + i)->nomorKereta
             << " | " << setw(22) << (arr + i)->namaKereta
             << " | " << setw(14) << (arr + i)->asal
             << " | " << setw(16) << (arr + i)->tujuan
             << " | " << setw(10)  << (arr + i)->jamBerangkat
             << " | " << setw(7)  << (arr + i)->jamTiba
             << " | " << setw(12) << (arr + i)->hargaTiket
             << " | " << setw(7)  << (arr + i)->kursiTersedia
             << " |\n";
    }

    cout << batasLuar << "\n";
    cout << "  Total: " << n << " kereta terdaftar\n";
}

void tambahKereta(Kereta* arr, int& n) {
    judulBox("         TAMBAH DATA KERETA BARU");
    tampilkanSemua(arr, n);
    cout << "\n  Masukkan data kereta baru:\n";

    if (n >= MAX_KERETA) {
        cout << "  [!] Error: Kapasitas penuh! Maks " << MAX_KERETA << " kereta.\n";
        return;
    }

    Kereta baru;

    cout << "  Nomor Kereta   : "; cin >> baru.nomorKereta;
    cin.ignore(1000, '\n');

    for (int i = 0; i < n; i++) {
        if ((arr + i)->nomorKereta == baru.nomorKereta) {
            cout << "  [!] Error: Nomor " << baru.nomorKereta << " sudah terdaftar!\n";
            return;
        }
    }

    cout << "  Nama Kereta    : "; getline(cin, baru.namaKereta);
    cout << "  Kota Asal      : "; getline(cin, baru.asal);
    cout << "  Kota Tujuan    : "; getline(cin, baru.tujuan);
    cout << "  Jam Berangkat  : "; getline(cin, baru.jamBerangkat);
    cout << "  Jam Tiba       : "; getline(cin, baru.jamTiba);
    cout << "  Harga Tiket    : Rp "; cin >> baru.hargaTiket;
    cin.ignore(1000, '\n');
    cout << "  Kursi Tersedia : "; cin >> baru.kursiTersedia;
    cin.ignore(1000, '\n');

    if (baru.namaKereta.empty() || baru.asal.empty() || baru.tujuan.empty()) {
        cout << "\n  [!] Error: Nama, asal, dan tujuan tidak boleh kosong!\n";
        return;
    } else if (baru.hargaTiket <= 0) {
        cout << "\n  [!] Error: Harga tiket harus lebih dari Rp 0!\n";
        return;
    } else if (baru.kursiTersedia < 0) {
        cout << "\n  [!] Error: Jumlah kursi tidak boleh negatif!\n";
        return;
    }

    *(arr + n) = baru;
    n++;

    garis('-', 48);
    cout << "  [+] Kereta \"" << baru.namaKereta
         << "\" (" << baru.nomorKereta << ") berhasil ditambahkan!\n";
}

void linearSearch(Kereta* arr, int n) {
    judulBox("         CARI KERETA BERDASARKAN RUTE");
    tampilkanSemua(arr, n);

    if (n == 0) {
        return;
    }

    string asal, tujuan;
    cout << "\n  Kota Asal   : "; getline(cin, asal);
    cout << "  Kota Tujuan : "; getline(cin, tujuan);

    if (asal.empty() || tujuan.empty()) {
        cout << "\n  [!] Error: Kota asal dan tujuan tidak boleh kosong!\n";
        return;
    }

    string asalLow = "", tujuanLow = "";
    for (char c : asal)   asalLow   += (char)tolower(c);
    for (char c : tujuan) tujuanLow += (char)tolower(c);

    cout << "\n  Mencari rute: " << asal << " --> " << tujuan << "\n";

    bool ditemukan = false;
    int  count     = 0;

    string batasHasil = "+------+----------+------------------------+------------+---------+--------------+---------+";

    for (int i = 0; i < n; i++) {
        string a = "", t = "";
        for (char c : (arr + i)->asal)   a += (char)tolower(c);
        for (char c : (arr + i)->tujuan) t += (char)tolower(c);

        if (a == asalLow && t == tujuanLow) {
            if (!ditemukan) {
                cout << batasHasil << "\n";
                cout << "| " << left << setw(4)  << "No"
                     << " | " << setw(8)  << "No.KA"
                     << " | " << setw(22) << "Nama Kereta"
                     << " | " << setw(10)  << "Berangkat"
                     << " | " << setw(7)  << "Tiba"
                     << " | " << setw(12) << "Harga(Rp)"
                     << " | " << setw(7)  << "Kursi"
                     << " |\n";
                cout << batasHasil << "\n";
            }
            count++;
            ditemukan = true;
            cout << "| " << left << setw(4)  << count
                 << " | " << setw(8)  << (arr + i)->nomorKereta
                 << " | " << setw(22) << (arr + i)->namaKereta
                 << " | " << setw(10)  << (arr + i)->jamBerangkat
                 << " | " << setw(7)  << (arr + i)->jamTiba
                 << " | " << setw(12) << (arr + i)->hargaTiket
                 << " | " << setw(7)  << (arr + i)->kursiTersedia
                 << " |\n";
        }
    }

    if (!ditemukan) {
        garis('-');
        cout << "  [!] Tidak ada kereta untuk rute "
             << asal << " --> " << tujuan << "\n";
        garis();
    } else {
        cout << batasHasil << "\n";
        cout << "  Ditemukan " << count << " kereta untuk rute tersebut.\n";
        cout << "  Kompleksitas: O(n)\n";
    }
}

void sortTemp(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->nomorKereta < (arr + minIdx)->nomorKereta)
                minIdx = j;
        }
        if (minIdx != i)
            swapKereta(arr + i, arr + minIdx);
    }
}

void jumpSearch(Kereta* arr, int n) {
    judulBox("      CARI BERDASARKAN NOMOR KERETA");
    tampilkanSemua(arr, n);

    if (n == 0) {
        return;
    }

    string target;
    cout << "\n  Nomor Kereta yang dicari : "; getline(cin, target);

    if (target.empty()) {
        cout << "  [!] Error: Nomor kereta tidak boleh kosong!\n";
        return;
    }

    Kereta temp[MAX_KERETA];
    for (int i = 0; i < n; i++) *(temp + i) = *(arr + i);
    sortTemp(temp, n);

    cout << "\n  Target : \"" << target << "\"\n";
    cout << "  Array diurutkan berdasarkan nomor kereta:\n";
    for (int i = 0; i < n; i++)
        cout << "    [" << i << "] "
             << (temp + i)->nomorKereta
             << " - " << (temp + i)->namaKereta << "\n";
    garis('-');

    int step    = (int)sqrt((double)n);
    int prev    = 0;
    int iterasi = 0;

    cout << "  n = " << n << "  |  step = sqrt(" << n << ") = " << step << "\n";
    cout << "  \n  [ FASE LOMPAT ]\n";

    int checkIdx = (step < n ? step : n) - 1;

    while ((temp + checkIdx)->nomorKereta < target) {
        iterasi++;
        cout << "  Iterasi " << setw(2) << iterasi
             << " | Indeks [" << checkIdx << "]"
             << " | \"" << (temp + checkIdx)->nomorKereta << "\""
             << " < \"" << target << "\""
             << " --> LOMPAT\n";

        prev = step;
        step += (int)sqrt((double)n);

        if (prev >= n) {
            cout << "\n  [!] Nomor \"" << target << "\" tidak ditemukan di data.\n";
            garis();
            return;
        }
        checkIdx = (step < n ? step : n) - 1;
    }

    iterasi++;
    cout << "  Iterasi " << setw(2) << iterasi
         << " | Indeks [" << checkIdx << "]"
         << " | \"" << (temp + checkIdx)->nomorKereta << "\""
         << " >= \"" << target << "\""
         << " --> BERHENTI, mulai fase linear\n";

    int batas = (step < n ? step : n);
    cout << "  [ FASE LINEAR (indeks " << prev << " s/d " << (batas - 1) << ") ]\n";

    bool ditemukan = false;
    while (prev < batas) {
        iterasi++;
        cout << "  Iterasi " << setw(2) << iterasi
             << " | Indeks [" << prev << "]"
             << " | \"" << (temp + prev)->nomorKereta << "\"";

        if ((temp + prev)->nomorKereta == target) {
            cout << " == \"" << target << "\" --> KETEMU!\n";
            ditemukan = true;
            cout << "  \n  DATA KERETA DITEMUKAN:";
            cout << "  \n  Nomor Kereta   : " << (temp + prev)->nomorKereta   << "\n";
            cout << "  Nama Kereta    : " << (temp + prev)->namaKereta    << "\n";
            cout << "  Rute           : " << (temp + prev)->asal
                 << " --> " << (temp + prev)->tujuan << "\n";
            cout << "  Jam Berangkat  : " << (temp + prev)->jamBerangkat  << "\n";
            cout << "  Jam Tiba       : " << (temp + prev)->jamTiba       << "\n";
            cout << "  Harga Tiket    : Rp " << (temp + prev)->hargaTiket << "\n";
            cout << "  Kursi Tersedia : " << (temp + prev)->kursiTersedia << "\n";
            break;
        }
        cout << " != \"" << target << "\" --> lanjut\n";
        prev++;
    }

    if (!ditemukan) {
        cout << "\n  [!] Nomor \"" << target << "\" tidak ditemukan.\n";
    }
    cout << "\n  Total iterasi : " << iterasi << "  |  Kompleksitas: O(sqrt(n))\n";
}

void mergeProses(Kereta* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];

    for (int i = 0; i < n1; i++) *(L + i) = *(arr + left + i);
    for (int j = 0; j < n2; j++) *(R + j) = *(arr + mid + 1 + j);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if ((L + i)->namaKereta <= (R + j)->namaKereta) {
            *(arr + k) = *(L + i);
            i++;
        } else {
            *(arr + k) = *(R + j);
            j++;
        }
        k++;
    }
    while (i < n1) { *(arr + k) = *(L + i); i++; k++; }
    while (j < n2) { *(arr + k) = *(R + j); j++; k++; }

    delete[] L;
    delete[] R;
}

void mergeSort(Kereta* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        mergeProses(arr, left, mid, right);
    }
}

void jalankanMergeSort(Kereta* arr, int& n) {
    judulBox("       URUTKAN NAMA KERETA (A-Z)");

    if (n == 0) {
        return;
    } else if (n == 1) {
        cout << "  [!] Hanya 1 kereta, tidak perlu sorting.\n";
        return;
    }

    cout << "  Data SEBELUM:\n";
    garis('-');
    for (int i = 0; i < n; i++)
        cout << "  [" << i << "] " << (arr + i)->namaKereta << "\n";

    mergeSort(arr, 0, n - 1);

    cout << "\n  Data SESUDAH:\n";
    garis('-');
    for (int i = 0; i < n; i++)
        cout << "  [" << i << "] " << (arr + i)->namaKereta << "\n";

    garis();
    cout << "  Data berhasil diurutkan A-Z!\n";
    cout << "  Kompleksitas: O(n log n)\n";
    garis();
    cout << "\n";
    tampilkanSemua(arr, n);
}

void selectionSort(Kereta* arr, int& n) {
    judulBox("         URUTKAN HARGA TIKET (TERMURAH)");

    if (n == 0) {
        return;
    } else if (n == 1) {
        cout << "  [!] Hanya 1 kereta, tidak perlu sorting.\n";
        return;
    }

    cout << "  Data SEBELUM Selection Sort:\n";
    garis('-');
    for (int i = 0; i < n; i++)
        cout << "  [" << i << "] "
             << left << setw(22) << (arr + i)->namaKereta
             << "Rp " << (arr + i)->hargaTiket << "\n";

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->hargaTiket < (arr + minIdx)->hargaTiket)
                minIdx = j;
        }
        if (minIdx != i)
            swapKereta(arr + i, arr + minIdx);
    }

    cout << "\n  Data SESUDAH Selection Sort:\n";
    garis('-');
    for (int i = 0; i < n; i++)
        cout << "  [" << i << "] "
             << left << setw(22) << (arr + i)->namaKereta
             << "Rp " << (arr + i)->hargaTiket << "\n";

    garis();
    cout << "  Data diurutkan dari harga termurah!\n";
    cout << "  Kompleksitas: O(n^2)\n";
    garis();
    cout << "\n";
    tampilkanSemua(arr, n);
}

void tampilkanMenu() {
    judulBox("SISTEM MANAJEMEN KEBERANGKATAN KERETA API");
    cout << "  [1] Tampil Semua Jadwal Kereta\n";
    cout << "  [2] Tambah Data Kereta Baru\n";
    cout << "  [3] Cari Rute Kereta\n";
    cout << "  [4] Cari Nomor Kereta\n";
    cout << "  [5] Urutkan Nama (A-Z)\n";
    cout << "  [6] Urutkan Harga (Termurah)\n";
    cout << "  [0] Keluar Program\n";
    garis();
    cout << "  Pilihan Anda: ";
}

int main() {
    inisialisasiData();

    int pilihan;

    do {
        bersihkanLayar();
        tampilkanMenu();

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(1000, '\n');
            pilihan = -1;
        } else {
            cin.ignore(1000, '\n');
        }

        bersihkanLayar();

        switch (pilihan) {
            case 1:
                judulBox("         JADWAL SEMUA KERETA API");
                tampilkanSemua(&daftarKereta[0], jumlahKereta);
                tekanEnter();
                break;
            case 2:
                tambahKereta(&daftarKereta[0], jumlahKereta);
                tekanEnter();
                break;
            case 3:
                linearSearch(&daftarKereta[0], jumlahKereta);
                tekanEnter();
                break;
            case 4:
                jumpSearch(&daftarKereta[0], jumlahKereta);
                tekanEnter();
                break;
            case 5:
                jalankanMergeSort(&daftarKereta[0], jumlahKereta);
                tekanEnter();
                break;
            case 6:
                selectionSort(&daftarKereta[0], jumlahKereta);
                tekanEnter();
                break;
            case 0:
                bersihkanLayar();
                judulBox("  TERIMA KASIH - SELAMAT BEPERGIAN!");
                cout << "      Program selesai. Sampai jumpa!\n";
                garis();
                break;
            default:
                cout << "  [!] Pilihan tidak valid! Masukkan angka 0-6.\n";
                tekanEnter();
                break;
        }

    } while (pilihan != 0);

    return 0;
}