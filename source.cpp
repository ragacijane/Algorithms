#include <iostream>
#include <vector>
#include <algorithm>

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
        bool node,leaf,root;
        vector<Data*> keys;
        vector<Node*> branches;
        Node* parent;
        Node(int m){
            maxBranches = m;
            maxKeys = m-1;
            minKeys = m/2;
            minBranches = m/2+1;
            branches.push_back(nullptr);
            leaf=root=false;
            node=true;
            cout << "Node created!" << endl;
        }
        bool isFull(){return (keys.size() < maxKeys)?false:true;}
        int getNodeSize(){return maxBranches;}
};

bool compareVec(Data *d1, Data *d2){
    return d1->getValue() < d2->getValue();
}

bool compareNode(Node* n1,Node* n2){
    return n1->keys[0]->getValue() < n2->keys[0]->getValue();
}

// FIXME
void addKey(Node* temp,Data* data){
    if(!temp->isFull() && temp->leaf){
        temp->keys.push_back(data);
        temp->branches.push_back(nullptr);
    }
    else {
        while(!temp->leaf){
        for(int i=0; i< temp->keys.size(); i++)
            if( temp->keys[i]->getValue() > data->getValue())
                temp=temp->branches[i];
            else if( i == temp->keys.size()-1 && temp->keys[i]->getValue() < data->getValue())
                temp=temp->branches[i+1];
        }
        if(!temp->isFull() && temp->leaf){
        temp->keys.push_back(data);
        temp->branches.push_back(nullptr);
        }
        else refractionLeaf(temp,data);
    }
    sort(temp->keys.begin(),temp->keys.end(),compareVec);
}

// FIXME
void refractionLeaf(Node *temp,Data* data){
    Node* left,*right,*parent,*destroy;
    vector<Data*> datas;
    for(int i=0; i<temp->keys.size();i++)datas.push_back(temp->keys[i]);
    datas.push_back(data);
    sort(temp->keys.begin(),temp->keys.end(),compareVec);
    int middle=datas.size()/2;
    left=new Node(temp->getNodeSize());
    right=new Node(temp->getNodeSize());
    destroy=temp;
    parent=left->parent=right->parent=temp->parent;
    for(int i=0;i<datas.size();i++){
        if(i<middle){
            left->keys.push_back(datas[i]);
            left->branches.push_back(nullptr);
        }
        if(i>middle){
            right->keys.push_back(datas[i]);
            right->branches.push_back(nullptr);
        }
    }
    if(parent->isFull())refractionNode();
    else{
        parent->keys.push_back(datas[middle]);
        sort(parent->keys.begin(),parent->keys.end(),compareVec);
        parent->branches.push_back(left);
        parent->branches.push_back(right);
        sort(temp->branches.begin(),temp->branches.end(),compareNode);
    }

}

// TODO
void refractionNode(){

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
    return 0;
}