#include <iostream>
using namespace std;

// Struktur node linked list
struct Node
{
    int data;
    Node *next;
};

// Pengembangan: Mengubah fungsi tambah menjadi murni rekursif
void tambahRekursif(Node *&head, int nilai)
{
    // Basis rekursi: Jika mencapai akhir (atau list kosong), buat node di sini
    if (head == nullptr)
    {
        head = new Node{nilai, nullptr};
        return;
    }
    // Jika belum di ujung, panggil fungsi yang sama untuk node selanjutnya
    tambahRekursif(head->next, nilai);
}

// Menampilkan linked list secara rekursif
void tampil(Node *head)
{
    if (head == nullptr)
        return;                // Basis rekursi: berhenti jika kosong
    cout << head->data << " "; // Cetak data saat ini
    tampil(head->next);        // Panggil cetak untuk node selanjutnya
}

// Mencari data secara rekursif
bool cari(Node *head, int key)
{
    if (head == nullptr)
        return false; // Tidak ketemu sampai akhir
    if (head->data == key)
        return true;              // Ketemu di node saat ini
    return cari(head->next, key); // Cari di node selanjutnya
}

// Menghitung jumlah node secara rekursif
int hitung(Node *head)
{
    if (head == nullptr)
        return 0;                  // Jika kosong, jumlah = 0
    return 1 + hitung(head->next); // Tambah 1, lalu hitung sisanya
}

// Pengembangan: Dealokasi memori secara rekursif (Mencegah Memory Leak)
void hapusListRekursif(Node *&head)
{
    if (head == nullptr)
        return;                    // Jika sudah habis, kembali
    hapusListRekursif(head->next); // Instruksikan hapus untuk node selanjutnya dulu
    delete head;                   // Setelah ujung terhapus, hapus diri sendiri
    head = nullptr;                // Netralkan pointer
}

int main()
{
    Node *head = nullptr; // Perbaikan: Gunakan nullptr

    // Memasukkan data dengan rekursi
    tambahRekursif(head, 10);
    tambahRekursif(head, 25);
    tambahRekursif(head, 7);
    tambahRekursif(head, 19);
    tambahRekursif(head, 30);

    cout << "Isi Linked List: ";
    tampil(head);
    cout << endl;

    int key;
    cout << "Masukkan data yang dicari: ";
    cin >> key;

    if (cari(head, key))
        cout << "Data ditemukan!" << endl;
    else
        cout << "Data tidak ditemukan." << endl;

    cout << "Jumlah node: " << hitung(head) << endl;

    // Bersihkan RAM
    hapusListRekursif(head);

    return 0;
}