#include <iostream>
#include <string>
using namespace std;

// Struktur Node untuk Circular Doubly Linked List
struct Node
{
    string nama;       // Menyimpan data nama wilayah
    Node *prev, *next; // Pointer menunjuk ke node sebelumnya dan berikutnya

    // Konstruktor inisialisasi nama dan atur pointer ke nullptr
    Node(string n = "") : nama(move(n)), prev(nullptr), next(nullptr) {}
};

// Fungsi membuat ring baru yang hanya berisi 1 node
Node *make_single(const string &nama)
{
    Node *x = new Node(nama); // Alokasi node baru
    x->next = x->prev = x;    // Karena circular, next dan prev menunjuk ke dirinya sendiri
    return x;
}

// Fungsi menyisipkan node 'x' SETELAH node 'pos'
void insert_after(Node *pos, Node *x)
{
    if (!pos)
        return;          // Cegah crash jika referensi posisi kosong
    Node *a = pos;       // Node saat ini
    Node *b = pos->next; // Node berikutnya

    a->next = x; // Node saat ini menunjuk next ke node baru
    x->prev = a; // Node baru menunjuk prev ke node saat ini
    x->next = b; // Node baru menunjuk next ke node berikutnya
    b->prev = x; // Node berikutnya menunjuk prev ke node baru
}

// Fungsi menyisipkan node 'x' SEBELUM node 'pos'
void insert_before(Node *pos, Node *x)
{
    if (pos)
        insert_after(pos->prev, x); // Memanfaatkan fungsi insert_after pada node sebelumnya
}

// Fungsi menghapus node 't' dari ring dan mengembalikan node pengganti
Node *erase(Node *&head, Node *t)
{
    if (!t)
        return head; // Jika target kosong, tidak ada yang dihapus

    // Kondisi jika ring hanya tersisa 1 node (menunjuk dirinya sendiri)
    if (t->next == t)
    {
        delete t;       // Hapus node dari memori
        head = nullptr; // Ring sekarang kosong
        return nullptr; // Kembalikan nullptr
    }

    Node *p = t->prev; // Ambil node sebelum target
    Node *n = t->next; // Ambil node sesudah target

    p->next = n; // Sambungkan next node sebelumnya ke node sesudahnya
    n->prev = p; // Sambungkan prev node sesudahnya ke node sebelumnya

    if (head == t)
        head = n; // Jika target kebetulan head, geser head ke node berikutnya

    delete t; // Hapus node dari memori
    return n; // Kembalikan node sesudahnya sebagai posisi terkini
}

// Fungsi mengubah string menjadi huruf kecil (untuk pencarian tidak case sensitive)
string lower_copy(string s)
{
    for (char &c : s)
    {
        if (c >= 'A' && c <= 'Z')
            c = char(c - 'A' + 'a');
    }
    return s;
}

// Fungsi mencari node berdasarkan nama wilayah
Node *find_by_name(Node *head, const string &key)
{
    if (!head)
        return nullptr;              // Jika ring kosong, langsung return nullptr
    string target = lower_copy(key); // Konversi kunci ke lowercase

    Node *cur = head;
    do
    {
        if (lower_copy(cur->nama) == target)
            return cur;  // Jika cocok, kembalikan node tersebut
        cur = cur->next; // Pindah ke node selanjutnya
    } while (cur != head); // Berhenti jika sudah memutar kembali ke head

    return nullptr; // Tidak ditemukan
}

// Fungsi mencetak isi ring sebanyak 1 putaran penuh
void print_ring(Node *start)
{
    if (!start)
    { // Validasi ring kosong
        cout << "(ring kosong)\n";
        return;
    }

    Node *cur = start;
    cout << "\n== Daftar Wilayah (satu putaran) ==\n";
    do
    {
        cout << "[" << cur->nama << "]"; // Cetak nama wilayah
        if (cur == start)
            cout << "  <- (posisi sekarang)"; // Penanda posisi
        cout << "\n";
        cur = cur->next; // Geser ke node berikutnya
    } while (cur != start); // Loop hingga kembali ke awal mula

    cout << "===================================\n\n";
}

int main()
{
    // Persiapan ring awal
    Node *head = make_single("Wilayah-A");                 // Buat node pertama
    insert_after(head, new Node("Wilayah-B"));             // Tambah Wilayah-B
    insert_after(head->next, new Node("Wilayah-C"));       // Tambah Wilayah-C
    insert_after(head->next->next, new Node("Wilayah-D")); // Tambah Wilayah-D

    Node *cur = head; // Variabel penyimpan posisi saat ini

    cout << "=== Navigasi Wilayah (Circular Doubly Linked List) ===\n";
    cout << "Awal dibuat 4 wilayah: Wilayah-A, Wilayah-B, Wilayah-C, Wilayah-D\n";

    cout << "Mulai dari wilayah mana?: ";
    string startName;
    getline(cin >> ws, startName); // Baca input dengan toleransi spasi/newline

    if (!startName.empty())
    {
        if (Node *found = find_by_name(head, startName))
            cur = found; // Pindah jika ditemukan
        else
            cout << "Tidak ditemukan \"" << startName << "\". Mulai dari [" << cur->nama << "].\n";
    }

    while (true)
    {
        if (!cur)
            cout << "\nRing kosong. Pilih 3/4 untuk menambah wilayah, atau 0 untuk keluar.\n";
        else
            cout << "\nPosisi: [" << cur->nama << "]\n";

        cout << "Menu:\n"
             << " 1. Next (maju)\n"
             << " 2. Prev (mundur)\n"
             << " 3. Tambah wilayah SETELAH posisi sekarang\n"
             << " 4. Tambah wilayah SEBELUM posisi sekarang\n"
             << " 5. Hapus wilayah saat ini\n"
             << " 6. Cetak satu putaran\n"
             << " 0. Keluar\n"
             << "Pilih: ";

        int opsi;
        if (!(cin >> opsi))
            break; // Validasi mencegah infinite loop jika input bukan angka
        if (opsi == 0)
            break; // Exit program

        if (opsi == 1)
        {
            if (cur)
                cur = cur->next; // Maju
            else
                cout << "Ring kosong.\n";
        }
        else if (opsi == 2)
        {
            if (cur)
                cur = cur->prev; // Mundur
            else
                cout << "Ring kosong.\n";
        }
        else if (opsi == 3)
        {
            string n;
            cout << "Nama wilayah baru: ";
            getline(cin >> ws, n); // Ambil nama wilayah

            if (!cur)
                head = cur = make_single(n); // Jika kosong, inisiasi ulang ring
            else
                insert_after(cur, new Node(n)); // Insert setelah cur

            cout << "Ditambahkan SETELAH posisi.\n";
        }
        else if (opsi == 4)
        {
            string n;
            cout << "Nama wilayah baru: ";
            getline(cin >> ws, n);

            if (!cur)
                head = cur = make_single(n); // Jika kosong, inisiasi ulang ring
            else
                insert_before(cur, new Node(n)); // Insert sebelum cur

            cout << "Ditambahkan SEBELUM posisi.\n";
        }
        else if (opsi == 5)
        {
            if (!cur)
            {
                cout << "Ring kosong.\n";
                continue;
            }
            cout << "Menghapus [" << cur->nama << "]...\n";
            cur = erase(head, cur); // Panggil fungsi hapus, cur pindah ke node sebelahnya
        }
        else if (opsi == 6)
        {
            print_ring(cur ? cur : head); // Cetak putaran
        }
        else
        {
            cout << "Opsi tidak valid.\n";
        }
    }

    // Pembersihan Memory (Mencegah Leak)
    if (head)
    {
        Node *p = head->next;
        while (p != head)
        { // Loop membuang node selain head
            Node *tmp = p;
            p = p->next;
            delete tmp;
        }
        delete head; // Terakhir, hapus head
    }

    cout << "Selesai.\n";
    return 0;
}