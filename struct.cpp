#include <iostream>
#include <string> // Perbaikan: Menambahkan library string wajib
using namespace std;

// Definisi Struct Laptop
struct Laptop
{
    string Merek;
    string Model;
    string KapasitasRAM;
    int TahunProduksi;

    // Pengembangan: Konstruktor untuk mempermudah pembuatan objek
    Laptop(string merk = "", string model = "", string ram = "", int tahun = 0)
    {
        Merek = merk;
        Model = model;
        KapasitasRAM = ram;
        TahunProduksi = tahun;
    }
};

// Pengembangan: Fungsi cetak khusus agar main() lebih bersih
void tampilkanLaptop(const Laptop &laptop)
{
    cout << "Merek Laptop   : " << laptop.Merek << endl;
    cout << "Model Laptop   : " << laptop.Model << endl;
    cout << "Kapasitas RAM  : " << laptop.KapasitasRAM << endl;
    cout << "Tahun Produksi : " << laptop.TahunProduksi << endl;
    cout << "------------------------------\n";
}

int main()
{
    // Memanggil konstruktor struct
    Laptop laptop1("Asus", "Asus Vivobook X14", "24GB", 2023);

    // Pengembangan: Demonstrasi lebih dari 1 data (Array of Struct)
    Laptop laptop2("Lenovo", "Legion 5 Pro", "32GB", 2024);

    cout << "=== Data Laptop ===\n";
    tampilkanLaptop(laptop1);
    tampilkanLaptop(laptop2);

    return 0; // Perbaikan: Menghapus titik koma (;) di luar kurung kurawal main()
}