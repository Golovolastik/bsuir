#include <iostream>
#include <fstream>
#define SIZE 50

using namespace std;

struct LIST{
    string value;
    LIST* next;
};

void add(LIST *dict[], string element);
int hash_function(string element);
void print_list(LIST *list);

int main() {
    LIST *dict[SIZE];
    for (int i=0; i<SIZE; i++){
        dict[i] = new LIST;
        dict[i]->next = NULL;
    }
    while (1){
        cout << "1) Add" << endl;
        cout << "2) Add from file" << endl;
        cout << "3) Delete" << endl;
        cout << "4) Info" << endl;
        cout << "5) Search" << endl;
        cout << "6) Exit" << endl;
        cout << "7) Print all" << endl;
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
                ifstream file;
                file.open ("wordlist.10000.txt");
                string word;
                while (file >> word)
                {
                    //cout << word << endl;
                    add(dict, word);
                }
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
            case 7: {
                for (int i=0; i<SIZE; i++){
                    cout << "Index: " << i << " ";
                    print_list(dict[i]);
                    cout << endl;
                    //printf("Index: %d Values: %s\n", i, dict[i] -> value.c_str());
                }
            }
            default: break;
        }
    }
}

void add(LIST *dict[], string element){
    int hash = hash_function(element);
    if (dict[hash] -> value == "") {
        dict[hash]->value = element;
        dict[hash]->next = NULL;
    } else{
        struct LIST* temp;
        temp = new LIST;
        temp -> value = element;
        temp -> next = dict[hash];
        dict[hash] = temp;
    }
}

int hash_function(string element){
    int result = 0;
    for (int i=0; i<element.length(); i++){
        result += element[i];
    }
    result %= SIZE;
    return result;
}

void print_list(LIST *list){
    struct LIST *temp = list;
    do {
        cout << temp -> value << " ";
        temp = temp -> next;
    } while (temp -> next != NULL);


}
