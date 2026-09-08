#include <iostream>
using namespace std;

// Struktur node untuk Binary Tree
struct TreeNode
{
    int data;        // Menyimpan nilai node
    TreeNode *left;  // Pointer ke anak kiri
    TreeNode *right; // Pointer ke anak kanan
};

// Fungsi membuat node baru
TreeNode *buatNode(int nilai)
{
    TreeNode *baru = new TreeNode; // Alokasi memori dinamis
    baru->data = nilai;
    baru->left = nullptr; // Perbaikan: Gunakan nullptr alih-alih NULL
    baru->right = nullptr;
    return baru;
}

// Penelusuran Inorder (Kiri, Root, Kanan)
void inorder(TreeNode *root)
{
    if (root == nullptr)
        return;                // Basis rekursi
    inorder(root->left);       // Ke kiri
    cout << root->data << " "; // Cetak root
    inorder(root->right);      // Ke kanan
}

// Pengembangan: Penelusuran Preorder (Root, Kiri, Kanan)
void preorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Pengembangan: Penelusuran Postorder (Kiri, Kanan, Root)
void postorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Pengembangan: Fungsi dealokasi seluruh Tree (mencegah Memory Leak)
void hapusTree(TreeNode *root)
{
    if (root == nullptr)
        return;
    hapusTree(root->left);  // Hapus anak kiri dulu
    hapusTree(root->right); // Hapus anak kanan
    delete root;            // Hapus root
}

int main()
{
    // Membangun Tree
    TreeNode *root = buatNode(1);
    root->left = buatNode(2);
    root->right = buatNode(3);
    root->left->left = buatNode(4);
    root->left->right = buatNode(5);

    cout << "Inorder Traversal   : ";
    inorder(root);
    cout << "\nPreorder Traversal  : ";
    preorder(root);
    cout << "\nPostorder Traversal : ";
    postorder(root);
    cout << endl;

    // Bersihkan RAM sebelum keluar
    hapusTree(root);

    return 0;
}