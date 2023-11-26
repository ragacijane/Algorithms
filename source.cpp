#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Data{
    private:
        int value;
    public:
        Data(int x){
            value = x;
        };
        int getValue(){return value;}
};

class Node{
    private:
        int minKeys, maxKeys, minBranches, maxBranches;
    public:
        bool leaf,root;
        vector<Data*> keys;
        vector<Node*> branches;
        Node* parent;
        Node(int m){
            maxBranches = m;
            maxKeys = m-1;
            minKeys = m/2;
            minBranches = m/2+1;
            //branches.push_back(NULL);
            leaf=root=false;
        }
        bool overFull(){return (keys.size() > maxKeys)?true:false;}
        bool isFull(){return (keys.size() < maxKeys)?false:true;}
        int getNodeSize(){return maxBranches;}
        friend ostream& operator<<(ostream& os,const Node &n){
            int i;
            os<<"(";
            for(i=0; i<n.maxBranches-1; i++){
                if(i<n.keys.size())
                    os<<setw(2)<<n.keys[i]->getValue();
                else os<<setw(2)<<" ";

                if(i == n.maxBranches-2)os<<")";
                else os<<"|";
            }
            return os;
        }
};

bool compareVec(Data *d1, Data *d2){
    return d1->getValue() < d2->getValue();
}

bool compareNode(Node* n1,Node* n2){
    if(n1!=nullptr && n2!=nullptr)
        return n1->keys[0]->getValue() < n2->keys[0]->getValue();
    else return true;
}

// DONE
void refraction(Node *temp,Data* data){
    int i;
    Node* left,*right,*parent,*destroy;
    do{
        left=new Node(temp->getNodeSize());
        right=new Node(temp->getNodeSize());
        Data* tempData;

        int middle=temp->keys.size()/2;
        tempData=temp->keys[middle];
        //splitting overfull node
        for(i=0;i<temp->keys.size();i++){
            if(i<middle){
                left->keys.push_back(temp->keys[i]);
                left->branches.push_back(temp->branches[i]);
            }
            if(i==middle)
                left->branches.push_back(temp->branches[i]);
            if(i>middle){
                right->keys.push_back(temp->keys[i]);
                right->branches.push_back(temp->branches[i]);
            }
        }
        right->branches.push_back(temp->branches[i]);

        if(temp->leaf){
            left->leaf=right->leaf=true;
        }

        if(temp->root){
            temp->keys.clear();
            temp->branches.clear();
            temp->leaf=false;
            parent=temp;
        }
        else{
            destroy=temp;
            parent=temp->parent;
            for(int i=0;i<parent->branches.size(); i++)
                if(parent->branches[i] == temp)parent->branches.erase(parent->branches.begin()+i);
            delete(destroy);
        }
        parent->keys.push_back(tempData);
        sort(parent->keys.begin(),parent->keys.end(),compareVec);
        left->parent=right->parent=parent;
        parent->branches.push_back(left);
        parent->branches.push_back(right);
        sort(parent->branches.begin(),parent->branches.end(),compareNode);

        temp=parent;
    }while(temp->overFull() || !temp->root);
}

// DONE
void addKey(Node* root,Data* data){
    Node* temp=root;
    if(!temp->isFull() && temp->leaf){
        if(temp->keys.empty())
            //temp->branches.push_back(NULL);
        temp->keys.push_back(data);
        //temp->branches.push_back(NULL);
        sort(temp->keys.begin(),temp->keys.end(),compareVec);
    }
    else {
        while(!temp->leaf){
            for(int i=0; i< temp->keys.size(); i++){
                if( temp->keys[i]->getValue() > data->getValue()){
                    temp=temp->branches[i];
                    break;
                }
                else if( i == temp->keys.size()-1 && temp->keys[i]->getValue() < data->getValue()){
                    temp=temp->branches[i+1];
                    break;
                }
            }   
        }
        temp->keys.push_back(data);
        //temp->branches.push_back(NULL);
        sort(temp->keys.begin(),temp->keys.end(),compareVec);

        if(temp->overFull())
            refraction(temp,data);
    }
}

// TODO
void compression(){

}

// TODO
void deleteKey(){

}

// TODO
void printTree(Node* root){

}
// TODO test adding and writting
int main(){
    int m = 0;
    Data* dat;
    while( m < 3 || m > 10){
        cout << "Input node size: ";
        cin >>  m;
        if(m < 3 || m > 10) cout << "Node size is out of range. Size should be between 3 and 10." << endl;
    }
    Node* tree = new Node(m);
    tree->root=tree->leaf=true;
    addKey(tree,new Data(3));
    addKey(tree,new Data(2));
    addKey(tree,new Data(7));
    addKey(tree,new Data(5));
    addKey(tree,new Data(1));
    addKey(tree,new Data(0));
    addKey(tree,new Data(4));
    addKey(tree,new Data(6));
    addKey(tree,new Data(8));
    cout<<*tree;
    cout<<endl;
    cout<<*tree->branches[0];
    cout<<*tree->branches[1];
    return 0;
}