#include <iostream>
using namespace std;

struct nodeQueue {
    int organ;
    string nama;
    nodeQueue* next;
};

struct nodeStack {
    int organ;
    string nama;
    nodeStack* next;
};

struct nodeTree {
    int organ;
    string nama;
    nodeTree* kiri;
    nodeTree* kanan;
};

nodeQueue* front = nullptr;
nodeQueue* last = nullptr;
nodeStack* top = nullptr;
nodeTree* root = nullptr;

nodeTree* tambah_tree (nodeTree* akar, int organ, string nama){
    if (akar == nullptr){
        return new nodeTree {organ, nama, nullptr, nullptr};
    }
    if (organ < akar->organ) {
        akar->kiri = tambah_tree(akar->kiri, organ, nama);
    }else {
        akar->kanan = tambah_tree(akar->kanan, organ, nama);
    }
    return akar;
}

nodeTree* cari_tree(nodeTree* akar, int organ){
    if (akar == nullptr || organ == akar->organ) {
        return akar;
    }
    if  (organ < akar->organ) {
        return cari_tree(akar->kiri, organ);
    }
    return cari_tree(akar->kanan, organ);
}

nodeTree* hapus_tree(nodeTree* akar, int organ) {
    if (akar == nullptr){
        return nullptr;
    }
    if (organ < akar->organ) {
        akar->kiri = hapus_tree(akar->kiri, organ);
    }else if (organ > akar->organ){
        akar->kanan = hapus_tree(akar->kanan, organ);
    }else if (akar->kiri == nullptr){
        nodeTree* sisa = akar->kanan;
        delete akar;
        return sisa;
    }else if (akar->kanan == nullptr){
        nodeTree* sisa = akar->kiri;
        delete akar;
        return sisa;
    } else {
        nodeTree* pengganti = akar->kanan;
        while (pengganti->kiri != nullptr){
            pengganti = pengganti->kiri;
        }
        akar->organ = pengganti->organ;
        akar->nama = pengganti->nama;
        akar->kanan = hapus_tree(akar->kanan, pengganti->organ);
    }
    return akar;
}

void preorder(nodeTree* akar, int& no){
    if (akar == nullptr)
        return;
    cout << no << ". [" << akar->organ << "] " << akar->nama << endl;
    no++;
    preorder(akar->kiri, no);
    preorder(akar->kanan, no);
}

void inorder(nodeTree* akar, int& no){
    if (akar == nullptr)
        return;
    inorder(akar->kiri, no);
    cout << no << ". [" << akar->organ << "] " << akar->nama << endl;
    no++;
    inorder(akar->kanan, no);
}

void postorder(nodeTree* akar, int& no){
    if (akar == nullptr)
        return;
    postorder(akar->kiri, no);
    postorder(akar->kanan, no);
    cout << no << ". [" << akar->organ << "] " << akar->nama << endl;
    no++;
}

void tambah_energi(){
    int organ;
    string nama;
    cout << "Masukkan Kode Energi: ";
    cin >> organ;
    if (cin.fail() || organ <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode Enegi Harus Angka Lebih dari 0!" << endl;
        return;
    }
    nodeQueue* q = front;
    while (q != nullptr) {
        if(q->organ == organ){
            cout << "Kode Energi Sudah Ada!" << endl;
            return;
        }
        q = q->next;
    }
    nodeStack* s = top;
    while (s != nullptr) {
        if(s->organ == organ){
            cout << "Kode Energi Sudah Ada!" << endl;
            return;
        }
        s = s->next;
    }
    cout << "Masukkan Nama Energi: ";
    cin.ignore();
    getline (cin, nama);
    if (nama.empty()){
        cout << "Nama Energi Tidak Boleh Kosong!" << endl;
        return;
    }
    nodeQueue* bantu = new nodeQueue {organ, nama, nullptr};
    if (front == nullptr){
        front = last = bantu;
    } else {
        last->next = bantu;
        last = bantu;
    }
    cout << "Berhasil Memasukkan Energi" << endl;
}

void lihat_antrean(){
    if (front == nullptr){
        cout << "Antrean Masih Kosong" << endl;
        return;
    }
    nodeQueue* bantu = front;
    int no = 1;
    cout << "=== Energi dalam Antrean ===" << endl;
    while (bantu != nullptr){
        no++;
        cout << no << ". [" << bantu->organ << "] "<< bantu->nama << endl;
        bantu = bantu->next;
    }
    cout << endl;
}

void proses_energi(){
    if (front == nullptr){
        cout << "Antrean Masih Kosong" << endl;
        return;
    }
    nodeQueue* hapus = front;
    nodeStack* bantu = new nodeStack {hapus->organ, hapus->nama, top};
    top = bantu;
    root = tambah_tree(root, hapus->organ, hapus->nama);
    cout << "Berhasil Memproses Energi " << hapus->nama << "!" << endl << endl;
    front = hapus->next;
    if (front == nullptr){
        last = nullptr;
    }
    delete hapus;
}

void energi_terserap () {
    if (top == nullptr){
        cout << "Belum Ada Energi yang Terserap!" << endl;
        return;
    }
    nodeStack* bantu = top;
    int no = 1;
    cout << "=== Energi yang Sudah Terserap ===" << endl;
    while (bantu != nullptr) {
        cout << no << ". [" << bantu->organ << "] "<< "bantu->nama" << endl;
        bantu = bantu->next;
        no++;
    }
    cout << endl;
}

void cari_energi() {
    if (root == nullptr){
        cout << "Kode Energi Tidak Ditemukan" << endl;
        return;
    }
    int organ;
    cout << "Masukkan Kode Energi: ";
    cin >> organ;
    if (cin.fail() || organ <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode Enegi Harus Angka Lebih dari 0!" << endl;
        return;
    }
    nodeTree* hasil = cari_tree(root, organ);
    if (hasil == nullptr){
        cout << "Enegri dengan Kode " << organ <<" Tidak Ditemukan" << endl;
        return;
    }
    cout << "Ditemukan: [" << hasil->organ << "] " << hasil->nama << endl << endl;
}

void lihat_organ(){
    if (root == nullptr){
        cout << "Isi Organ Masih Kosong" << endl << endl;
        return;
    }
    char pilihan;
    int no = 1;
    cout << "=== Isi Kristal Organ ===" << endl << endl;
    cout << "1. Pre-order" << endl;
    cout << "2. In-order" << endl;
    cout << "3. Post-order" << endl << endl;
    cout << "Masukkan Pilihan Anda: ";
    cin >> pilihan;
    cout << endl;
    switch (pilihan) {
        case '1' : {
            preorder(root, no);
            break;
   
        }
        case '2' : {
            inorder(root, no);
            break;
        }
        case '3' : {
            postorder(root, no);
            break;
        }
        default: {
            cout << "Pilahan yang Anda  Masukkan Salah!" << endl;
        }
    }
    cout << endl;
}

void gunakan_energi () {
    if (root == nullptr){
        cout << "Isi Organ Masih Kosong" << endl << endl;
        return;
    }
    int organ;
    cout << "Masukkan Kode Energi: ";
    cin >> organ;
    if (cin.fail() || organ <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode Enegi Harus Angka Lebih dari 0!" << endl;
        return;
    }
    nodeTree* hasil = cari_tree(root, organ);
    if (hasil == nullptr){
        cout << "Enegri dengan Kode " << organ <<" Tidak Ditemukan" << endl;
        return;
    }
    cout << "Energi " <<  hasil->nama << " Telah Digunakan" << endl << endl;
    root = hapus_tree(root, organ);
}

int main (){
    char pilihan = '0';
    while (pilihan != 9){
        cout << "\n\n=== Sistem Organ Inti Nirwana ===" << endl << endl;
        cout << "1. Tambah Energi" << endl;
        cout << "2. Lihat Energi dalam Antrean" << endl;
        cout << "3. Proses Energi" << endl;
        cout << "4. Lihat Energi yang Sudah terserap" << endl;
        cout << "5. Hapus Riwayat Energi Teratas" << endl;
        cout << "6. Cari Energi di Organ" << endl;
        cout << "7. Lihat Isi Organ" << endl;
        cout << "8. Gunakan Energi" << endl;
        cout << "9. Keluar" << endl << endl;
        cout << "Masukkan Pilihan Anda: ";
        cin >> pilihan;
        switch (pilihan) {
            case '1': {
                char pil_tambah = 'y';
                while (pil_tambah == 'y' || pil_tambah == 'Y'){
                    tambah_energi();
                    cout << "Apakah anda Ingin Menambahkan Energi Lagi? (y/n): ";
                    cin >> pil_tambah;
                }
                break;
            }
            case '2' : {
                lihat_antrean();
                break;
            }
            case '3' : {
                proses_energi();
                break;
            }
            case '4' : {
                energi_terserap();
                break;
            }
            case '5' : {
                cout << "Maaf! Program belum dibuat, Sekar kehabisan waktu"<< endl;
                break;
            }
            case '6' : {
                cari_energi();
                break;
            }
            case '7' : {
                lihat_organ();
                break;
            }
            case '8' : {
                gunakan_energi();
                break;
            }
            case '9' : {
                cout << "Program akan dikeluarkan, Terima Kasih!";
                exit (0);
            }
            default: {
                cout << "Pilihan yang Anda Masukkan Salah!" << endl;
                cout << "Silahkan Coba lagi." << endl << endl;
            }
        }

    }
}