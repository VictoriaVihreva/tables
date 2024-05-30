#include "Polinom.h"

using namespace std;

class OrderedTable {
private:
    list<pair<string, Polinom>> table;

public:
    void addPol(const string& name, Polinom& pol)
    {
        for (auto id = table.begin(); id != table.end(); id++) {
            if (id->first == name) {
                id->second = pol;
                return;
            }
            else if (id->first > name) {
                table.insert(id, make_pair(name, pol));
                return;
            }
        }
        table.emplace_back(name, pol);
    }

    void delPol(const string& name)
    {
        for (auto id = table.begin(); id != table.end(); id++) {
            if (id->first == name) {
                table.erase(id);
                return;
            }
        }
    }

    Polinom* searchPol(const string& name)
    {
        for (auto& st : table) {
            if (st.first == name) {
                return &st.second;
            }
        }
        return nullptr;
    }

    void printTable()
    {
        for (auto& st : table) {
            cout << st.first << ": ";
            st.second.Print();
            cout << endl;
        }
    }
};