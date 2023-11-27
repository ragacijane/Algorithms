#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

class Data
{
private:
    int value;

public:
    Data(int x)
    {
        value = x;
    };
    int getValue() { return value; }
};
// TODO get min keys max keys based on root or leaf
class Node
{
private:
    int minKeys, maxKeys, minBranches, maxBranches;

public:
    bool leaf, root;
    vector<Data *> keys;
    vector<Node *> branches;
    Node *parent;
    Node(int m)
    {
        maxBranches = m;
        maxKeys = m - 1;
        minKeys = ceil(m * 1.0 / 2) - 1;
        minBranches = m / 2 + 1;
        // branches.push_back(NULL);
        leaf = root = false;
    }
    bool overFull() { return (keys.size() > maxKeys) ? true : false; }
    bool isFull() { return (keys.size() < maxKeys) ? false : true; }
    bool isEnoughKeys() { return keys.size() >= minKeys; }
    bool canBorrow() { return keys.size() > minKeys; }
    int getNodeSize() { return maxBranches; }
    friend ostream &operator<<(ostream &os, const Node &n)
    {
        int i;
        os << "(";
        for (i = 0; i < n.maxBranches - 1; i++)
        {
            if (i < n.keys.size())
                os << setw(2) << n.keys[i]->getValue();
            else
                os << setw(2) << " ";

            if (i == n.maxBranches - 2)
                os << ")";
            else
                os << "|";
        }
        return os;
    }
};

bool compareVec(Data *d1, Data *d2)
{
    return d1->getValue() < d2->getValue();
}

bool compareNode(Node *n1, Node *n2)
{
    if (n1 != nullptr && n2 != nullptr)
        return n1->keys[0]->getValue() < n2->keys[0]->getValue();
    else
        return true;
}

// DONE
void refraction(Node *temp, Data *data)
{
    int i;
    Node *left, *right, *parent, *destroy;
    do
    {
        left = new Node(temp->getNodeSize());
        right = new Node(temp->getNodeSize());
        Data *tempData;

        int middle = (temp->keys.size() - 1) / 2;
        tempData = temp->keys[middle];
        // splitting overfull node
        for (i = 0; i < temp->keys.size(); i++)
        {
            if (i < middle)
            {
                left->keys.push_back(temp->keys[i]);
                if (temp->branches.size() > 0)
                    left->branches.push_back(temp->branches[i]);
            }
            if (i == middle)
                if (temp->branches.size() > 0)
                    left->branches.push_back(temp->branches[i]);
            if (i > middle)
            {
                right->keys.push_back(temp->keys[i]);
                if (temp->branches.size() > 0)
                    right->branches.push_back(temp->branches[i]);
            }
        }
        if (temp->branches.size() > 0)
            right->branches.push_back(temp->branches[i]);

        if (temp->leaf)
        {
            left->leaf = right->leaf = true;
        }
        // setting up parents
        if (left->branches.size() > 0)
            for (int i = 0; i < left->branches.size(); i++)
                left->branches[i]->parent = left;
        if (right->branches.size() > 0)
            for (int i = 0; i < right->branches.size(); i++)
                right->branches[i]->parent = right;

        if (temp->root)
        {
            temp->keys.clear();
            temp->branches.clear();
            temp->leaf = false;
            parent = temp;
        }
        else
        {
            destroy = temp;
            parent = temp->parent;
            for (int i = 0; i < parent->branches.size(); i++)
                if (parent->branches[i] == temp)
                    parent->branches.erase(parent->branches.begin() + i);
            // delete (destroy);
        }
        parent->keys.push_back(tempData);
        sort(parent->keys.begin(), parent->keys.end(), compareVec);
        left->parent = right->parent = parent;
        parent->branches.push_back(left);
        parent->branches.push_back(right);
        sort(parent->branches.begin(), parent->branches.end(), compareNode);

        temp = parent;
    } while (temp->overFull());
}

// DONE
void addKey(Node *root, Data *data)
{
    Node *temp = root;
    if (!temp->isFull() && temp->leaf)
    {
        // if(temp->keys.empty())
        // temp->branches.push_back(NULL);
        temp->keys.push_back(data);
        // temp->branches.push_back(NULL);
        sort(temp->keys.begin(), temp->keys.end(), compareVec);
    }
    else
    {
        while (!temp->leaf)
        {
            for (int i = 0; i < temp->keys.size(); i++)
            {
                if (temp->keys[i]->getValue() > data->getValue())
                {
                    temp = temp->branches[i];
                    break;
                }
                else if (i == temp->keys.size() - 1 && temp->keys[i]->getValue() < data->getValue())
                {
                    temp = temp->branches[i + 1];
                    break;
                }
            }
        }
        temp->keys.push_back(data);
        // temp->branches.push_back(NULL);
        sort(temp->keys.begin(), temp->keys.end(), compareVec);

        if (temp->overFull())
            refraction(temp, data);
    }
}

// TODO
Node *compression(Node *temp)
{
    int i;
    Node *parent, *branch, *destroy, *host;
    do
    {
        parent = temp->parent;
        branch = temp->branches[0];
        for (i = 0; i < parent->branches.size(); i++)
            if (parent->branches[i] == temp)
                break;
        if (i + 1 < parent->branches.size())
        { // ima desnog brata TODO obrisi temp i njegovu povezanost na parenta
            host = parent->branches[i + 1];
            host->keys.insert(host->keys.begin(), parent->keys.back());
            host->branches.insert(host->branches.begin(), branch);
            branch->parent = host;
            parent->keys.erase(parent->keys.end() - 1);
            parent->branches.erase(parent->branches.begin() + i);
            destroy = temp;
            temp = parent;
        } // ako nema desnog brata
        else
        {
            host = parent->branches[i - 1];
            host->keys.push_back(parent->keys.back());
            host->branches.push_back(branch);
            branch->parent = host;
            parent->keys.erase(parent->keys.end() - 1);
            parent->branches.erase(parent->branches.begin() + i);
            destroy = temp;
            temp = parent;
        }
    } while (!temp->root);
    host = temp->branches[0];
    host->root = true;
    return host;
}

// DONE
Node *swapKeys(Node *curent, int data)
{
    int i;
    Node *temp = curent;
    Data *tempData;
    for (i = 0; i < temp->keys.size(); i++)
        if (temp->keys[i]->getValue() == data)
        {
            temp = temp->branches[i + 1];
            break;
        }

    while (!temp->leaf)
        temp = temp->branches[0];
    tempData = temp->keys[0];
    temp->keys[0] = curent->keys[i];
    curent->keys[i] = tempData;
    return temp;
}

// DONE
Node *findNode(Node *root, int data)
{
    Node *temp = root;
    bool found = false;
    while (!found)
    {
        for (int i = 0; i < temp->keys.size(); i++)
        {
            if (temp->keys[i]->getValue() == data)
            {
                found = true;
                break;
            }
            else if (i == temp->keys.size() - 1 && temp->keys[i]->getValue() < data)
            {
                temp = temp->branches[i + 1];
                break;
            }
            else if (temp->keys[i]->getValue() > data)
            {
                temp = temp->branches[i];
                break;
            }
        }
    }
    return temp;
}

// TODO unisti izabrane cvorove
void deleteKey(Node *&root, int data)
{
    int i;
    Node *parent, *temp = findNode(root, data);
    // DONE ako nije u listu
    if (!temp->leaf)
        temp = swapKeys(temp, data);
    // obrisi TODO vidi da li treba dealocirati data
    for (i = 0; i < temp->keys.size(); i++)
    {
        if (temp->keys[i]->getValue() == data)
            temp->keys.erase(temp->keys.begin() + i);
    }
    if (!temp->isEnoughKeys())
    { // 2. ako nema dovoljno kljuceva
        if (!temp->root)
        { // ako nije koren
            parent = temp->parent;
            for (i = 0; i < parent->branches.size(); i++)
                if (parent->branches[i] == temp)
                    break;
            // ako moze da pozajmi
            if (i + 1 < parent->branches.size() && parent->branches[i + 1]->canBorrow())
            { // DONE pozajmljuje od desnog
                temp->keys.push_back(parent->keys[i]);
                parent->keys[i] = parent->branches[i + 1]->keys[0];
                parent->branches[i + 1]->keys.erase(parent->branches[i + 1]->keys.begin());
                sort(temp->keys.begin(), temp->keys.end(), compareVec);
            }
            else if (i - 1 >= 0 && parent->branches[i - 1]->canBorrow())
            { // DONE pozajmljuje od levog
                temp->keys.push_back(parent->keys[i - 1]);
                parent->keys[i - 1] = parent->branches[i - 1]->keys.back();
                parent->branches[i - 1]->keys.erase(parent->branches[i - 1]->keys.end() - 1);
                sort(temp->keys.begin(), temp->keys.end(), compareVec);
            }
            else if (i + 1 < parent->branches.size())
            { // ako ima desnog brata TODO
                temp->keys.push_back(parent->keys[i]);
                temp->keys.push_back(parent->branches[i + 1]->keys.back());
                parent->branches.erase(parent->branches.begin() + i + 1);
                parent->keys.erase(parent->keys.begin() + i);
                // sort(temp->keys.begin(),temp->keys.end(),compareVec);
                if (parent->keys.empty())
                {
                    cout << "Poziva se prelamanje";
                    root = compression(parent);
                }
            }
            else
            { // ako nema desnog brata TODO
                parent->branches[i - 1]->keys.push_back(parent->keys[i - 1]);
                parent->keys.erase(parent->keys.end() - 1);
                parent->branches.erase(parent->branches.begin() + i);
                // sort(temp->keys.begin(),temp->keys.end(),compareVec);
                if (parent->keys.empty())
                {
                    cout << "Poziva se prelamanje";
                    root = compression(parent);
                }
            }
        }
        else
        {
            // TODO ako je koren
        }
    }
}

// TODO
void printTree(Node *root)
{
}

// TODO test deleting
int main()
{
    int m = 0;
    Data *dat;
    while (m < 3 || m > 10)
    {
        cout << "Input node size: ";
        cin >> m;
        if (m < 3 || m > 10)
            cout << "Node size is out of range. Size should be between 3 and 10." << endl;
    }
    Node *tree = new Node(m);
    tree->root = tree->leaf = true;
    addKey(tree, new Data(3));
    addKey(tree, new Data(2));
    addKey(tree, new Data(7));
    addKey(tree, new Data(5));
    addKey(tree, new Data(1));
    addKey(tree, new Data(0));
    addKey(tree, new Data(4));
    addKey(tree, new Data(6));
    addKey(tree, new Data(8));
    addKey(tree, new Data(9));
    addKey(tree, new Data(10));
    addKey(tree, new Data(11));
    // deleteKey(tree,4);
    // deleteKey(tree,8);
    // deleteKey(tree,11);
    // deleteKey(tree,6);
    deleteKey(tree, 5);
    deleteKey(tree, 10);
    deleteKey(tree, 11);
    deleteKey(tree, 9);
    addKey(tree, new Data(10));
    addKey(tree, new Data(11));
    cout << *tree;
    cout << endl;
    cout << *tree->branches[0];
    cout << *tree->branches[1];
    cout << *tree->branches[2];
    return 0;
}