#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void buat_ulang_pin(){
    string pin_baru;
    cout << "masukan pin baru: ";
    cin >> pin_baru;

    ofstream filebuatpin("data_pin.txt");
    if (filebuatpin.is_open()) {
        filebuatpin << pin_baru;
        filebuatpin.close();
    }
}

bool cek_pin(){
    string pin_input;
    cout << "masukan pin: ";
    cin >> pin_input;

    ifstream filecekpin("data_pin.txt");
    string pin_tersimpan;
    if (filecekpin.is_open()) {
        filecekpin >> pin_tersimpan;
        filecekpin.close();
    }
    return pin_input == pin_tersimpan;
}

const int jumlah_hari = 30;
string data_tanggal[jumlah_hari];
long long data_saldo[jumlah_hari];
int jumlah_data = 0;

const string DATA_FILE = "data_tabungan.txt"; 

long long saldo_awal() {

    ifstream fileMasuk(DATA_FILE);
    long long saldo = 0;

    if (fileMasuk.is_open()) {
        fileMasuk >> saldo;
        fileMasuk.close();
    }

    return saldo;
}

void update_saldo(long long saldo_baru){
    if  (saldo_baru < 0){
        cout << "saldo tidak valid" << endl;
        return;
    }
    ofstream filekeluar(DATA_FILE);
    if (filekeluar.is_open()) {
        filekeluar << saldo_baru; 
        filekeluar.close();
        cout << "uang berhasil disimpan ke file." << endl;
        }else {
        cout << "Gagal menyimpan uang." << endl;
    }
}

void simpan_riwayat(string tanggal, long long jumlah_tabungan){
    
    if (jumlah_data < jumlah_hari){
        data_tanggal[jumlah_data] = tanggal;
        data_saldo[jumlah_data] = jumlah_tabungan;
        jumlah_data++;
        
        
    }
}

void tampilan_riwayat(){
    if (jumlah_data == 0){
        cout << "belum ada riwayat tabungan" << endl;
        return;
    }

    cout << "==============================" << endl;
    cout << "      RIWAYAT TABUNGAN       " << endl;
    cout << "==============================" << endl;
    for (int i = 0; i < jumlah_data; i++){
        cout << i + 1 << " Tanggal: " << data_tanggal[i] << " jumlah tabungan: " << data_saldo[i] << endl<< endl;
    }
}


int main(){
    int pilihan;
    bool pin_benar = false;
    int percobaan = 0;
    
    // Verifikasi PIN dengan maksimal 3 percobaan
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

    do{
        cout << "1, masukin tabungan" << endl;
        cout << "2. cek saldo" << endl;
        cout << "3. buat ulang pin" << endl;
        cout << "4. cek riwayat" << endl;
        cout << "5. keluar" << endl;
        cout << "pilih menu: ";

        cin >> pilihan;

        switch (pilihan){

            case 1: {

                cout << "==============================" << endl;
                cout << "      MASUKAN TABUNGAN       " << endl;
                cout << "==============================" << endl;

                if (jumlah_data > jumlah_hari){
        cout << "sudah melewati hari, data tidak dapat disimpan" << endl;
        return 0;
    }
                    long long saldo = saldo_awal();
                    cout << "masukan jumlah tabungan: ";
                    long long jumlah_tabungan;
                    cin >> jumlah_tabungan;
                    
                    if (jumlah_tabungan <= 0) {
                        cout << "Jumlah tabungan harus lebih dari 0!" << endl << endl;
                        break;
                    }
                    
                    saldo +=  jumlah_tabungan;
                    update_saldo(saldo);

                    cout << "masukan tanggal (hari/bulan/tahun): ";
                    string tanggal;
                    cin >> tanggal;
                    data_tanggal[jumlah_data] = tanggal;
                    data_saldo[jumlah_data] = jumlah_tabungan;
                    jumlah_data++;
            }
            break;

            case 2:{
                long long saldo_sekarang = saldo_awal();
                cout << "==============================" << endl;
                cout << "        CEK SALDO           " << endl; 
                cout << "==============================" << endl;
                cout << "Saldo saat Ini: "<<saldo_sekarang << endl<< endl;
            }
                break;
        
            case 3:{
                buat_ulang_pin();
            }
                break;
            
            case 4:{
                tampilan_riwayat();
            }
                break;
            case 5:{
                cout << "keluar program" << endl;
                return 0;
            }
                break;
            default:{
                cout << endl;
                cout << "==============================" << endl;
                cout << "       PERINGATAN!!!        " << endl;
                cout << "   pilihan tidak valid!!!"  << endl;
                cout << "==============================" << endl<< endl;
            }
                break;
        }
            

    } while (pilihan != 5);
    
    return 0;
}