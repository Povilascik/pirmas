#ifndef DUOMENYS_H
#define DUOMENYS_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <ctime>
#include <unordered_map>
#include <chrono>
#include <list>
#include <deque>
#include <fstream>
#include <cwchar>

const std::string test_file_location = TEST_FILE_LOCATION;      // skirtas naudoti SU CMake
// const std::string test_file_location = "";                   // skirtas naudoti BE CMake

struct blogi;
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



struct duomenys {
    // apsirasoma struktura duomenims saugoti.
    string vardas, pavarde;
    vector<int> nd;
    int egz;
    double vid, med;
};

struct blogi {
    // apsirasoma struktura duomenims saugoti.
    string vardas, pavarde;
    vector<int> nd;
    int egz;
    double vid, med;
};

void meniu(vector<duomenys > &studentai);

double galutinis_vid(vector<int> nd, int egz);

void galutinis_vid(vector<int> nd, int egz, vector<duomenys> &studentai);

double galutinis_med(vector<int> nd, int egz);

void galutinis_med(vector<int> nd, int egz, vector<duomenys> &studentai);

void read(const string &filename, vector<duomenys> &studentai);

void ss_write(const string &filename, vector<duomenys> &studentai);

void write(vector<duomenys> &studentai);

void write_file(const std::string &filename, std::vector<duomenys> &studentai, int nd_skaicius);

void make_file(vector <duomenys>& studentai,const string& filename, int mok_sk, int paz_sk);

void generuoti_paz(duomenys &student, int paz_sk);

void generuoti_paz_ranka(vector<duomenys> &studentai);

void generuoti_vard(vector<duomenys> &studentai, int paz_sk1, int mok_sk);

void sortas(vector<duomenys> &studentai);

//void dalina(vector<duomenys> &studentai);

#endif //DUOMENYS_H
