#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <regex>

using namespace std;
// TODO check privacy of classes
class Account
{
public:
    string CA_ID, CA_B_ID, CA_C_ID,
        CA_NAME, CA_TAX_ST, CA_BAL;
    Account(string line)
    {
        CA_ID = line.substr(0, line.find('|'));
        line = line.substr(line.find('|') + 1);
        CA_B_ID = line.substr(0, line.find('|'));
        line = line.substr(line.find('|') + 1);
        CA_C_ID = line.substr(0, line.find('|'));
        line = line.substr(line.find('|') + 1);
        CA_NAME = line.substr(0, line.find('|'));
        line = line.substr(line.find('|') + 1);
        CA_TAX_ST = line.substr(0, line.find('|'));
        line = line.substr(line.find('|') + 1);
        CA_BAL = line.substr(0, line.find('|'));
        line = line.substr(line.find('|') + 1);
    }
    friend ostream &operator<<(ostream &os, const Account *acc)
    {
        return os << acc->CA_ID << "|" << acc->CA_C_ID << "|" << acc->CA_TAX_ST << "|" << acc->CA_BAL;
    }
};

// TODO check privacy
class Data
{
private:
    int value;

public:
    vector<Account *> accounts;
    Data(Account *acc)
    {
        accounts.push_back(acc);
        value = atoi(acc->CA_C_ID.substr(acc->CA_C_ID.length() - 4).c_str());
    };
    int getValue() { return value; }
    void pushAcc(Account *acc)
    {
        accounts.push_back(acc);
    }
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

// DONE
bool compareVec(Data *d1, Data *d2)
{
    return d1->getValue() < d2->getValue();
}

// DONE
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
void insertCAKey(Node *temp, Data *data)
{
    bool added = false;
    for (int i = 0; i < temp->keys.size(); i++)
        if (data->getValue() == temp->keys[i]->getValue())
        {
            temp->keys[i]->accounts.push_back(data->accounts.back());
            added = true;
            delete data;
        }
    if (!added)
    {
        temp->keys.push_back(data);
        sort(temp->keys.begin(), temp->keys.end(), compareVec);
    }
}

// DONE
void addKey(Node *root, Data *data)
{
    Node *temp = root;
    if (!temp->isFull() && temp->leaf)
    {
        insertCAKey(temp, data);
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
        insertCAKey(temp, data);
        if (temp->overFull())
            refraction(temp, data);
    }
}

// DONE
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
        { // having right one
            host = parent->branches[i + 1];
            host->keys.insert(host->keys.begin(), parent->keys.back());
            host->branches.insert(host->branches.begin(), branch);
            branch->parent = host;
            parent->keys.erase(parent->keys.end() - 1);
            parent->branches.erase(parent->branches.begin() + i);
            destroy = temp;
            temp = parent;
            delete destroy;
        } // not having right one
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
Node *findNode(Node *root, int data, int &numstep)
{
    Node *temp = root;
    bool found = false;
    int cnt = 0;
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
                if (!temp->leaf)
                {
                    temp = temp->branches[i + 1];
                    cnt++;
                }
                else
                    return NULL;
                break;
            }
            else if (temp->keys[i]->getValue() > data)
            {
                if (!temp->leaf)
                {
                    temp = temp->branches[i];
                    cnt++;
                }
                else
                    return NULL;
                break;
            }
        }
    }

    numstep = cnt;
    return temp;
}

// TODO unisti izabrane cvorove
void deleteKey(Node *&root, int data)
{
    int i;
    Node *parent, *temp = findNode(root, data, i);
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

// DONE
Data *findKey(Node *temp, int data)
{
    Data *found = NULL;
    if (temp != NULL)
        for (int i = 0; i < temp->keys.size(); i++)
        {
            if (temp->keys[i]->getValue() == data)
            {
                found = temp->keys[i];
                break;
            }
        }
    return found;
}

// TODO create menu
int main()
{
    int m = 0, keyValue, numStep = 0;
    Data *dataNode;
    Node *tree, *temp;
    string line, userID, userData, userDataFinal;
    while (m < 3 || m > 10)
    {
        cout << "Input node size: ";
        cin >> m;
        if (m < 3 || m > 10)
            cout << "Node size is out of range. Size should be between 3 and 10." << endl;
    }

    tree = new Node(m);
    tree->root = tree->leaf = true;
    // DONE Creating tree
    ifstream customerAcc("CustomerAccount250.txt");

    if (customerAcc.is_open())
    {

        while (getline(customerAcc, line))
        {
            addKey(tree, new Data(new Account(line)));
        }
        customerAcc.close();
    }
    else
        cout << "Unable to open file";

    // DONE searching for customer
    cout << endl
         << "Input C_ID of user:" << endl;
    cin >> userID;
    ifstream customerList("Customer.txt");

    if (customerList.is_open())
    {
        while (getline(customerList, line))
        { // TODO if user doesnt exist
            if (!userID.compare(line.substr(0, line.find('|'))))
            {
                userData = line;
            }
        }
        customerAcc.close();
    }
    else
        cout << "Unable to open file";
    // DONE creating file
    userDataFinal = userData.substr(0, userData.find('|') + 1);
    userData = userData.substr(userData.find('|') + 1);
    userDataFinal.append(userData.substr(0, userData.find('|') + 1));
    userData = userData.substr(userData.find('|') + 1);
    userDataFinal.append(userData.substr(0, userData.find('|') + 1));
    userData = userData.substr(userData.find('|') + 1);
    userDataFinal.append(userData.substr(0, userData.find('|') + 1));
    ofstream outputFile("output.txt");
    keyValue = atoi(userID.substr(userID.length() - 4).c_str());
    temp = findNode(tree, keyValue, numStep);
    dataNode = findKey(temp, keyValue);
    if (dataNode != NULL)
    {
        for (int i = 0; i < dataNode->accounts.size(); i++)
        {
            cout << "Number of steps:" << numStep << endl;
            outputFile << userDataFinal << dataNode->accounts[i] << '\n';
        }
    }
    else
    {
        cout << "Number of steps:" << numStep << endl;
        outputFile << userDataFinal << "null|null|null|null" << '\n';
    }
    outputFile.close();
    // DONE deleting
    cout << "Input user for deleting";
    cin >> userID;
    keyValue = atoi(userID.substr(userID.length() - 4).c_str());
    deleteKey(tree, keyValue);

    temp = findNode(tree, keyValue, numStep);
    if (temp == NULL)
        cout << "Data doesnt exist. Number of steps: " << numStep << endl;
    else
        cout << "Deleting is not working!" << endl;

    return 0;
}
// switch (expression)
// {
// case x:
//     // code block
//     break;
// case y:
//     // code block
//     break;
// default:
//     // code block
// }