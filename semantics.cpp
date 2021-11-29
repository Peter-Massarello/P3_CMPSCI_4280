#include "semantics.hpp"
using namespace std;

vector<string> stack;
int globalOffset = 0;
bool inGlobal = true;

void staticSemantics(Node* &tree) {
    cout << "in static semantics" << endl;
    int level = 0;
    buildStack(tree, level);

    cout << globalOffset << endl;
}

void checkForDuplicates(string variableString) {
    if (find(stack.begin(), stack.end(), variableString) != stack.end())
        error();
    else return;
}

void addIdToStack(Node* &tree, int level){

    if (tree->tk1->tokenType == IDtk && tree->nodeType == "<VARS>"){
        if (inGlobal) {
            cout << "global offset increased" << endl;
            globalOffset++;
        }
        cout << "found " << tree->tk1->token << endl;
        checkForDuplicates(tree->tk1->token);
        stack.push_back(tree->tk1->token);
    }
    if (tree->tk2->tokenType == IDtk && tree->nodeType == "<VARS>"){
        cout << "found " << tree->tk2->token << endl;
        checkForDuplicates(tree->tk1->token);
        stack.push_back(tree->tk2->token);
    }
    if (tree->tk2->tokenType == IDtk && tree->nodeType == "<VARS>"){
        cout << "found " << tree->tk3->token << endl;
        checkForDuplicates(tree->tk1->token);
        stack.push_back(tree->tk3->token);
    }
}

void buildStack(Node* &tree, int level) {
    if (tree == NULL) return;

    if (tree->nodeType == "<BLOCK>") inGlobal = false;

    addIdToStack(tree, level);

    //subtrees
    buildStack(tree->child1, level+1);  

    //subtrees
    buildStack(tree->child2, level+1);  

    //subtrees
    buildStack(tree->child3, level+1);  

    //subtrees
    buildStack(tree->child4, level+1);  

    //subtrees
    buildStack(tree->child5, level+1);  

}

void push() {

}

void pop() {

}

void error() {
    cout << "double declaration" << endl;
    exit(0);
}