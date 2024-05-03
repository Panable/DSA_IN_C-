#pragma once
#include <initializer_list>
#include <iostream>
#include <vector>

template <typename k, typename v>
class HashTable
{
public:
    HashTable(const std::vector<k>& keys, const std::vector<v>& values)
    {
        num = keys.size();
        this->keys = new k[num];
        this->values = new v[num];

        for(int i = 0; i < num; i++)
        {
            this->keys[i] = keys[i];
            this->values[i] = values[i];
        }

        nmax = num * 100;
        tbl = new v*[nmax]; // Store pointers to values, not values themselves

        for(int i = 0; i < nmax; i++)
        {
            tbl[i] = nullptr; // Initialize all pointers to nullptr
        }

        for(int i = 0; i < num; i++)
        {
            unsigned int h = hash1(this->keys[i]);
            tbl[h] = &this->values[i]; // Store the pointer to the value
        }
    }

public:
    v* GetValue(k key)
    {
        unsigned int h = hash1(key);
        if (tbl[h]) {
            return tbl[h]; // Return the pointer to the value
        }
        else {
            return nullptr; // Value not initialized
        }
    }

private:
    k* keys;
    v* values;
    v** tbl; // Array of pointers to values
    int num;
    unsigned int nmax;

    unsigned int raw_hash(void* key, int len)
    {
        unsigned char* p = (unsigned char*)key;
        unsigned int h = 0x811c9dc5;
        int i;

        for(i = 0; i < len; i++)
            h = (h ^ p[i]) * 0x01000193;

        return h;
    }

    unsigned int hash1(k key)
    {
        char const* p = &key[0];
        unsigned int index = raw_hash((void*)p, key.size());
        return index % nmax;
    }
};

