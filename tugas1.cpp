#include <iostream>
#include <string>
using namespace std;

// Struktur node untuk grid 2D yang berbasis linked list
struct Node
{
    char id;                        // Nama titik (A..I)
    Node *up, *down, *left, *right; // Pointer ke tetangga arah (Atas, Bawah, Kiri, Kanan)
    Node *next;                     // Pointer ke node berikutnya dalam linked list (satu arah)

    // Konstruktor untuk inisialisasi node baru
    Node(char c) : id(c), up(nullptr), down(nullptr), left(nullptr), right(nullptr), next(nullptr) {}
};

// Fungsi untuk membangun grid 3x3 (A..I) secara efisien (O(1) lookup)
Node *buildGrid()
{
    Node *nodes[9];                        // Array sementara untuk menyimpan referensi ke 9 node
    Node *head = nullptr, *tail = nullptr; // Pointer untuk head dan tail linked list

    // Loop untuk membuat 9 node (A sampai I) dan menyambungkannya ke linked list
    for (int i = 0; i < 9; ++i)
    {
        nodes[i] = new Node('A' + i); // Buat node baru dengan huruf A-I
        if (!head)
        {
            head = tail = nodes[i]; // Jika head kosong, jadikan node pertama sebagai head dan tail
        }
        else
        {
            tail->next = nodes[i]; // Sambungkan tail ke node baru
            tail = nodes[i];       // Geser tail ke node baru
        }
    }

    // Loop untuk menyambungkan pointer arah (up, down, left, right)
    for (int k = 0; k < 9; ++k)
    {
        int r = k / 3; // Menghitung baris (0, 1, 2)
        int c = k % 3; // Menghitung kolom (0, 1, 2)

        if (c > 0)
            nodes[k]->left = nodes[k - 1]; // Jika bukan kolom paling kiri, sambung ke kiri
        if (c < 2)
            nodes[k]->right = nodes[k + 1]; // Jika bukan kolom paling kanan, sambung ke kanan
        if (r > 0)
            nodes[k]->up = nodes[k - 3]; // Jika bukan baris paling atas, sambung ke atas
        if (r < 2)
            nodes[k]->down = nodes[k + 3]; // Jika bukan baris paling bawah, sambung ke bawah
    }
    return head; // Kembalikan head dari linked list
}

// Fungsi untuk mencari node berdasarkan huruf
Node *find(Node *head, char id)
{
    for (; head; head = head->next)
    { // Iterasi menelusuri linked list
        if (head->id == id)
            return head; // Jika ketemu, kembalikan node tersebut
    }
    return nullptr; // Jika tidak ketemu, kembalikan nullptr
}

// Fungsi untuk mencetak denah peta ke layar
void printMap(Node *cur)
{
    // Lambda function untuk menentukan format cetak (kurung siku jika posisi pemain)
    auto cell = [&](char c) -> string
    {
        if (cur && cur->id == c)
            return string("[") + c + "]";
        return string(" ") + c + " ";
    };

    cout << "\n=== Denah Peta 3x3 ===\n";
    cout << cell('A') << "-" << cell('B') << "-" << cell('C') << "\n";
    cout << " |   |   |\n";
    cout << cell('D') << "-" << cell('E') << "-" << cell('F') << "\n";
    cout << " |   |   |\n";
    cout << cell('G') << "-" << cell('H') << "-" << cell('I') << "\n\n";
}

// Fungsi untuk menormalisasi input arah dari user
string normDir(string s)
{
    for (char &ch : s)
        ch = (char)tolower((unsigned char)ch); // Ubah input jadi huruf kecil semua

    if (s == "kanan" || s == "right" || s == "r")
        return "right"; // Deteksi arah kanan
    if (s == "kiri" || s == "left" || s == "l")
        return "left"; // Deteksi arah kiri
    if (s == "atas" || s == "up" || s == "u")
        return "up"; // Deteksi arah atas
    if (s == "bawah" || s == "down" || s == "d")
        return "down"; // Deteksi arah bawah
    return "";         // Kembalikan string kosong jika tidak valid
}

// Fungsi untuk mengeksekusi pergerakan node
Node *moveTo(Node *cur, const string &dir)
{
    if (!cur)
        return nullptr; // Keamanan: Cegah crash jika node saat ini kosong
    if (dir == "right")
        return cur->right;
    if (dir == "left")
        return cur->left;
    if (dir == "up")
        return cur->up;
    if (dir == "down")
        return cur->down;
    return nullptr;
}

// Struktur untuk linked list riwayat jejak perjalanan
struct Trace
{
    char id;                                // Data node jejak
    Trace *next;                            // Pointer ke jejak selanjutnya
    Trace(char c) : id(c), next(nullptr) {} // Konstruktor
};

// Fungsi untuk menambahkan jejak baru di akhir linked list jejak
void tracePush(Trace *&h, Trace *&t, char id)
{
    Trace *n = new Trace(id); // Buat node jejak baru
    if (!h)
        h = t = n; // Jika kosong, jadikan head dan tail
    else
    {
        t->next = n; // Sambungkan di akhir
        t = n;       // Geser tail
    }
}

// Fungsi untuk mencetak seluruh riwayat jejak
void tracePrint(Trace *h)
{
    for (Trace *p = h; p; p = p->next)
    { // Iterasi jejak
        if (p != h)
            cout << " -> "; // Tambahkan panah kecuali untuk elemen pertama
        cout << p->id;      // Cetak ID jejak
    }
    cout << "\n";
}

// Fungsi untuk membersihkan memori grid (Cegah Memory Leak)
void freeGrid(Node *&head)
{
    while (head)
    {                      // Selama linked list belum kosong
        Node *tmp = head;  // Simpan node saat ini
        head = head->next; // Geser head ke depan
        delete tmp;        // Hapus node yang disimpan
    }
}

// Fungsi untuk membersihkan memori jejak (Cegah Memory Leak)
void freeTrace(Trace *&h)
{
    while (h)
    {                   // Selama linked list jejak belum kosong
        Trace *tmp = h; // Simpan jejak saat ini
        h = h->next;    // Geser head jejak
        delete tmp;     // Hapus jejak
    }
}

int main()
{
    Node *head = buildGrid(); // Bangun grid

    cout << "=== Denah Peta 3x3 (A..I) ===\n";
    cout << "Masukkan titik awal (A..I): ";
    char start;
    cin >> start;
    start = (char)toupper((unsigned char)start); // Ubah input titik awal ke huruf kapital

    Node *cur = find(head, start); // Cari node awal
    if (!cur)
    {
        cout << "Titik awal tidak valid.\n";
        freeGrid(head); // Bebaskan memori jika input salah
        return 0;       // Keluar program
    }

    Trace *th = nullptr, *tt = nullptr; // Inisialisasi head dan tail untuk jejak
    tracePush(th, tt, cur->id);         // Simpan titik awal ke dalam jejak

    printMap(cur); // Cetak peta awal

    cout << "Input arah: kanan/kiri/atas/bawah atau r/l/u/d\n";
    cout << "Ketik 'stop' untuk selesai.\n";

    while (true)
    { // Loop utama permainan
        cout << "Langkah: ";
        string step;
        cin >> step; // Baca input langkah

        if (step == "stop" || step == "STOP")
            break; // Hentikan loop jika input stop

        string d = normDir(step); // Normalisasi arah input
        if (d.empty())
        {
            cout << "Arah tidak dikenali.\n";
            continue; // Ulangi loop jika salah ketik
        }

        Node *next = moveTo(cur, d); // Coba berpindah
        if (!next)
        {
            cout << "Tidak bisa jalan ke \"" << step << "\" dari " << cur->id << " (Mentok!).\n";
            printMap(cur); // Cetak ulang posisi terakhir
            continue;      // Tolak langkah
        }

        cur = next;                 // Update posisi jika berhasil
        tracePush(th, tt, cur->id); // Catat ke riwayat jejak
        printMap(cur);              // Cetak peta setelah berpindah
    }

    cout << "\nPosisi akhir: " << cur->id << "\n";
    cout << "Jejak: ";
    tracePrint(th); // Cetak riwayat perjalanan

    // Bersihkan semua sisa memori sebelum program ditutup
    freeGrid(head);
    freeTrace(th);

    return 0;
}