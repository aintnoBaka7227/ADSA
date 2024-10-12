#include <iostream>
#include <vector> 
#include <string> 
#include <sstream> 

class HashSlot {
    private: 
    std::string key; 
    std::string status;
    friend class HashTable;
    public: 
    HashSlot() : key(""), status("never used") {};
}; 

class HashTable {
    private: 
    std::vector<HashSlot> table; 
    public:
    HashTable() : table(26) {}; 
    int hash (std::string key) {
        return key.back() - 'a';
    }
    int searching(std::string key) {
        int hash_value = hash(key);
        int flag = hash_value;
        while (table[hash_value].status != "never used") {
            if (table[hash_value].status == "occupied" && table[hash_value].key == key) {
                return hash_value;
            }
            hash_value = (hash_value + 1) % 26;
            if (flag == hash_value) {
                break;
            }
        }
        return -1;
    }

    void insertion(std::string key) {
        if (searching(key) != -1) {
            return;
        }
        int hash_value = hash(key);
        while (table[hash_value].status == "occupied") {
            hash_value = (hash_value + 1) % 26;
        }
        table[hash_value].status = "occupied";
        table[hash_value].key = key;
    }

    void deletion(std::string key) {
        int hash_value = searching(key);
        if (hash_value == -1) {
            return;
        }
        else {
            table[hash_value].status = "tombstone";                                     
        }
    }

    void print() {
        for (int i = 0; i < 26; i++) {
            if (table[i].status == "occupied") {
                std::cout << table[i].key << " ";
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    std::string instruction;
    getline(std::cin, instruction);
    std::stringstream ss(instruction);
    std::string move;
    std::vector<std::string> moves;
    while(ss >> move) {
        moves.push_back(move);
    }

    HashTable hash_table; 
    for (size_t i = 0; i < moves.size(); i++) {
        std::string key = moves[i].substr(1);
        if (moves[i][0] == 'A') { 
            hash_table.insertion(key);
        }
        else if (moves[i][0] == 'D') {
            hash_table.deletion(key);
        }
    }

    hash_table.print();

    return 0;
}