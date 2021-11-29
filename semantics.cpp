#include "semantics.hpp"
using namespace std;

vector<string> variables;
int globalOffset = 0;

void staticSemantics(Node* &tree) {
    cout << "in static semantics" << endl;
    int level = 0;
    buildStack(tree, level);
}

void addIdToStack(Node* &tree, int level){
    if (tree->tk1->tokenType == IDtk && tree->nodeType == "<VARS>"){
        cout << "found " << tree->tk1->token << endl;
        variables.push_back(tree->tk1->token);
    }
    if (tree->tk2->tokenType == IDtk && tree->nodeType == "<VARS>"){
        cout << "found " << tree->tk2->token << endl;
        variables.push_back(tree->tk2->token);
    }
    if (tree->tk2->tokenType == IDtk && tree->nodeType == "<VARS>"){
        cout << "found " << tree->tk3->token << endl;
        variables.push_back(tree->tk3->token);
    }
}

void buildStack(Node* &tree, int level) {
    if (tree == NULL) return;

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

int find() {
    return 1;
}

void push() {

}

void pop() {

}