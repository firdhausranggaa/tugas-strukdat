# Tugas Struktur Data - Informatika UPNVJT

Repositori ini berisi kumpulan *source code* C++ yang merupakan hasil pengerjaan tugas mata kuliah Struktur Data. Program-program di dalamnya berfokus pada implementasi struktur data fundamental (seperti *Linked List*, *Stack*, *Queue*, *Tree*, dan *Graph*) yang dibangun dari awal (*from scratch*) dengan mengutamakan efisiensi algoritma dan manajemen memori manual (mencegah *memory leak*).

---

**Daftar Modul dan Implementasi**

* **Fundamental C++**
  * `struct.cpp`: Implementasi dasar struktur data kustom menggunakan `struct`.
  * `pointer.cpp`: Penggunaan *pointer* tingkat lanjut dan dealokasi memori pada struktur *Binary Tree*.
  * `rekursif.cpp`: Operasi manipulasi dan pencarian pada *Linked List* menggunakan fungsi rekursif murni.

* **Struktur Data Linier (Linked List, Stack, Queue)**
  * `tugas2.cpp`: Implementasi *Circular Doubly Linked List* untuk sistem navigasi wilayah (maju, mundur, tambah, dan hapus *node* secara dinamis).
  * `tugas4.cpp`: Implementasi dasar *Stack* (LIFO) dan *Queue* (FIFO) berbasis *Linked List*.
  * `penggati_ets.cpp`: Algoritma konversi ekspresi matematika Infix ke Postfix sekaligus mesin kalkulator evaluasinya menggunakan *Stack*.
  * `aplikasibengkel.cpp`: Studi kasus manajemen antrean bengkel terpadu menggunakan *Queue* (untuk daftar tunggu) dan *Stack* (untuk kendaraan yang sedang diproses).

* **Struktur Data Non-Linier (Tree, Graph, & Map)**
  * `mapsederhana.cpp`: Konsep pergerakan arah 2D (Atas, Bawah, Kiri, Kanan) menggunakan Array 2D.
  * `tugas1.cpp`: Pengembangan peta 2D interaktif (Grid 3x3) menggunakan sistem *Linked List* dengan pencatatan riwayat jejak langkah.
  * `tugas3.cpp`: Implementasi *Adjacency List* untuk *Graph* tidak berarah beserta algoritma pencarian *Breadth-First Search* (BFS) untuk membentuk *Spanning Tree* berhierarki.
  * `graphtree.cpp`: Konversi bentuk *Graph* menjadi *Tree* menggunakan algoritma penelusuran *Depth-First Search* (DFS).

---

**Cara Menjalankan Program**

Pastikan *compiler* C++ (seperti MinGW/GCC) sudah terpasang. Kamu bisa mengompilasi dan menjalankan *file* secara individual melalui terminal:

1. Buka terminal/Command Prompt di dalam direktori repositori ini.
2. Lakukan kompilasi menggunakan perintah (contoh untuk `tugas1.cpp`):
```bash
g++ tugas1.cpp -o tugas1

```

3. Eksekusi program yang sudah dikompilasi:
* **Windows:** `.\tugas1.exe`
* **Linux/Mac:** `./tugas1`
