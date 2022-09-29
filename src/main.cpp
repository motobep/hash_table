#include <iostream>
#include <string>

#include "HashTable.h"

using std::cout;
using std::endl;
using std::string;


int main() {
    HashTable<string, string> table(10);
    string str = "new";

    table.set("first", str);
    string val = table.get("first");
    cout << "First value: " << val << endl;

    table.set("some key", "some value");
    table.show_vector();

    return 0;
}

