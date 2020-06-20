#include <iostream>
#include <string>
#include <assert.h>
#include <vector>
#include <cstddef>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
const int TABLE_SIZE = 1000;

class HashNode {
private:
    int key;
    int value;

public:
    HashNode(int key, int value) {
        this->key = key;
        this->value = value;
    }
    int getKey() {
        return key;
    }
    int getValue() {
        return value;
    }
};                            //From c++ reference.

class HashNodeChained {

private:
    int key;
    int value;

public:
    HashNodeChained* next;

    HashNodeChained(int key, int value) {  //From c++ reference
        this->key = key;
        this->value = value;
        this->next = NULL;
    }


    int getKey() {
        return key;
    }
    int getValue() {
        return value;
    }

    void setValue(int val) {
        this->value = val;
    }

};

class HashMap {
private:
    HashNode **tableUnchained;
    HashNodeChained **table;
    string collisionResolutionType;
    string hashMethod;
    int numCollisions = 0;
    int filledBuckets = 0;
    int numTotalItems = 0;


public:
    HashMap(string collisionResolutionType, string hashMethod) {

        this->collisionResolutionType = collisionResolutionType;
        this->hashMethod = hashMethod;

        if (this->collisionResolutionType == "chaining") {
            // Chaining method
            table = new HashNodeChained*[TABLE_SIZE];

            for (int i = 0; i < TABLE_SIZE; i++) // Set the table
                table[i] = NULL;
        } else {
            // Linear addressing method
            tableUnchained = new HashNode*[TABLE_SIZE];

            for (int i = 0; i < TABLE_SIZE; i++)  //Set the table
                tableUnchained[i] = NULL;
        }

    }

    int midsquare(int key) {

        int index = 0;
        double x;
        double y;
        int z;
        x = pow((TABLE_SIZE*3), 2);
        y = ceil(log2(x));
        z = y - ceil(log2(TABLE_SIZE));
        z = z/2;
        index = (pow(key,2)) / pow(2,z);
        int value1 = index % TABLE_SIZE;
        return value1;

    }

    int hashFunction(int key) {

        if (this->hashMethod == "mod") {
            // Mod method
            return (key % TABLE_SIZE);
        } else {
            return midsquare(key);
        }

    }

    int get(int key) {  // From c++ reference. A bit of code written by me tho.

        int hash = hashFunction(key);

        if (this->collisionResolutionType == "chaining") {

            // Chaining resolution

            bool flag = false;
            HashNodeChained* entry = table[hash];

            while (entry != NULL) {
                if (entry->getKey() == key) {
                    return entry->getValue();
                    flag = true;
                } else {
                    entry = entry->next;
                }
            }

            return -1;

        } else {

            // Open addressing resolution

            while (tableUnchained[hash] != NULL && tableUnchained[hash]->getKey() != key)
                hash = (hash + 1) % TABLE_SIZE;

            if (tableUnchained[hash] == NULL)
                return -1;
            else
                return tableUnchained[hash]->getValue();

        }

    }

    void put(int key, int value) {

        int hash = hashFunction(key);

        if (this->collisionResolutionType == "chaining") {

            // Chaining resolution

            this->numTotalItems = this->numTotalItems + 1;

            HashNodeChained* prev = NULL;
            HashNodeChained* entry = table[hash];

            while (entry != NULL) {
                prev = entry;
                entry = entry->next;
            }

            if (entry == NULL) {
                entry = new HashNodeChained(key, value);
                if (prev == NULL) {
                    table[hash] = entry;
                } else {
                    prev->next = entry;
                }
            } else {
                //entry->setValue(value);
            }

        } else {

            // Linear addressing resolution

            if (this->getNumFilledBuckets() != TABLE_SIZE) {

                bool collision = false;
                this->numTotalItems = this->numTotalItems + 1;

                while (tableUnchained[hash] != NULL) {
                    hash = (hash + 1) % TABLE_SIZE;
                    if (!collision) {
                        this->numCollisions = this->numCollisions + 1;
                        collision = true;
                    }
                }

                if (tableUnchained[hash] == NULL)
                    tableUnchained[hash] = new HashNode(key, value);

            }

        }

    }

    int getNumFilledBuckets() {

        int filled = 0;
        if (this->collisionResolutionType == "chaining") {

            for (int i = 0; i < TABLE_SIZE; i++)
                if (table[i] != NULL)
                    filled++;

        } else {

            for (int i = 0; i < TABLE_SIZE; i++)
                if (tableUnchained[i] != NULL)
                    filled++;

        }
        return filled;

    }

    int getNumCollisions() {

        if (this->collisionResolutionType == "chaining") {
            return (this->numTotalItems - getNumFilledBuckets());
        } else {
            return this->numCollisions;
        }

    }

    double getLoadFactor() {
        return ((double)this->numTotalItems / (double)TABLE_SIZE);
    }

    ~HashMap() { // From c++ reference

        if (this->collisionResolutionType == "chaining") {

            for (int i = 0; i < TABLE_SIZE; i++)
                if (table[i] != NULL)
                    delete table[i];

            delete[] table;

        } else {

            for (int i = 0; i < TABLE_SIZE; i++)
                if (tableUnchained[i] != NULL)
                    delete tableUnchained[i];

            delete[] tableUnchained;

        }

    }

};


int main() {

    srand(time(0));
    vector<int> keys;
    vector<int> values;
    //for (int i = 0; i < TABLE_SIZE; i++) {
        //keys.push_back(i);
        //values.push_back(i * 3);
    //}
     //Chaining method with mod
    HashMap hmapChain = HashMap("chaining", "mod"); // WORKS
    for(int a = 0; a < 500; a++) {
        hmapChain.put(rand() % (3 * TABLE_SIZE), 10);
    }

    cout << "Hash Map Chaining Method & Mod: \n";
    cout << "Num Filled Buckets: " << hmapChain.getNumFilledBuckets() << "\n";
    cout << "Load Factor: " << hmapChain.getLoadFactor() << "\n";
    cout << "Collision Count: " << hmapChain.getNumCollisions() << "\n---\n";


    // Chaining method with midsquare
    HashMap hmapChainMid = HashMap("chaining", "mid");
   for(int a = 0; a < 500; a++ ) // Stop when the load factor is 1
   {
       hmapChainMid.put(rand() % (3 * TABLE_SIZE),40);
   }

    cout << "Hash Map Chaining Method and  MidSquare: \n";
    cout << "Num Filled Buckets: " << hmapChainMid.getNumFilledBuckets() << "\n";
    cout << "Load Factor: " << hmapChainMid.getLoadFactor() << "\n";
    cout << "Collision Count: " << hmapChainMid.getNumCollisions() << "\n---\n";


   // Open addressing method with mod1
    HashMap hmapOpen = HashMap("open", "mod"); // WORK
    for(int a = 0; a < 500; a++) { // Stop when the load factor is 1
        hmapOpen.put(rand() % (3 * TABLE_SIZE), 10);
    }

    cout << "Hash Open Addressing Method & Mod: \n";
    cout << "Num Filled Buckets: " << hmapOpen.getNumFilledBuckets() << "\n";
    cout << "Load Factor: " << hmapOpen.getLoadFactor() << "\n";
    cout << "Collision Count: " << hmapOpen.getNumCollisions() << "\n---\n";

    // Open addressing method with midsquare
    HashMap hmapOpenMid = HashMap("open", "mid");
    for(int a = 0; a < 500; a++)  //Stop when the load factor is 1
    {
        hmapOpenMid.put(rand() % (3 * TABLE_SIZE), 10);
    }
    cout << "Hash Open Addressing Method & Mid: \n";
    cout << "Num Filled Buckets: " << hmapOpenMid.getNumFilledBuckets() << "\n";
    cout << "Load Factor: " << hmapOpenMid.getLoadFactor() << "\n";
    cout << "Collision Count: " << hmapOpenMid.getNumCollisions() << "\n---\n";


}















