#include "BinaryTree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

PokeTree::PokeTree()
{
    nil = new PokeNode(0,"NIL",0,0,"NIL","NIL","NIL","NIL","NIL","NIL");
    root = nil;
    nil->isRed = false;
    nil->leftChild = nil;
    nil->rightChild = nil;
}

PokeTree::~PokeTree()
{
    if(root != nil){
        DeleteAll(root);
    }

    delete nil;

}

void PokeTree::addPokeNode(int in_id, std::string in_name, int in_height, int in_weight, string in_type1, string in_type2
             ,string in_ability, string in_evobase, string in_evomid, string in_evotop)
{
    PokeNode *y = nil;
    PokeNode *x = root;
    PokeNode *z = new PokeNode(in_id, in_name,in_height,in_weight,in_type1,in_type2,in_ability,in_evobase,in_evomid,in_evotop);

    if(root == nil){
        root = z;
        z->parent = nil;
    }else{
        while(x != nil){
            y = x;
            if(z->name.compare(x->name) < 0){
                x = x->leftChild ;
            }else{
                x = x->rightChild;
            }
        }
        z->parent = y;

        if(z->name.compare(y->name) < 0)
            y->leftChild  = z;
        else
            y->rightChild = z;
    }

    z->leftChild = nil;
    z->rightChild = nil;
    z->isRed = true;
    z->id = in_id;
    z->name = in_name;
    z->height = in_height;
    z->weight = in_weight;
    z->type1 = in_type1;
    z->type2 = in_type2;
    z->ability = in_ability;
    z->evobase = in_evobase;
    z->evomid = in_evomid;
    z->evotop = in_evotop;

    //cout<<"adding: "<<z->name<<endl;
    //cout<<"new: "<<z->name<<endl;
    //cout<<"type1: "<<z->type1<<endl;
    //cout<<"parent: "<<z->parent->name<<endl;


    rbAddFixup(z);

}

void PokeTree::rbAddFixup(PokeNode * z){

    PokeNode *y;
    y = new PokeNode;
    y->leftChild = nil;
    y->rightChild = nil;
    y->parent = nil;
    while(z->parent->isRed == true){
        if(z->parent == z->parent->parent->leftChild){
            y = z->parent->parent->rightChild;
            if(y->isRed == true){
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            }else{
                if(z == z->parent->rightChild){
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                rightRotate(z->parent->parent);
            }
        }else{
            y = z->parent->parent->leftChild;
            if(y->isRed == true){
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            }else{
                if(z == z->parent->leftChild){
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->isRed = false;


}

void PokeTree::leftRotate(PokeNode * x){

    PokeNode *y;
    y = new PokeNode;
    y->parent = nil;
    y->leftChild = nil;
    y->rightChild = nil;

    y = x->rightChild;
    x->rightChild = y->leftChild;

    if(y->leftChild != nil){
        y->leftChild->parent = x;
    }

    y->parent = x->parent;

    if(x->parent == nil){
        root = y;

    }else if(x == x->parent->leftChild){
        x->parent->leftChild = y;

    }else{
        x->parent->rightChild = y;
    }

    y->leftChild = x;
    x->parent = y;
}

void PokeTree::rightRotate(PokeNode * y){

    PokeNode *x;
    x = new PokeNode;
    x->parent = nil;
    x->leftChild = nil;
    x->rightChild = nil;

    x = y->leftChild;
    y->leftChild = x->rightChild;
    if(x->rightChild != nil){
        x->rightChild->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == nil){
        root = x;
    }else if(y == y->parent->leftChild){
        y->parent->leftChild = x;
    }else{
        y->parent->rightChild = x;
    }
    x->rightChild = y;
    y->parent = x;

}

void PokeTree::printPokeInventory(){
    printPokeInventory(root);
}

void PokeTree::printPokeInventory(PokeNode * node){

    if(node->leftChild!=nil){
        printPokeInventory(node->leftChild);
    }
    cout<<node->name<<endl;
    if(node->rightChild!=nil){
        printPokeInventory(node->rightChild);
    }
}

void PokeTree::searchPokeTree(string name){
    PokeNode *x;
    x = root;
    while(x != nil && x->name != name){
        if(x->name.compare(name) > 0){
            x = x->leftChild;
        }else{
            x = x->rightChild;
        }
    }
    if(x->name == name){
        cout<<"\nName: "<<x->name<<endl;
        cout<<"Pokedex Number: "<<x->id<<endl;
        cout<<"Height: "<<x->height<<endl;
        cout<<"Weight: "<<x->weight<<endl;
        cout<<"Primary Ability: "<<x->ability<<endl;
        cout<<"Primary Type: "<<x->type1<<endl;
        cout<<"Secondary Type: "<<x->type2<<endl;
        if(x->evobase == "none"){
            cout<<"This pokemon does not evolve"<<endl;
        }else{
            if(x->evotop == "none"){
                cout<<"Unevolved: "<<x->evobase<<endl;
                cout<<"Final Evolution: "<<x->evomid<<endl;
            }else{
                cout<<"Unevolved: "<<x->evobase<<endl;
                cout<<"First Evolution: "<<x->evomid<<endl;
                cout<<"Final Evolution: "<<x->evotop<<endl;
            }
        }
    }else{
        cout<<"Pokemon not found"<<endl;
    }
}

int PokeTree::countPokeNodes(){
    nodeCount = 0;
    countPokeNodes(root);
    cout<<nodeCount<<endl;

}

int PokeTree::countPokeNodes(PokeNode *node){

    if(node->leftChild!=nil){
        countPokeNodes(node->leftChild);
    }
    nodeCount++;
    if(node->rightChild!=nil){
        countPokeNodes(node->rightChild);
    }
}

PokeNode* PokeTree::searchPokeTree(PokeNode* node, string name){

    PokeNode *x;
    x = root;
    while(x != nil && x->name != name){
        if(x->name.compare(name) > 0){
            x = x->leftChild;
        }else{
            x = x->rightChild;
        }
    }

    return x;
}

void PokeTree::deletePokeNode(string name){

    PokeNode *z;
    z = searchPokeTree(root,name);

    if(z == nil){
        cout<<"Pokemon not found"<<endl;
    }else{

        PokeNode *y;
        y = new PokeNode;
        y->leftChild = nil;
        y->rightChild = nil;
        y->parent = nil;
        PokeNode *x;
        x = new PokeNode;
        x->leftChild = nil;
        x->rightChild = nil;
        x->parent = nil;
        bool origColor;

        y = z;
        origColor = y->isRed;

        if(z->leftChild == nil){
            x = z->rightChild;
            rbTransplant(z, z->rightChild);

        }else if(z->rightChild == nil){
            x = z->leftChild;
            rbTransplant(z, z->leftChild);

        }else{
            y = treeMinimum(z->rightChild);
            origColor = y->isRed;
            x = y->rightChild;

            if(y->parent == z){
                x->parent = y;

            }else{
                rbTransplant(y, y->rightChild);
                y->rightChild = z->rightChild;
                y->rightChild->parent = y;

            }

            rbTransplant(z,y);
            y->leftChild = z->leftChild;
            y->leftChild->parent = y;
            y->isRed = z->isRed;
        }

        delete z;

        if(origColor == false && x != nil){
            rbDeleteFixup(x);
        }

    }

}

PokeNode* PokeTree::treeMinimum(PokeNode * x){
    while(x->leftChild != nil){
        x = x->leftChild;
    }
    return x;
}

void PokeTree::rbDeleteFixup(PokeNode * node){

    PokeNode * w = NULL;

    // Now we restore the red-black properties.
    while((node != root) && (node->isRed == false)){
        // If we are a left child
        if(node == node->parent->leftChild){
            w = node->parent->rightChild;

            // If helper is red
            if(w->isRed){
                w->isRed = false;
                node->parent->isRed = true;
                leftRotate(node->parent);
                w = node->parent->rightChild;
            }

            // If helper's children are both black
            if(w->leftChild->isRed == false && w->rightChild->isRed == false){
                w->isRed = true;
                node = node->parent;
            }else{
                if(w->rightChild->isRed == false){
                    // case 3
                    w->leftChild->isRed = false;
                    w->isRed = true;
                    rightRotate(w);
                    w = node->parent->rightChild;
                }
                // case 4
                w->isRed = node->parent->isRed;
                node->parent->isRed = false;
                w->rightChild->isRed = false;
                leftRotate(node->parent);
                node = root;
            }
        }

        // If we are a right child
        else{

            // helper is the left child
            w = node->parent->leftChild;
            // If helper is red
            if(w->isRed){
                w->isRed = false;
                node->parent->isRed = true;
                rightRotate(node->parent);
                w = node->parent->leftChild;
            }

            // If helper's children are both black
            if(w->leftChild->isRed == false && w->rightChild->isRed == false){
                w->isRed = true;
                node = node->parent;
            }

            else{
                if(w->leftChild->isRed == false){
                    // case 3
                    w->rightChild->isRed = false;
                    w->isRed = true;
                    leftRotate(w);
                    w = node->parent->leftChild;
                }

                // case 4
                w->isRed = node->parent->isRed;
                node->parent->isRed = false;
                w->leftChild->isRed = false;
                rightRotate(node->parent);
                node = root;
            }
        }

    }

    node->isRed = false;
    return;
}

void PokeTree::rbTransplant(PokeNode * u, PokeNode * v){

    if(u->parent == nil){
        root = v;
    }else if(u == u->parent->leftChild){
        u->parent->leftChild = v;
    }else{
        u->parent->rightChild = v;
    }
    //if(v != nil){
        v->parent = u->parent;
    //}
}

bool PokeTree::isValid(){
    bool x = rbValid(root);
    return x;
}

int PokeTree::rbValid(PokeNode * node) // Returns 0 if the tree is invalid, otherwise returns the black node height.
{

    int lh = 0;
    int rh = 0;

    // If we are at a nil node just return 1
    if (node == nil)
        return 1;

    else
    {
        // First check for consecutive red links.
        if (node->isRed)
        {
            if(node->leftChild->isRed || node->rightChild->isRed)
            {
                cout << "This tree contains a red violation" << endl;
                return 0;
            }
        }

        // Check for valid binary search tree.
        if ((node->leftChild != nil && node->leftChild->name.compare(node->name) > 0) || (node->rightChild != nil && node->rightChild->name.compare(node->name) < 0))
        {
            cout << "This tree contains a binary tree violation" << endl;
            return 0;
        }

        // Deteremine the height of left and right children.
        lh = rbValid(node->leftChild);
        rh = rbValid(node->rightChild);

        // black height mismatch
        if (lh != 0 && rh != 0 && lh != rh)
        {
            cout << "This tree contains a black height violation" << endl;
            return 0;
        }

        // If neither height is zero, increment if it if black.
        if (lh != 0 && rh != 0)
        {
                if (node->isRed)
                    return lh;
                else
                    return lh+1;
        }

        else
            return 0;

    }
}

void PokeTree::findType(string type){
    string answer;
    vector<PokeNode> typeList;
    findType(type, root, &typeList);
    for(int i = 0; i < typeList.size(); i++){
        cout<<typeList[i].name<<": list number: "<<i<<endl;
    }

    if(typeList.size() == 0){
        cout<<"\nNo Pokemon have this type"<<endl;
    }else{
        cout<<"\nWould you like to learn more about one of these Pokemon? Y/N?"<<endl;
        getline(cin,answer);
        if(answer == "Y" || answer == "Yes" || answer == "yes" || answer == "y"){
            cout<<"Enter list number: "<<endl;
            getline(cin,answer);
            if(atoi(answer.c_str()) < typeList.size()){
                int i = atoi(answer.c_str());
                cout<<"\nName: "<<typeList[i].name<<endl;
                cout<<"Pokedex Number: "<<typeList[i].id<<endl;
                cout<<"Height: "<<typeList[i].height<<endl;
                cout<<"Weight: "<<typeList[i].weight<<endl;
                cout<<"Primary Ability: "<<typeList[i].ability<<endl;
                cout<<"Primary Type: "<<typeList[i].type1<<endl;
                cout<<"Secondary Type: "<<typeList[i].type2<<endl;
                if(typeList[i].evobase == "none"){
                    cout<<"This pokemon does not evolve"<<endl;
                }else{
                    if(typeList[i].evotop == "none"){
                        cout<<"Unevolved: "<<typeList[i].evobase<<endl;
                        cout<<"Final Evolution: "<<typeList[i].evomid<<endl;
                    }else{
                        cout<<"Unevolved: "<<typeList[i].evobase<<endl;
                        cout<<"First Evolution: "<<typeList[i].evomid<<endl;
                        cout<<"Final Evolution: "<<typeList[i].evotop<<endl;
                    }
                }
            }else{
                cout<<"List number outside of range: "<<endl;
            }
        }
    }


}

void PokeTree::findAbility(string ability){
    string answer;
    vector<PokeNode> abilityList;
    findAbility(ability, root, &abilityList);
    for(int i = 0; i < abilityList.size(); i++){
        cout<<abilityList[i].name<<": list number: "<<i<<endl;
    }

    if(abilityList.size() == 0){
        cout<<"\nNo Pokemon have this ability"<<endl;
    }else{
        cout<<"\nWould you like to learn more about one of these Pokemon? Y/N?"<<endl;
        getline(cin,answer);
        if(answer == "Y" || answer == "Yes" || answer == "yes" || answer == "y"){
            cout<<"Enter list number: "<<endl;
            getline(cin,answer);
            if(atoi(answer.c_str()) < abilityList.size()){
                int i = atoi(answer.c_str());
                cout<<"\nName: "<<abilityList[i].name<<endl;
                cout<<"Pokedex Number: "<<abilityList[i].id<<endl;
                cout<<"Height: "<<abilityList[i].height<<endl;
                cout<<"Weight: "<<abilityList[i].weight<<endl;
                cout<<"Primary Ability: "<<abilityList[i].ability<<endl;
                cout<<"Primary Type: "<<abilityList[i].type1<<endl;
                cout<<"Secondary Type: "<<abilityList[i].type2<<endl;
                if(abilityList[i].evobase == "none"){
                    cout<<"This pokemon does not evolve"<<endl;
                }else{
                    if(abilityList[i].evotop == "none"){
                        cout<<"Unevolved: "<<abilityList[i].evobase<<endl;
                        cout<<"Final Evolution: "<<abilityList[i].evomid<<endl;
                    }else{
                        cout<<"Unevolved: "<<abilityList[i].evobase<<endl;
                        cout<<"First Evolution: "<<abilityList[i].evomid<<endl;
                        cout<<"Final Evolution: "<<abilityList[i].evotop<<endl;
                    }
                }
            }else{
                cout<<"List number outside of range: "<<endl;
            }
        }
    }
}

void PokeTree::findType(string type, PokeNode *node, vector<PokeNode>* typeList){

    if(node->leftChild!=nil){
        findType(type, node->leftChild, typeList);
    }

    if((node->type1 == type) || (node->type2 == type)){
        typeList->push_back(*node);
    }

    if(node->rightChild!=nil){
        findType(type, node->rightChild, typeList);
    }


}

void PokeTree::findAbility(string ability, PokeNode *node, vector<PokeNode>* abilityList){

    if(node->leftChild!=nil){
        findAbility(ability, node->leftChild, abilityList);
    }

    if(node->ability == ability){
        abilityList->push_back(*node);
    }

    if(node->rightChild!=nil){
        findAbility(ability, node->rightChild, abilityList);
    }
}

void PokeTree::DeleteAll(PokeNode * node){

    if(node->leftChild != nil){
        DeleteAll(node->leftChild);
    }
    if(node->rightChild != nil){
        DeleteAll(node->rightChild);
    }

    delete node;
}

