#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;
using std::string;
using std::vector;
using std::fstream;
using std::ifstream;

struct duomenys_m {           // apsirasoma struktura duomenims saugoti.
    string vardas, pavarde;
    int nd[100];
    int nd_sk{};
    int egz;
}A[100];

int zmn_sk{};

void inputStudentData() {
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
        zmn_sk++;
    }
}

double galutinis_vid(int j) {              // skaiciuoja galutini bala pagal vidurki
    double vid = 0;
    for (int i = 0; i < A[j].nd_sk; i++) {
        vid += A[j].nd[i];
    }
    vid /= A[j].nd_sk;
    return 0.4 * vid + 0.6 * A[j].egz;
}

double galutinis_med(int j) {         // skaiciuoja galutini bala pagal mediana
std::sort(A[j].nd, A[j].nd + A[j].nd_sk);
    double med;
    if (A[j].nd_sk == 0) {
        med = 0;
    }else if (A[j].nd_sk % 2 == 0) {
        med = (A[j].nd[A[j].nd_sk / 2 - 1] + A[j].nd[A[j].nd_sk / 2]) / 2.0;
    } else {
        med = A[j].nd[A[j].nd_sk / 2];
    }
    return 0.4 * med + 0.6 * A[j].egz;
}

void write(const string &filename) {           //isvedimo funkcija
    fstream out(filename);
    cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left << "Galutinis (Vid.) / Galutinis (Med.)" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < zmn_sk; i++) {
        cout <<setw(20) << left << A[i].vardas << setw(20) << left << A[i].pavarde << setw(20) << left << fixed << setprecision(2) << galutinis_vid(i) << setw(20) << left << fixed << setprecision(2) << galutinis_med(i) <<endl;
    }
    out.close();
}
