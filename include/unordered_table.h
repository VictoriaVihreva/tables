#include "polinom.h"
using namespace std;

class UnorderedTable {
private:
    static const int MAX_SIZE = 100;
    pair<string, Polinom> table[MAX_SIZE];
    int size;

public:
    UnorderedTable() : size(0) {}

    void addPol(const string& name, Polinom& pol)
    {
        for (int i = 0; i < size; i++)
            if (table[i].first == name)
            {
                table[i].second = pol;
                return;
            }
        if (size < MAX_SIZE)
        {
            table[size] = make_pair(name, pol);
            size++;
        }
        else
            throw out_of_range("Size is out of range");
    }

    void delPol(const string& name)
    {
        for (int i = 0; i < size; i++)
            if (table[i].first == name) {
                for (int j = i; j < size - 1; j++)
                    table[j] = table[j + 1];
                size--;
                return;
            }
    }


    Polinom* searchPol(const string& name)
    {
        for (int i = 0; i < size; i++)
            if (table[i].first == name)
                return &table[i].second;
        return nullptr;
    }

    void printTable()
    {
        for (int i = 0; i < size; i++)
        {
            cout << table[i].first << ": ";
            table[i].second.Print();
            cout << endl;
        }
    }
};
