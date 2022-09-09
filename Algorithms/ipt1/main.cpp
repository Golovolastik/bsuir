#include <iostream>

using namespace std;

struct LIST{
    string value;
    LIST* next;
};

void add(LIST dict[], string element);
int hash_function(string element);

int main() {
    LIST dict[255];
    while (1){
        cout << "1) Add" << endl;
        cout << "2) Add from file" << endl;
        cout << "3) Delete" << endl;
        cout << "4) Info" << endl;
        cout << "5) Search" << endl;
        cout << "6) Exit" << endl;
        int i;
        cin >> i;
        switch (i) {
            case 1: {
                cout << "Enter element:" << endl;
                string element;
                cin >> element;
                add(dict, element);
                break;
            }
            case 2: {
                cout << "Hello" << endl;
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 6: {
                return 0;
            }
            default: break;
        }
    }
}

void add(LIST dict[], string element){
    int hash = hash_function(element);
    dict[hash].value = element;
    dict[hash].next = NULL;
    return;
}

int hash_function(string element){
    int result = 0;
    for (int i=0; i<element.length(); i++){
        result += element[i];
    }
    result %= 255;
    cout << "Hash = " << result << endl;
    return result;
}
