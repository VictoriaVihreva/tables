#include "polinom.h"


int main()
{
    Polinom p1("-7y-15xyz+x^2y");
    Polinom p2("y-12+5xyz+45x^2y^4z^3");
    cout << "p1 = ";
    p1.Print();
    cout << "\np2 = ";
    p2.Print();
    Polinom res;
    res = p1 + p2;
    cout << "\np1 + p2 = ";
    res.Print();
    res = p2-p1;
    cout << "\np2 - p1 = ";
    res.Print();
    res = p1 * p2;
    cout << "\np1 * p2 = ";
    res.Print();
    res = p1 * 3;
    cout << "\np1 * 3 = ";
    res.Print();

    /*Polinom pol1("12x^2yz+12+11x");
    Polinom pol2("6x+25x^2y^2z^2+5");
    Polinom pol3 = pol1 + pol2;
    Polinom pol4("25x^2y^2z^2+12x^2yz+17x+17");
    pol3.Print();*/
}

