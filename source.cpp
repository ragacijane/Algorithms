#include <iostream>
#include <list>
using namespace std;

class Data{
    private:
        int x;
    public:
        Data(int x){
            x=x;
            cout << "Data created with value " + x << endl;
        };
};

class Node{
    private:
        list<Data*> keys;
        list<Node*> branches;
        Node* parent;
    public:
        Node(){
            cout << "Node created!" << endl;
        }
};

int main(){
    return 0;
}