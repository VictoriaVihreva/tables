#include "Polinom.h"
#include <list>

using namespace std;

struct HashFunc1 {
    int operator()(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash + ch) % 100;
        }
        return hash;
    }
};
template<typename HashFunc>
class HashTable {
private:
    static const int TABLE_SIZE = 100;
    vector<list<pair<string, Polinom>>> table;
    HashFunc hashFunction;

public:
    HashTable() : table(TABLE_SIZE) {}

    void addPol(const string& name, Polinom& pol)
    {
        int i = hashFunction(name) % TABLE_SIZE;
        for (auto& st : table[i]) 
            if (st.first == name) 
            {
                st.second = pol;
                return;
            }
        table[i].emplace_back(name, pol);
    }

    void delPol(const string& name)
    {
        int i = hashFunction(name) % TABLE_SIZE;
        for (auto it = table[i].begin(); it != table[i].end(); it++) 
            if (it->first == name) 
            {
                table[i].erase(it);
                return;
            }
    }

    Polinom* searchPol(const string& name)
    {
        int i = hashFunction(name) % TABLE_SIZE;
        for (auto& st : table[i])
            if (st.first == name)
                return &st.second;

        return nullptr;
    }

    void print()
    {
        for (int i = 0; i < TABLE_SIZE; i++) 
            if (!table[i].empty()) 
            {
                for (auto& st : table[i]) 
                {
                    cout << st.first << ": ";
                    st.second.print();
                    cout << "; ";
                }
                cout << endl;
            }
    }
};

