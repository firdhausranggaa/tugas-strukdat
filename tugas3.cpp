#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Fungsi rekursif untuk mencetak Tree secara visual
void printTreeVisual(int node, string prefix, bool isLast, const vector<vector<int>> &children)
{
    // Cetak prefix awal (kosong jika root) lalu garis cabang
    cout << prefix;
    cout << (isLast ? "└── " : "├── ");
    cout << node << "\n"; // Cetak ID Node

    // Hitung jumlah anak dari node ini
    int childCount = children[node].size();

    // Iterasi untuk mencetak anak-anaknya secara rekursif
    for (int i = 0; i < childCount; i++)
    {
        // Jika ini adalah anak terakhir, cabang selanjutnya pakai spasi kosong, jika bukan pakai garis lurus "|"
        string newPrefix = prefix + (isLast ? "    " : "│   ");
        printTreeVisual(children[node][i], newPrefix, (i == childCount - 1), children);
    }
}

int main()
{
    int n, m;
    cout << "Jumlah node (n): ";
    cin >> n;
    cout << "Jumlah edge (m): ";
    cin >> m;

    vector<vector<int>> adj(n); // Adjacency list untuk graf

    cout << "Masukkan edge u v (0..n-1), graph tak berarah:\n";
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        // Validasi input agar tidak out of bounds
        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            cout << "Edge tidak valid.\n";
            return 0;
        }

        // Simpan koneksi dua arah (undirected graph)
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root;
    cout << "Root tree (0..n-1): ";
    cin >> root;

    // Validasi input root
    if (root < 0 || root >= n)
    {
        cout << "Root tidak valid.\n";
        return 0;
    }

    vector<int> parent(n, -1); // Array penyimpan parent node
    vector<int> depth(n, -1);  // Array penanda kedalaman node (-1 berarti belum dikunjungi)
    queue<int> q;              // Queue pembantu algoritma BFS

    // Pengembangan: Array adjacency 1-arah khusus Tree untuk keperluan visual
    vector<vector<int>> treeChildren(n);

    // Inisialisasi BFS dari Root
    depth[root] = 0;
    q.push(root);

    while (!q.empty())
    {
        int u = q.front(); // Ambil elemen terdepan dari queue
        q.pop();           // Hapus dari queue

        // Telusuri semua tetangga graf dari node u
        for (int v : adj[u])
        {
            if (depth[v] == -1)
            {                                 // Jika tetangga belum pernah dikunjungi
                parent[v] = u;                // Catat u sebagai parent dari v
                depth[v] = depth[u] + 1;      // Kedalaman bertambah 1
                treeChildren[u].push_back(v); // Catat v sebagai child dari u di dalam Tree
                q.push(v);                    // Masukkan v ke queue untuk di-explore
            }
        }
    }

    cout << "\n=== Hasil Tree (Spanning Tree BFS) ===\n";

    // Tampilkan graf hierarki mulai dari root (memanggil rekursif visual tree)
    cout << root << " (Root)\n";
    for (size_t i = 0; i < treeChildren[root].size(); i++)
    {
        printTreeVisual(treeChildren[root][i], "", (i == treeChildren[root].size() - 1), treeChildren);
    }

    // Pengecekan Graph Terputus (Disconnected Graph)
    bool adaTerputus = false;
    for (int i = 0; i < n; i++)
    {
        if (depth[i] == -1)
        { // Jika depth tetap -1 setelah BFS, berarti node terisolasi
            adaTerputus = true;
            break;
        }
    }

    if (adaTerputus)
    {
        cout << "\n[Catatan]: Ada node yang tidak terhubung dari root dan tidak masuk dalam spanning tree.\n";
    }

    return 0;
}