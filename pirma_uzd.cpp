#include "libr.h"
#include  "saugojimas_masyve.h"

vector <duomenys> studentai;

int main()
{
    read("C:/Users/PC/Documents/GitHub/pirmas/duomenys.txt",studentai);
    write("C:/Users/PC/Documents/GitHub/pirmas/rez.txt",studentai);
    ivedimas();
    write1("C:/Users/PC/Documents/GitHub/pirmas/rez.txt");
    return 0;
}
