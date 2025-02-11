#include "libr.h"
#include "saugojimas_masyve.cpp"

vector <duomenys> studentai;

int main()
{
    read("C:/Users/PC/Documents/GitHub/pirmas/duomenys.txt",studentai);
    write("C:/Users/PC/Documents/GitHub/pirmas/rez.txt",studentai);
    return 0;
}
