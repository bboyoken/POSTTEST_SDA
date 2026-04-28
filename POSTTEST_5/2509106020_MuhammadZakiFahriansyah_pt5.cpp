#include <iostream>
#include <string>
using namespace std;

struct BarangNode {
    string namaBarang;
    int stok;
    BarangNode* next;

    BarangNode(string nama, int jumlah) {
        namaBarang = nama;
        stok = jumlah;
        next = nullptr;
    }
};

BarangNode* tambahBarang(BarangNode* head, string nama, int jumlah) {
    BarangNode* newNode = new BarangNode(nama, jumlah);
    if (head == nullptr) {
        newNode->next = newNode;
        return newNode;
    }
    
    BarangNode* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

void tampilkanStokSembako(BarangNode* head) {
    if (head == nullptr) {
        cout << "Gudang kosong." << endl;
        return;
    }

    BarangNode* temp = head;
    do {
        cout << "- " << temp->namaBarang << ": " << temp->stok << endl;
        temp = temp->next;
    } while (temp != head);
}

int main() {
    BarangNode* head = nullptr;
    
    head = tambahBarang(head, "Beras", 50);
    head = tambahBarang(head, "Minyak Goreng", 30);
    head = tambahBarang(head, "Gula Pasir", 20);
    head = tambahBarang(head, "Tepung Terigu", 15);

    cout << "Daftar Stok Sembako:" << endl;
    tampilkanStokSembako(head); 

    return 0;
}