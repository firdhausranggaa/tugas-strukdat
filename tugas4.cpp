#include <iostream>
#include <string>
using namespace std;

// ================== STACK ==================
struct NodeStack
{
    string data;     // Data stack
    NodeStack *next; // Pointer ke node di bawahnya
};

// Fungsi memasukkan data ke tumpukan teratas
void push(NodeStack *&top, string value)
{
    NodeStack *newNode = new NodeStack{value, top}; // Buat node baru, next-nya menunjuk ke top lama
    top = newNode;                                  // Geser top ke node baru
}

// Fungsi mengambil dan menghapus data tumpukan teratas
void pop(NodeStack *&top)
{
    if (top == nullptr)
    { // Cek jika kosong
        cout << "Stack kosong!\n";
        return;
    }
    NodeStack *temp = top;                 // Simpan top
    cout << "Pop: " << temp->data << endl; // Tampilkan data yang dipop
    top = top->next;                       // Turunkan top
    delete temp;                           // Hapus node lama dari memori
}

// Fungsi melihat tumpukan teratas tanpa menghapusnya
void peekStack(NodeStack *top)
{
    if (top == nullptr)
    {
        cout << "Stack kosong!\n";
        return;
    }
    cout << "Top: " << top->data << endl;
}

// Fungsi pembersih Stack secara menyeluruh (Mencegah Memory Leak)
void clearStack(NodeStack *&top)
{
    while (top != nullptr)
    {
        NodeStack *temp = top;
        top = top->next;
        delete temp; // Dealokasi semua node secara hening
    }
}

// ================== QUEUE ==================
struct NodeQueue
{
    string data;     // Data antrean
    NodeQueue *next; // Pointer ke node antrean di belakangnya
};

// Fungsi memasukkan data ke barisan paling belakang (rear)
void enqueue(NodeQueue *&front, NodeQueue *&rear, string value)
{
    NodeQueue *newNode = new NodeQueue{value, nullptr}; // Node baru selalu di paling belakang
    if (rear == nullptr)
    {                           // Jika antrean kosong
        front = rear = newNode; // Front dan rear menunjuk ke node pertama
    }
    else
    {
        rear->next = newNode; // Sambung belakangan antrean ke node baru
        rear = newNode;       // Geser rear ke node baru
    }
}

// Fungsi mengambil data barisan paling depan (front)
void dequeue(NodeQueue *&front, NodeQueue *&rear)
{
    if (front == nullptr)
    { // Cek jika kosong
        cout << "Queue kosong!\n";
        return;
    }
    NodeQueue *temp = front;                   // Simpan front
    cout << "Dequeue: " << temp->data << endl; // Tampilkan data
    front = front->next;                       // Geser front ke belakangnya

    if (front == nullptr)
        rear = nullptr; // Jika setelah digeser kosong, kosongkan juga rear
    delete temp;        // Hapus node dari memori
}

// Fungsi melihat data antrean depan tanpa menghapusnya
void peekQueue(NodeQueue *front)
{
    if (front == nullptr)
    {
        cout << "Queue kosong!\n";
        return;
    }
    cout << "Front: " << front->data << endl;
}

// Fungsi pembersih Queue secara menyeluruh (Mencegah Memory Leak)
void clearQueue(NodeQueue *&front, NodeQueue *&rear)
{
    while (front != nullptr)
    {
        NodeQueue *temp = front;
        front = front->next;
        delete temp; // Dealokasi semua node secara hening
    }
    rear = nullptr;
}

int main()
{
    NodeStack *top = nullptr;   // Pointer stack awal
    NodeQueue *front = nullptr; // Pointer depan queue awal
    NodeQueue *rear = nullptr;  // Pointer belakang queue awal

    int pilihanUtama, pilihanSub;
    string value;

    do
    {
        cout << "\n=== MENU UTAMA ===\n"
             << "1. Stack\n"
             << "2. Queue\n"
             << "3. Berhenti\n"
             << "Pilih opsi: ";
        cin >> pilihanUtama;

        switch (pilihanUtama)
        {
        case 1: // Sub-menu Stack
            do
            {
                cout << "\n[MENU STACK]\n"
                     << "1. Push\n"
                     << "2. Pop\n"
                     << "3. Peek\n"
                     << "4. Kembali\n"
                     << "Pilih opsi: ";
                cin >> pilihanSub;

                switch (pilihanSub)
                {
                case 1:
                    cout << "Masukkan data: ";
                    cin.ignore(); // Bersihkan buffer enter
                    getline(cin, value);
                    push(top, value);
                    break;
                case 2:
                    pop(top);
                    break;
                case 3:
                    peekStack(top);
                    break;
                case 4:
                    cout << "Kembali ke menu utama.\n";
                    break;
                default:
                    cout << "Pilihan tidak valid!\n";
                }
            } while (pilihanSub != 4);
            break;

        case 2: // Sub-menu Queue
            do
            {
                cout << "\n[MENU QUEUE]\n"
                     << "1. Enqueue\n"
                     << "2. Dequeue\n"
                     << "3. Peek\n"
                     << "4. Kembali\n"
                     << "Pilih opsi: ";
                cin >> pilihanSub;

                switch (pilihanSub)
                {
                case 1:
                    cout << "Masukkan data: ";
                    cin.ignore(); // Bersihkan buffer enter
                    getline(cin, value);
                    enqueue(front, rear, value);
                    break;
                case 2:
                    dequeue(front, rear);
                    break;
                case 3:
                    peekQueue(front);
                    break;
                case 4:
                    cout << "Kembali ke menu utama.\n";
                    break;
                default:
                    cout << "Pilihan tidak valid!\n";
                }
            } while (pilihanSub != 4);
            break;

        case 3:
            cout << "Program selesai. Sedang membersihkan sisa memori...\n";
            // Panggil pembersih saat user memutuskan untuk exit program
            clearStack(top);
            clearQueue(front, rear);
            break;

        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihanUtama != 3);

    return 0;
}