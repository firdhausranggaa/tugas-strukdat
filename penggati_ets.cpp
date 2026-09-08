#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <cctype>
using namespace std;

// Fungsi untuk menentukan prioritas operator matematika
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1; // Prioritas pertama
    if (op == '*' || op == '/')
        return 2; // Prioritas kedua (lebih tinggi)
    return 0;     // Jika bukan operator, prioritas 0
}

// Fungsi untuk mengubah ekspresi Infix ke Postfix
vector<string> infixToPostfix(const vector<string> &tokens)
{
    stack<char> st;        // Stack untuk menyimpan operator
    vector<string> output; // Menghasilkan hasil akhir dalam bentuk postfix

    for (const string &t : tokens)
    {
        // Dukungan untuk angka multi-digit
        if (isdigit(t[0]) || (t.length() > 1 && t[0] == '-' && isdigit(t[1])))
        {
            output.push_back(t); // Langsung memasukkan ke output
        }
        else if (t == "(")
        {                 // Jika token adalah kurung buka
            st.push('('); // Push '(' ke stack
        }
        else if (t == ")")
        { // Jika token adalah kurung tutup
            // Mengeluarkan operator dari stack sampai ketemu '('
            while (!st.empty() && st.top() != '(')
            {
                output.push_back(string(1, st.top())); // Memasukkan ke output
                st.pop();                              // Menghapus dari stack
            }
            if (!st.empty())
                st.pop(); // Buang '(' dari stack
        }
        else
        { // Jika token adalah operator
            char op = t[0];
            // Mengeluarkan operator dari stack selama prioritas lebih tinggi atau sama
            while (!st.empty() && precedence(st.top()) >= precedence(op))
            {
                output.push_back(string(1, st.top())); // Memindahkan ke output
                st.pop();
            }
            st.push(op); // Push operator baru ke stack
        }
    }

    // Jika masih ada operator tersisa di stack, mengeluarkan semua
    while (!st.empty())
    {
        output.push_back(string(1, st.top()));
        st.pop();
    }

    return output; // Mengembalikan vektor hasil postfix
}

// Mengubah tipe kembalian agar bisa menandakan error
void evalPostfix(const vector<string> &postfix)
{
    stack<int> st; // Stack untuk menyimpan angka selama evaluasi

    for (const string &t : postfix)
    {
        if (isdigit(t[0]) || (t.length() > 1 && t[0] == '-' && isdigit(t[1])))
        {                     // Jika token angka
            st.push(stoi(t)); // Mengubah string ke int, dan menyimpan ke stack
        }
        else
        {
            // Validasi cegah Segmentation Fault
            if (st.size() < 2)
            {
                cout << "Error: Ekspresi tidak valid (kekurangan operand)!\n";
                return;
            }

            int b = st.top();
            st.pop(); // Mengambil angka terakhir (operand kanan)
            int a = st.top();
            st.pop();       // Mengambil angka sebelumnya (operand kiri)
            char op = t[0]; // Mengambil operator
            int res = 0;    // Variabel untuk hasil

            if (op == '+')
                res = a + b;
            else if (op == '-')
                res = a - b;
            else if (op == '*')
                res = a * b;
            else if (op == '/')
            {
                // Mencegah pembagian dengan nol
                if (b == 0)
                {
                    cout << "Error: Pembagian dengan nol terdeteksi!\n";
                    return;
                }
                res = a / b;
            }

            st.push(res); // Menyimpan hasil kembali ke stack
        }
    }

    if (st.size() == 1)
    {
        cout << "Hasil: " << st.top() << endl;
    }
    else
    {
        cout << "Error: Ekspresi tidak seimbang (kelebihan operand)!\n";
    }
}

int main()
{
    cout << "Input ekspresi (pisahkan angka dan operator dengan spasi): ";
    string line;        // Variabel untuk input baris penuh
    getline(cin, line); // Membaca seluruh ekspresi (harus ada spasi)

    // Memecah string input menjadi token menggunakan stringstream
    stringstream ss(line); // Membuat stringstream dari input
    vector<string> tokens; // Menampung token hasil pecahan
    string tok;            // Variabel sementara untuk token

    while (ss >> tok)
    {
        tokens.push_back(tok); // Baca token satu per satu
    }

    if (tokens.empty())
    {
        cout << "Input kosong." << endl; // Menangani kasus input kosong
        return 0;
    }

    // Konversi dari Infix ke Postfix
    vector<string> postfix = infixToPostfix(tokens);

    // Menampilkan Postfix
    cout << "Postfix: ";
    for (auto &s : postfix)
    {
        cout << s << " ";
    }
    cout << endl;

    // Menghitung hasil Postfix dan menampilkan
    evalPostfix(postfix);

    return 0; // Selesai, keluar dari program
}