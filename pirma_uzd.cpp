// #include "duomenys.h"               // skirtas atsidarant per editoriu
#include "duomenys.cpp"          // skirtas atsidarant per terminala

vector<duomenys> studentai;

int main() {
    srand(time(nullptr));
    meniu(studentai);
    cout << "Iveskite bet ka, kad baigti darba.";
    cin.ignore(256, '\n');
    cin.get();
    return 0;
}