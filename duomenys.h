#ifndef DUOMENYS_H
#define DUOMENYS_H

#include <iostream>
#include <vector>
#include <iomanip>

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
using std::ofstream;
using std::time;
using std::srand;
using std::rand;

struct duomenys {           // apsirasoma struktura duomenims saugoti.
    string vardas, pavarde;
    vector <int> nd;
    int egz;
    double vid, med;
};

double galutinis_vid(vector<int> nd, int egz);
void galutinis_vid(vector<int> nd, int egz, vector<duomenys> &studentai);
double galutinis_med(vector<int> nd, int egz);
void galutinis_med(vector<int> nd, int egz, vector<duomenys> &studentai);
void read(const string &filename, vector<duomenys> &studentai);
void ss_write(const string &filename, vector<duomenys> &studentai);
void write(const string &filename, vector<duomenys> &studentai);
void generuoti_paz(duomenys &student);
void generuoti_paz_ranka(vector<duomenys> &studentai);
void generuoti_vard(vector<duomenys> &studentai);
void sort(vector<duomenys> &studentai);

#endif //DUOMENYS_H
