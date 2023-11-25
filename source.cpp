#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

class Data{
    private:
        int value;
    public:
        Data(int x){
            value = x;
            cout << "Data created with value " << value << " yep!" << endl;
        };
        int getValue(){return value;}
};

class Node{
    private:
        int minKeys, maxKeys, minBranches, maxBranches;
    public:
        vector<Data*> keys;
        vector<Node*> branches;
        Node* parent;
        Node(int m){
            maxBranches = m;
            maxKeys = m-1;
            minKeys = m/2;
            minBranches = m/2+1;
            cout << "Node created!" << endl;
        }
        bool isFull(){return (keys.size() < maxKeys)?false:true;}
};

bool compareVec(Data *d1, Data *d2){
    return d1->getValue() < d2->getValue();
}
// TODO
void addKey(Node* root,Data* data){
    if(!root->isFull()){
        root->keys.push_back(data);
    }
    else{

    }
    sort(root->keys.begin(),root->keys.end(),compareVec);
}
// TODO
void refraction(){

}

int main(){
    int m = 0;
    Data* dat;
    while( m < 3 || m > 10){
        cout << "Input node size: ";
        cin >>  m;
        if(m < 3 || m > 10) cout << "Node size is out of range. Size should be between 3 and 10." << endl;
    }
    Node* tree = new Node(m);
    addKey(tree,new Data(3));
    addKey(tree,new Data(2));
    cout<<tree->keys[0]->getValue()<<" "<<tree->keys[1]->getValue()<<endl;
    return 0;
}