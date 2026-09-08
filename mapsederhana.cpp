#include <iostream>
#include <cctype>
using namespace std;

struct Node
{
    char data;
    Node *up;
    Node *down;
    Node *left;
    Node *right;
};

Node *buatNode(char nilai)
{
    Node *baru = new Node;
    baru->data = nilai;
    baru->up = nullptr;
    baru->down = nullptr;
    baru->left = nullptr;
    baru->right = nullptr;
    return baru;
}

Node *buatMap()
{
    Node *grid[3][3];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            grid[i][j] = buatNode('.');
        }
    }

    // Titik keluar di pojok kanan bawah
    grid[2][2]->data = 'X';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i > 0)
                grid[i][j]->up = grid[i - 1][j];
            if (i < 2)
                grid[i][j]->down = grid[i + 1][j];
            if (j > 0)
                grid[i][j]->left = grid[i][j - 1];
            if (j < 2)
                grid[i][j]->right = grid[i][j + 1];
        }
    }

    return grid[1][1];
}

void tampilMap(Node *start)
{
    Node *baris = start;

    // Cari titik ujung kiri atas yang sesungguhnya
    while (baris->up != nullptr)
        baris = baris->up;
    while (baris->left != nullptr)
        baris = baris->left;

    Node *currBaris = baris;
    while (currBaris != nullptr)
    {
        Node *curr = currBaris;
        while (curr != nullptr)
        {
            cout << curr->data << " ";
            curr = curr->right;
        }
        cout << endl;
        currBaris = currBaris->down;
    }
}

// Dealokasi pointer untuk menghindari memory leak
void hapusMap(Node *start)
{
    Node *baris = start;
    while (baris->up != nullptr)
        baris = baris->up;
    while (baris->left != nullptr)
        baris = baris->left;

    Node *currBaris = baris;
    while (currBaris != nullptr)
    {
        Node *nextBaris = currBaris->down;
        Node *curr = currBaris;
        while (curr != nullptr)
        {
            Node *nextNode = curr->right;
            delete curr;
            curr = nextNode;
        }
        currBaris = nextBaris;
    }
}

void pindah(Node *&pemain, char arah)
{
    Node *tujuan = nullptr;
    arah = tolower(arah); // Mengatasi input huruf besar

    if (arah == 'w')
        tujuan = pemain->up;
    else if (arah == 's')
        tujuan = pemain->down;
    else if (arah == 'a')
        tujuan = pemain->left;
    else if (arah == 'd')
        tujuan = pemain->right;

    if (tujuan != nullptr)
    {
        pemain->data = '.';
        pemain = tujuan;

        // Mengecek kondisi berhasil
        if (pemain->data == 'X')
        {
            cout << "\nSelamat! Kamu menemukan titik keluar (X)!\n";
        }
        pemain->data = 'P';
    }
    else
    {
        // Notifikasi tabrakan batas grid
        cout << "\nMentok! Kamu menabrak dinding batas.\n";
    }
}

int main()
{
    Node *pemain = buatMap();
    pemain->data = 'P';

    char input;
    do
    {
        // Clear screen aman secara cross-platform
        system("cls || clear");
        tampilMap(pemain);

        cout << "\nGerak (w/a/s/d), q untuk keluar: ";
        cin >> input;

        if (tolower(input) != 'q')
        {
            pindah(pemain, input);
        }

    } while (tolower(input) != 'q');

    hapusMap(pemain);
    return 0;
}