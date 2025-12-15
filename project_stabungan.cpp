#include <iostream>
#include <fstream>

using namespace std;

void buat_ulang_pin()
{
    string pin_baru;
    cout << "masukan pin baru: ";
    cin >> pin_baru;

    ofstream filebuatpin("data_pin.txt");
        filebuatpin << pin_baru;
     
}

bool cek_pin()
{
    string pin_input;
    cout << "masukan pin: ";    
    cin >> pin_input;

    ifstream filecekpin("data_pin.txt");
    string pin_tersimpan;
        filecekpin >> pin_tersimpan;
    

   return pin_input == pin_tersimpan;
}

const int data_transaksi = 30;
string data_tanggal[data_transaksi];
long long data_saldo[data_transaksi];
int jumlah_data = 0;

const string DATA_FILE = "data_tabungan.txt";

long long saldo_awal()
{

    ifstream fileMasuk(DATA_FILE);
    long long saldo = 0;

        fileMasuk >> saldo;

    return saldo;
}

void update_saldo(long long saldo_baru)
{

    ofstream filekeluar(DATA_FILE);
    if (filekeluar.is_open())
    {
        filekeluar << saldo_baru;
        filekeluar.close();
        cout << "Data uang berhasil disimpan." << endl;
    }
    else
    {
        cout << "Gagal menyimpan uang." << endl;
    }
}

void cek_saldo(){

    long long saldo_sekarang = saldo_awal();
    cout << "==============================" << endl;
    cout << "        CEK SALDO           " << endl;
    cout << "==============================" << endl;
    cout << "Saldo saat Ini: " << saldo_sekarang << endl 
     << endl;
}

void simpan_riwayat(string tanggal, long long jumlah_tabungan)
{

    if (jumlah_data < data_transaksi)
    {
        data_tanggal[jumlah_data] = tanggal;
        data_saldo[jumlah_data] = jumlah_tabungan;
        jumlah_data++;
    }
}

void tampilan_riwayat()
{
    if (jumlah_data == 0)
    {
        cout << "belum ada riwayat tabungan" << endl;
        return;
    }

    cout << "==============================" << endl;
    cout << "      RIWAYAT TABUNGAN       " << endl;
    cout << "==============================" << endl;
    for (int i = 0; i < jumlah_data; i++)
    {
        cout << i + 1 << " Tanggal: " << data_tanggal[i] << " jumlah tabungan: " << data_saldo[i] << endl
             << endl;
    }
}

string masukin_tanggal(){
    cout << "masukan tanggal (hari/bulan/tahun): ";
            string tanggal;
            cin.ignore();

            
            getline(cin, tanggal);
            return tanggal;
}

void setor_tabungan(){

    long long saldo=saldo_awal();
    long long jumlah_masuk;
    
    cout << "Masukan jumlah tabungan: ";
    cin >> jumlah_masuk;

    saldo += jumlah_masuk;
    update_saldo(saldo);
    string tanggal = masukin_tanggal();

    simpan_riwayat(tanggal,jumlah_masuk);

}

void penarikan(){

    long long saldo = saldo_awal();
    long long jumlah_saldo ;

    cout << "Masukan jumlah penarikan";
    cin >> jumlah_saldo;

    if (jumlah_saldo > saldo){
        cout << "Saldo tidak mencukupi!!!";
        return;
    }
    
    saldo -= jumlah_saldo;
    update_saldo(saldo);
    
    string tanggal = masukin_tanggal();
    simpan_riwayat(tanggal, -jumlah_saldo);
    

}

void pilihan_tidak_valid(){
    cout << endl;
            cout << "==============================" << endl;
            cout << "       PERINGATAN!!!        " << endl;
            cout << "   pilihan tidak valid!!!" << endl;
            cout << "==============================" << endl
                 << endl;
}



int main()
{
     int pilihan;
    bool pin_benar = false;
    int percobaan = 0;
    
    
    while (!pin_benar && percobaan < 3) {
        if (cek_pin()) {
            pin_benar = true;
            cout << "Login berhasil!" << endl << endl;
        } else {
            percobaan++;
            cout << "PIN salah! Sisa percobaan: " << (3 - percobaan) << endl << endl;
        }
    }
    
    if (!pin_benar){
        cout << "Anda telah melebihi batas percobaan login!" << endl;
        return 0;
    }

    do
    {
        cout << "1. Masukin tabungan" << endl;
        cout << "2. Cek saldo" << endl;
        cout << "3. Buat ulang pin" << endl;
        cout << "4. Cek riwayat" << endl;
        cout << "5. Penarikan" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilih menu: ";

        
        cin >> pilihan;

        switch (pilihan)
        {

        case 1:
        {
            setor_tabungan();
        }
        break;

        case 2:
        {
            cek_saldo();
        }
        break;

        case 3:
        {
            buat_ulang_pin();
        }
        break;

        case 4:
        {
            tampilan_riwayat();
        }
        break;
        case 5:
        {
             penarikan();
        }
        break;
        case 6:{
            cout << "Anda telah keluar program";
        }
        break;
        default:
        {
           pilihan_tidak_valid();
        }
        }

    } while (pilihan != 6 );

    return 0;
}
