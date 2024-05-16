#include <fstream>
#include <string>
#include <iostream>
#include <map>

using namespace std;

struct Ogrenci {
    string ad;
    string soyad;
    int numara;
    string bolum;
};

void sequential() {
    ofstream dosya("ogrenciler.txt", ios::app);

    if (!dosya) {
        cerr << "Dosya açılamadı!";
        return;
    }

    Ogrenci ogrenci;

    cout << "Öğrenci adı: ";
    getline(cin, ogrenci.ad);
    //cout << endl;
    cout << "Öğrenci soyadı: ";
    getline(cin, ogrenci.soyad);
    cout << "Öğrenci numarası: ";
    cin >> ogrenci.numara;
    cout << "Bölüm: ";
    cin >> ogrenci.bolum;

    dosya << ogrenci.numara << " " << ogrenci.ad << " " << ogrenci.soyad << " " << ogrenci.bolum << endl;

    dosya.close();

    cout << "Öğrenci bilgileri dosyaya kaydedildi." << endl;
}

void direcacces(const string& dosyaAdi, int numara) {
    ifstream dosya(dosyaAdi);

    if (!dosya) {
        cerr << "Dosya bulunamadı" << endl;
        return;
    }

    Ogrenci ogrenci;
    while (dosya >> ogrenci.numara >> ogrenci.ad >> ogrenci.soyad >> ogrenci.bolum) {
        if (ogrenci.numara == numara) {
            cout << "Okunan veri: " << ogrenci.numara << " " << ogrenci.ad << " " << ogrenci.soyad << " " << ogrenci.bolum << endl;
            return;
        }
    }

    cerr << "Öğrenci bulunamadı" << endl;
}

map<string, long> buildIndex(const string& dosyaadi) {
    ifstream dosya(dosyaadi);
    map<string, long> index;
    string line;
    long position = 0;

    if (!dosya) {
        cerr << "dosya açılamadı" << endl;
    }
    while (getline(dosya, line)) {
        string key = line.substr(0, line.find(' '));
        index[key] = position;
        position = dosya.tellg();
    }
    dosya.close();
    return index;
}
void searchbykey(const string& filename, const map<string, long>& index, const int& key) {
    string skey = to_string(key);
    auto it = index.find(skey);
    if (it == index.end()) {
        cout << "key bulunamadı: " << key << endl;
        return;
    }
    ifstream dosya(filename);
    dosya.seekg(it->second);
    string line;
    getline(dosya, line);
    cout << "Bulunan satır: " << line << endl;
    dosya.close();
}

int main() {

    cout << "yapacağınız işlemi seçiniz:\n1->öğrenci ekleme\n2->direct access erişim\n3->index arama" << endl;
    int islem;
    cin >> islem;

    switch (islem) {
    case 1:
        sequential();
        break;
    case 2:
        cout << "öğrenci numarasını giriniz: " << endl;
        int num;
        cin >> num;
        direcacces("ogrenciler.txt", num);
        break;
    case 3:
        cout << "öğrenci numarasını giriniz: " << endl;
        int num1;
        cin >> num1;
        auto index = buildIndex("ogrenciler.txt");
        searchbykey("ogrenciler.txt", index, num1);
        break;

    
    }

    return 0;
}
