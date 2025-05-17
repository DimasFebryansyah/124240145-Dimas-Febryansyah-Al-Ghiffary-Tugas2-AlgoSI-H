#include <iostream>
#include <string>

using namespace std;

// Struktur node untuk menyimpan data pasien dalam antrian
struct Node
{
    int nomorAntrian;
    string namaPasien;
    string keluhan;
    Node *prev;
    Node *next;
};

// Fungsi untuk menambahkan pasien dengan nomor antrian secara terurut
// Menggunakan doubly linked list agar data tetap terurut berdasarkan nomor antrian
void tambahPasien(Node *&head, Node *&tail, int nomor, string nama, string keluhan)
{
    Node *newNode = new Node{nomor, nama, keluhan, nullptr, nullptr};

    // Jika antrian masih kosong
    if (!head)
    {
        head = tail = newNode;
        return;
    }

    // Mencari posisi yang tepat untuk menyisipkan pasien baru secara terurut
    Node *temp = head;
    while (temp && temp->nomorAntrian < nomor)
        temp = temp->next;

    // Menambahkan pasien di akhir antrian jika nomor terbesar
    if (!temp)
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    else
    {
        // Menyisipkan pasien di tengah atau awal antrian
        newNode->next = temp;
        newNode->prev = temp->prev;
        if (temp->prev)
            temp->prev->next = newNode;
        else
            head = newNode;
        temp->prev = newNode;
    }
}

// Fungsi untuk menampilkan antrian pasien dari awal ke akhir
void tampilkanDepan(Node *head)
{
    if (!head)
    {
        cout << "\n===================================\n";
        cout << "|         Antrian Kosong!         |\n";
        cout << "===================================\n";
        return;
    }

    cout << "\n====================================\n";
    cout << "|       Daftar Antrian (Dari Awal)  |\n";
    cout << "====================================\n";

    // Menampilkan setiap pasien dari awal ke akhir
    Node *temp = head;
    while (temp)
    {
        cout << "------------------------------------\n";
        cout << " No Antrian   : " << temp->nomorAntrian << endl;
        cout << " Nama         : " << temp->namaPasien << endl;
        cout << " Keluhan      : " << temp->keluhan << endl;
        temp = temp->next;
    }
    cout << "====================================\n";
}

// Fungsi untuk menampilkan antrian pasien dari akhir ke awal
void tampilkanBelakang(Node *tail)
{
    if (!tail)
    {
        cout << "\n===================================\n";
        cout << "|         Antrian Kosong!         |\n";
        cout << "===================================\n";
        return;
    }

    cout << "\n====================================\n";
    cout << "|    Daftar Antrian (Dari Akhir)   |\n";
    cout << "====================================\n";

    // Menampilkan setiap pasien dari akhir ke awal
    Node *temp = tail;
    while (temp)
    {
        cout << "------------------------------------\n";
        cout << " No Antrian   : " << temp->nomorAntrian << endl;
        cout << " Nama         : " << temp->namaPasien << endl;
        cout << " Keluhan      : " << temp->keluhan << endl;
        temp = temp->prev;
    }
    cout << "====================================\n";
}

// Fungsi untuk mencari pasien berdasarkan nomor antrian
void cariPasien(Node *head, int nomor)
{
    Node *temp = head;

    // Mencari pasien berdasarkan nomor antrian
    while (temp)
    {
        if (temp->nomorAntrian == nomor)
        {
            cout << "\n===================================\n";
            cout << "|         Pasien Ditemukan        |\n";
            cout << "===================================\n";
            cout << " No Antrian   : " << temp->nomorAntrian << endl;
            cout << " Nama         : " << temp->namaPasien << endl;
            cout << " Keluhan      : " << temp->keluhan << endl;
            cout << "-----------------------------------\n";
            return;
        }
        temp = temp->next;
    }

    cout << "\n===================================\n";
    cout << "|      Pasien Tidak Ditemukan      |\n";
    cout << "===================================\n";
}

// Fungsi untuk menghapus pasien berdasarkan nomor antrian
void hapusPasien(Node *&head, Node *&tail, int nomor)
{
    Node *temp = head;

    // Mencari pasien dengan nomor antrian yang sesuai
    while (temp && temp->nomorAntrian != nomor)
        temp = temp->next;

    // Jika pasien tidak ditemukan
    if (!temp)
    {
        cout << "\n===================================\n";
        cout << "|      Pasien Tidak Ditemukan      |\n";
        cout << "===================================\n";
        return;
    }

    // Menampilkan informasi pasien sebelum dihapus
    cout << "\n===================================\n";
    cout << "|     Pasien Berhasil Dihapus      |\n";
    cout << "===================================\n";
    cout << " No Antrian   : " << temp->nomorAntrian << endl;
    cout << " Nama         : " << temp->namaPasien << endl;
    cout << " Keluhan      : " << temp->keluhan << endl;
    cout << "-----------------------------------\n";

    // Menghapus node dari linked list
    if (temp->prev)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next)
        temp->next->prev = temp->prev;
    else
        tail = temp->prev;

    delete temp;
}

// Fungsi utama untuk menjalankan program dan interaksi dengan pengguna
int main()
{
    Node *head = nullptr;
    Node *tail = nullptr;
    int pilihan, nomor;
    string nama, keluhan;

    do
    {
        cout << "\n=== Menu Antrian Pasien Klinik ===\n";
        cout << "1. Tambah Pasien\n";
        cout << "2. Tampilkan Antrian dari Awal\n";
        cout << "3. Tampilkan Antrian dari Akhir\n";
        cout << "4. Cari Pasien\n";
        cout << "5. Hapus Pasien\n";
        cout << "6. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            cout << "Masukkan Nomor Antrian: ";
            cin >> nomor;
            cin.ignore();
            cout << "Masukkan Nama Pasien: ";
            getline(cin, nama);
            cout << "Masukkan Keluhan: ";
            getline(cin, keluhan);
            tambahPasien(head, tail, nomor, nama, keluhan);
            cout << "Pasien berhasil ditambahkan!\n";
            break;
        case 2:
            tampilkanDepan(head);
            break;
        case 3:
            tampilkanBelakang(tail);
            break;
        case 4:
            cout << "Masukkan Nomor Antrian yang Dicari: ";
            cin >> nomor;
            cariPasien(head, nomor);
            break;
        case 5:
            cout << "Masukkan Nomor Antrian yang Akan Dihapus: ";
            cin >> nomor;
            hapusPasien(head, tail, nomor);
            break;
        case 6:
            cout << "Terima kasih!\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 6);

    return 0;
}