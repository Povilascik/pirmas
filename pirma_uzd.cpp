#include "duomenys.h"
// #include "duomenys.cpp"

vector<duomenys> studentai;

int main() {
    srand(time(nullptr));
    meniu(studentai);
    cout << "Iveskite bet ka, kad baigti darba.";
    cin.ignore(256, '\n');
    cin.get();
    return 0;
}
///usr/bin/c++ -std=c++17 -o CMakeFiles/pirma_uzd.dir/pirma_uzd.cpp.o -c /path/to/your/project/pirma_uzd.cpp
//complie settings , kompiliatoriaus eilute