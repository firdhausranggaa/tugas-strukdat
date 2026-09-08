#include <iostream>
#include <string> // Perbaikan: String mutlak diperlukan, bawaan malah memakai <stdio.h>
using namespace std;

// Struktur Node Graf
typedef struct Node
{
    string data;
    struct Edge *linkTo;
    struct Node *next;
    bool visited;
} Node;

// Struktur Edge (Garis/Sisi) Graf
typedef struct Edge
{
    Node *tujuan;
    struct Edge *next;
} Edge;

// Struktur Node Tree
typedef struct NodeTree
{
    string data;
    struct NodeTree *parent;
    struct EdgeTree *linkTo;
} NodeTree;

// Struktur Edge Tree
typedef struct EdgeTree
{
    NodeTree *tujuan;
    struct EdgeTree *next;
} EdgeTree;

// Deklarasi fungsi
NodeTree *treeGenerate(Node *head);
void treeAddChild(NodeTree *parent, Node *childNode);
void resetVisited(Node *head);
void printTree(NodeTree *root, string prefix, bool isLast);
void printAdj(Node *head);

// Pengembangan: Deklarasi fungsi pembersih memori
void freeGraph(Node *head);
void freeTree(NodeTree *root);

int main()
{
    // Inisialisasi Node Graf manual
    Node *nodeA = new Node();
    nodeA->data = "A";
    Node *nodeB = new Node();
    nodeB->data = "B";
    Node *nodeC = new Node();
    nodeC->data = "C";
    Node *nodeD = new Node();
    nodeD->data = "D";
    Node *nodeE = new Node();
    nodeE->data = "E";
    Node *nodeF = new Node();
    nodeF->data = "F";

    // Merangkai Node (Linked List utama Graf)
    Node *head = nodeA;
    nodeA->next = nodeB;
    nodeB->next = nodeC;
    nodeC->next = nodeD;
    nodeD->next = nodeE;
    nodeE->next = nodeF;
    nodeF->next = nullptr;

    // Relasi Adjacency (Edge) Node A
    nodeA->linkTo = new Edge();
    nodeA->linkTo->tujuan = nodeB;
    nodeA->linkTo->next = new Edge();
    nodeA->linkTo->next->tujuan = nodeC;
    nodeA->linkTo->next->next = nullptr;

    // Relasi Adjacency (Edge) Node B
    nodeB->linkTo = new Edge();
    nodeB->linkTo->tujuan = nodeD;
    nodeB->linkTo->next = new Edge();
    nodeB->linkTo->next->tujuan = nodeE;
    nodeB->linkTo->next->next = new Edge();
    nodeB->linkTo->next->next->tujuan = nodeC;
    nodeB->linkTo->next->next->next = nullptr;

    // Relasi Adjacency (Edge) Node C
    nodeC->linkTo = new Edge();
    nodeC->linkTo->tujuan = nodeD;
    nodeC->linkTo->next = new Edge();
    nodeC->linkTo->next->tujuan = nodeE;
    nodeC->linkTo->next->next = nullptr;

    // Relasi Adjacency (Edge) Node D
    nodeD->linkTo = new Edge();
    nodeD->linkTo->tujuan = nodeF;
    nodeD->linkTo->next = new Edge();
    nodeD->linkTo->next->tujuan = nodeE;
    nodeD->linkTo->next->next = nullptr;

    // Relasi Adjacency (Edge) Node E
    nodeE->linkTo = new Edge();
    nodeE->linkTo->tujuan = nodeF;
    nodeE->linkTo->next = nullptr;

    // Relasi Adjacency (Edge) Node F
    nodeF->linkTo = nullptr;

    cout << "=== Adjacency List (Graph) ===\n";
    printAdj(head);

    resetVisited(head);
    NodeTree *root = treeGenerate(nodeA);

    cout << "\n=== Tree (DFS dari A) ===\n";
    printTree(root, "", true);

    // Pengembangan: Membersihkan objek yang melayang di heap memory
    freeTree(root);
    freeGraph(head);

    return 0;
}

// Reset flag visited graf untuk penjelajahan
void resetVisited(Node *head)
{
    for (Node *p = head; p != nullptr; p = p->next)
        p->visited = false;
}

// Membangun DFS Spanning Tree dari Root
NodeTree *treeGenerate(Node *head)
{
    if (!head)
        return nullptr;

    head->visited = true; // Tandai sudah dikunjungi

    NodeTree *root = new NodeTree(); // Alokasi Root Tree
    root->data = head->data;
    root->parent = nullptr;
    root->linkTo = nullptr;

    // DFS rekursif ke tetangga node graf
    for (Edge *temp = head->linkTo; temp != nullptr; temp = temp->next)
    {
        if (!temp->tujuan->visited)
        {
            treeAddChild(root, temp->tujuan); // Jadikan child
        }
    }
    return root;
}

// Menambahkan anak ke dalam tree dan lanjut DFS
void treeAddChild(NodeTree *parent, Node *childNode)
{
    if (!parent || !childNode || childNode->visited)
        return;

    childNode->visited = true; // Tandai dikunjungi

    NodeTree *thisNode = new NodeTree(); // Alokasi Tree Node baru
    thisNode->data = childNode->data;
    thisNode->parent = parent;
    thisNode->linkTo = nullptr;

    EdgeTree *e = new EdgeTree(); // Alokasi relasi Edge Tree
    e->tujuan = thisNode;
    e->next = nullptr;

    // Masukkan Edge Tree ke daftar anak Parent
    if (parent->linkTo == nullptr)
    {
        parent->linkTo = e;
    }
    else
    {
        EdgeTree *p = parent->linkTo;
        while (p->next)
            p = p->next;
        p->next = e;
    }

    // Teruskan DFS
    for (Edge *temp = childNode->linkTo; temp != nullptr; temp = temp->next)
    {
        if (!temp->tujuan->visited)
        {
            treeAddChild(thisNode, temp->tujuan);
        }
    }
}

// Mencetak visualisasi Tree
void printTree(NodeTree *root, string prefix, bool isLast)
{
    if (!root)
        return;

    cout << prefix << "+- ";

    bool leaf = (root->linkTo == nullptr);
    if (root->parent == nullptr)
    {
        if (leaf)
            cout << root->data << " (root, end leaf)\n";
        else
            cout << root->data << " (root)\n";
    }
    else
    {
        if (leaf)
            cout << root->data << " (parent: " << root->parent->data << ", child, end leaf)\n";
        else
            cout << root->data << " (parent: " << root->parent->data << ", child)\n";
    }

    string newPrefix = prefix + (isLast ? "   " : "|  ");
    int cnt = 0;
    for (EdgeTree *e = root->linkTo; e; e = e->next)
        cnt++;

    int i = 0;
    for (EdgeTree *e = root->linkTo; e; e = e->next)
    {
        ++i;
        printTree(e->tujuan, newPrefix, i == cnt);
    }
}

// Mencetak Adjacency List (Graf)
void printAdj(Node *head)
{
    for (Node *p = head; p != nullptr; p = p->next)
    {
        cout << p->data << " terhubung ke: ";
        if (p->linkTo == nullptr)
        {
            cout << "(tidak ada tetangga)";
        }
        else
        {
            for (Edge *e = p->linkTo; e != nullptr; e = e->next)
            {
                cout << e->tujuan->data;
                if (e->next)
                    cout << " -> ";
            }
        }
        cout << "\n";
    }
}

// Pengembangan: Dealokasi Memory Graph
void freeGraph(Node *head)
{
    while (head != nullptr)
    {
        // Hapus semua Edge pada Node tersebut
        Edge *currEdge = head->linkTo;
        while (currEdge != nullptr)
        {
            Edge *tmpE = currEdge;
            currEdge = currEdge->next;
            delete tmpE;
        }
        // Hapus Node itu sendiri
        Node *tmpN = head;
        head = head->next;
        delete tmpN;
    }
}

// Pengembangan: Dealokasi Memory Tree (DFS Post-order Deletion)
void freeTree(NodeTree *root)
{
    if (root == nullptr)
        return;

    // Hapus anak-anaknya dulu beserta sisi relasinya
    EdgeTree *currEdge = root->linkTo;
    while (currEdge != nullptr)
    {
        EdgeTree *tmpE = currEdge;
        freeTree(currEdge->tujuan); // Hapus Subtree tujuan rekursif
        currEdge = currEdge->next;
        delete tmpE; // Hapus sisi
    }
    delete root; // Hapus parent
}