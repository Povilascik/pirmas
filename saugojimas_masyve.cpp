#include "saugojimas_masyve.h"

using namespace std;

/*void ivedimas() {
    while (true) {
        duomenys_m student;
        cout << "Įveskite mokinio vardą (įveskite 'p' norint užbaigti): ";
        cin >> student.vardas;
        if (student.vardas == "p") break;
        cout << "Įveskite mokinio pavardę: ";
        cin >> student.pavarde;
        student.nd_sk = 0;
        cout << "Įveskite pažymius už namų darbus (įveskite -1 norint užbaigti): ";
        while (true) {
            int grade;
            cin >> grade;
            if (grade == -1) break;
            if (grade >= 0 && grade <= 10) {
                student.nd[student.nd_sk++] = grade;
            }
        }
        cout << "Įveskite egazmino pažymį: ";
        cin >> student.egz;
        B[zmn_sk++] = student;
    }
}

double galutinis_vid1(int j) {
    double vid = 0;
    for (int i = 0; i < B[j].nd_sk; i++) {
        vid += B[j].nd[i];
    }
    vid /= B[j].nd_sk;
    return 0.4 * vid + 0.6 * B[j].egz;
}

double galutinis_med1(int j) {
    std::sort(B[j].nd, B[j].nd + B[j].nd_sk);
    double med;
    if (B[j].nd_sk == 0) {
        med = 0;
    } else if (B[j].nd_sk % 2 == 0) {
        med = (B[j].nd[B[j].nd_sk / 2 - 1] + B[j].nd[B[j].nd_sk / 2]) / 2.0;
    } else {
        med = B[j].nd[B[j].nd_sk / 2];
    }
    return 0.4 * med + 0.6 * B[j].egz;
}

void write1(const string &filename) {
    fstream out(filename);
    cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left << "Galutinis (Vid.) / Galutinis (Med.)" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < zmn_sk; i++) {
        cout << setw(20) << left << B[i].vardas << setw(20) << left << B[i].pavarde << setw(20) << left << fixed << setprecision(2) << galutinis_vid1(i) << " / " << galutinis_med1(i) << endl;
    }
    out.close();
}
*/
int main () {
    ivedimas();
    write1("C:/Users/PC/Documents/GitHub/pirmas/rez.txt");
    return 0;
}