#include <iostream> // library untuk input-output (cin, cout)
#include <string>   // library untuk tipe data string
#include <limits>   // library untuk numeric_limits
using namespace std;

// ====================== STRUCT DATA ======================

// struct untuk menyimpan data pelanggan bengkel
struct Bengkel
{
    string nama;    // nama pelanggan
    string plat;    // nomor plat kendaraan
    string keluhan; // keluhan kendaraan
};

// struct node untuk linked list
struct Node
{
    Bengkel data; // data pelanggan
    Node *next;   // pointer ke node berikutnya
};

// ====================== QUEUE (FIFO) ======================
// implementasi queue menggunakan linked list
struct QueueLL
{
    Node *front; // pointer ke depan antrian
    Node *rear;  // pointer ke belakang antrian

    // konstruktor untuk inisialisasi queue kosong
    QueueLL()
    {
        front = nullptr; // antrian depan kosong
        rear = nullptr;  // antrian belakang kosong
    }

    // fungsi untuk mengecek apakah queue kosong
    bool empty() const
    {
        return front == nullptr; // true jika front nullptr
    }

    // fungsi enqueue (menambah data ke belakang)
    void push(const Bengkel &b)
    {
        Node *baru = new Node; // alokasi node baru
        baru->data = b;        // mengisi data pelanggan
        baru->next = nullptr;  // node terakhir menunjuk nullptr

        if (empty())
        {                        // jika queue masih kosong
            front = rear = baru; // front dan rear menunjuk node baru
        }
        else
        {                      // jika queue sudah ada isi
            rear->next = baru; // menyambungkan node terakhir
            rear = baru;       // update rear ke node baru
        }
    }

    // fungsi dequeue (menghapus data dari depan)
    Bengkel pop()
    {
        Node *hapus = front;         // menyimpan node yang akan dihapus
        Bengkel hasil = hapus->data; // menyimpan data pelanggan

        front = front->next; // memindahkan front ke node berikutnya

        if (front == nullptr)
        {                   // jika setelah pop queue kosong
            rear = nullptr; // rear juga dikosongkan
        }

        delete hapus; // menghapus node dari memori
        return hasil; // mengembalikan data pelanggan
    }

    // fungsi menampilkan seluruh isi queue
    void print() const
    {
        if (empty())
        { // mengecek jika queue kosong
            cout << ">> Tidak ada antrian saat ini.\n";
            return;
        }

        cout << "\n--- DAFTAR ANTRIAN (Menunggu Diproses) ---\n";
        Node *cur = front; // pointer bantu dari depan
        int i = 1;         // nomor urut antrian

        while (cur != nullptr)
        { // loop sampai node terakhir
            cout << i++ << ". "
                 << cur->data.nama << " | "
                 << cur->data.plat << " | "
                 << cur->data.keluhan << endl;
            cur = cur->next; // berpindah ke node berikutnya
        }
    }

    // fungsi membersihkan seluruh queue
    void clear()
    {
        while (!empty())
            pop(); // menghapus satu per satu node dari depan
    }
};

// ====================== STACK (LIFO) ======================
// implementasi stack menggunakan linked list
struct StackLL
{
    Node *topNode; // pointer ke elemen paling atas

    // konstruktor stack kosong
    StackLL()
    {
        topNode = nullptr; // stack awalnya kosong
    }

    // fungsi mengecek apakah stack kosong
    bool empty() const
    {
        return topNode == nullptr; // true jika stack kosong
    }

    // fungsi push (menambah data ke atas stack)
    void push(const Bengkel &b)
    {
        Node *baru = new Node; // membuat node baru
        baru->data = b;        // mengisi data pelanggan
        baru->next = topNode;  // node baru menunjuk top lama
        topNode = baru;        // top diperbarui ke node baru
    }

    // fungsi pop (menghapus data teratas stack)
    Bengkel pop()
    {
        Node *hapus = topNode;       // menyimpan node teratas
        Bengkel hasil = hapus->data; // menyimpan datanya

        topNode = topNode->next; // memindahkan top ke node berikutnya
        delete hapus;            // menghapus node dari memori
        return hasil;            // mengembalikan data
    }

    // fungsi menampilkan isi stack
    void print() const
    {
        if (empty())
        { // mengecek jika stack kosong
            cout << ">> Stack pelayanan kosong (Tidak ada kendaraan yang sedang dikerjakan)\n";
            return;
        }

        cout << "\n--- STACK PELAYANAN (Sedang Dikerjakan) ---\n";
        Node *cur = topNode; // pointer bantu dari top
        int i = 1;           // nomor urut tampilan

        while (cur != nullptr)
        { // loop sampai node terakhir
            cout << i++ << ". "
                 << cur->data.nama << " | "
                 << cur->data.plat << " | "
                 << cur->data.keluhan << endl;
            cur = cur->next; // berpindah ke node berikutnya
        }
    }

    // fungsi membersihkan stack
    void clear()
    {
        while (!empty())
            pop(); // menghapus satu per satu
    }
};

// ====================== PROGRAM UTAMA ======================
// Fungsi pembantu untuk menjeda layar
void pauseScreen()
{
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

int main()
{
    QueueLL antrian;   // objek queue (FIFO)
    StackLL pelayanan; // objek stack (LIFO)
    int menu;          // variabel pilihan menu

    do
    {
        system("cls || clear"); // Membersihkan layar setiap kali menu dirender ulang

        cout << "\n=== APLIKASI BENGKEL ===\n";
        cout << "1. Tambah Antrian\n";
        cout << "2. Panggil Antrian ke Pelayanan (Queue ke Stack)\n";
        cout << "3. Lihat Daftar Antrian\n";
        cout << "4. Lihat Daftar Sedang Dilayani\n";
        cout << "5. Selesaikan Pelayanan (Hapus dari Stack)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";

        cin >> menu; // input pilihan menu

        // Mencegah infinite loop jika input bukan angka
        if (cin.fail())
        {
            cin.clear();                                         // Hapus flag error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Buang input yang salah dari buffer
            cout << "Input tidak valid! Harap masukkan angka.\n";
            pauseScreen();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan newline di buffer

        switch (menu)
        {
        case 1:
        {
            Bengkel b; // variabel data pelanggan
            cout << "\n[TAMBAH ANTRIAN]\n";
            cout << "Nama Pelanggan : ";
            getline(cin, b.nama);
            cout << "No Plat        : ";
            getline(cin, b.plat);
            cout << "Keluhan        : ";
            getline(cin, b.keluhan);

            antrian.push(b); // memasukkan ke queue
            cout << ">> Antrian berhasil ditambahkan\n";
            pauseScreen();
            break;
        }
        case 2:
        {
            cout << "\n[PROSES KE PELAYANAN]\n";
            if (antrian.empty())
            {
                cout << ">> Antrian masih kosong.\n";
            }
            else
            {
                Bengkel b = antrian.pop(); // mengambil dari queue
                pelayanan.push(b);         // memasukkan ke stack

                cout << ">> Kendaraan mulai dilayani:\n";
                cout << "Nama    : " << b.nama << "\n";
                cout << "Plat    : " << b.plat << "\n";
                cout << "Keluhan : " << b.keluhan << "\n";
            }
            pauseScreen();
            break;
        }
        case 3:
            antrian.print(); // menampilkan antrian
            pauseScreen();
            break;
        case 4:
            pelayanan.print(); // menampilkan stack pelayanan
            pauseScreen();
            break;
        case 5:
        {
            cout << "\n[SELESAI PELAYANAN]\n";
            if (pelayanan.empty())
            {
                cout << ">> Tidak ada kendaraan yang sedang dilayani.\n";
            }
            else
            {
                Bengkel b = pelayanan.pop(); // menghapus dari stack
                cout << ">> Pelayanan SELESAI untuk kendaraan:\n";
                cout << "Plat: " << b.plat << " milik " << b.nama << "\n";
            }
            pauseScreen();
            break;
        }
        case 0:
            cout << "\nProgram selesai. Membersihkan memori...\n";
            break;
        default:
            cout << "Menu tidak valid. Pilih angka 0-5.\n";
            pauseScreen();
        }
    } while (menu != 0);

    antrian.clear();   // menghapus seluruh data queue
    pelayanan.clear(); // menghapus seluruh data stack

    return 0; // akhir program
}
