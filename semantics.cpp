#include "semantics.hpp"
using namespace std;

vector<string> stack;
int globalOffset = 0;
int localVarsCount = 0;
bool inGlobal = true;

void staticSemantics(Node* &tree) {
    int level = 0;

    cout << "Checking static semantics..." << endl;

    buildStack(tree, level);

    clearStack();

    cout << "Program clear!" << endl;
}

void clearStack() {
    for (int i = stack.size(); i > 0; i--) {
        pop();
    }
}

int find(string token) {
    for (int i = stack.size()-1; i >= globalOffset + localVarsCount; i--){
        if (stack.at(i) == token) {
            return (stack.size()) - i;
        }
    }
    for (int i = globalOffset - 1; i >= 0; i--) {
        if (stack.at(i) == token) {
            return -1;
        }
    }
    return -1;
}

bool checkMissing(string token) {
    for (int i = stack.size()-1; i >= 0; i--){
        if (stack.at(i) == token) {
            return true;
        }
    }
    return false;
}

void clearLocalStack() {
    for (int i = stack.size(); i >= globalOffset + localVarsCount; i--){
        stack.pop_back();
    }
    localVarsCount = 0;
}

void getVars(Node* &tree) {
    if (tree->tk1->tokenType != IDtk) return;
    if (tree->nodeType != "<VARS>") return;

    int notFound = find(tree->tk1->token);

    if (notFound == -1) {
        push(tree->tk1->token);
        if (inGlobal) globalOffset++; else localVarsCount++;
    } else {
        doubleDeclarationError(tree->tk1->token);
    }

    if (tree->child1 != NULL) getVars(tree->child1);
}

void addBlockToStack(Node* &tree) {
    getVars(tree->child1);

    if (tree->child2 != NULL) buildStack(tree->child2, 0);

    clearLocalStack();
}

void buildStack(Node* &tree, int level) {
    if (tree->nodeType == "<PROGRAM>") {
        getVars(tree->child1);
        inGlobal = false;
        buildStack(tree->child2, 0);
    } else if (tree->nodeType == "<BLOCK>") {
        addBlockToStack(tree);
    } 
    else {
        string tk1 = tree->tk1->token;
        string tk2 = tree->tk2->token;
        string tk3 = tree->tk3->token;

        if (tree->tk1->tokenType == IDtk && checkMissing(tk1) == false) missingDeclarationError(tk1);
        if (tree->tk2->tokenType  == IDtk && checkMissing(tk1) == false) missingDeclarationError(tk2);
        if (tree->tk3->tokenType  == IDtk && checkMissing(tk1) == false) missingDeclarationError(tk3);

        //subtrees
        if (tree->child1 != NULL) buildStack(tree->child1, level+1);

        //subtrees
        if (tree->child2 != NULL) buildStack(tree->child2, level+1);

        //subtrees
        if (tree->child3 != NULL) buildStack(tree->child3, level+1);

        //subtrees
        if (tree->child4 != NULL) buildStack(tree->child4, level+1);

        //subtrees
        if (tree->child5 != NULL) buildStack(tree->child5, level+1);
    }
}

void pop() {
    stack.pop_back();
}

void push(string variable) {
    stack.push_back(variable);
    //   for (auto it = stack.rbegin(); it != stack.rend(); it++)
    //     cout << "current stack " <<  *it << endl;
}

void doubleDeclarationError(string variable) {
    cout << "STATIC SEMANTICS ERROR: Double declaration of " << variable << endl;
    exit(0);
}

void missingDeclarationError(string variable) {
    cout << "STATIC SEMANTICS ERROR: Missing declaration of " << variable << endl;
    exit(0);
}
