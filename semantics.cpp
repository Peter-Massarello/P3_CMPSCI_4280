#include "semantics.hpp"
using namespace std;

vector<string> stack;
int globalOffset = 0;
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

void checkLocalForDuplicates(string variableString) {
    for (int i = stack.size(); i > globalOffset; i--){
        if (stack.at(i-1) == variableString)
            doubleDeclarationError(variableString);
    }
}

void checkGlobalForDuplicates(string variableString) {
    if (find(stack.begin(), stack.end(), variableString) != stack.end())
        doubleDeclarationError(variableString);
    else return;
}

int find(string token) {
    for (int i = stack.size(); i > 0; i--){
        if (stack.at(i-1) == token) {
            return (stack.size()) - i;
        }
    }
    return -1;
}

void addIdToStack(Node* &tree, int level){
    string tk1 = tree->tk1->token;
    string tk2 = tree->tk2->token;
    string tk3 = tree->tk3->token;

    if (tree->tk1->tokenType == IDtk){
        if (tree->nodeType == "<VARS>"){
            if (inGlobal) {
                globalOffset++;
                checkGlobalForDuplicates(tk1);
                push(tk1);
            } else {
                checkLocalForDuplicates(tk1);
                push(tk1);
            }
        } else {
            int stackCheck = find(tk1);
            if (stackCheck == -1) missingDeclarationError(tk1);
        }
    }
    if (tree->tk2->tokenType == IDtk){
        if (tree->nodeType == "<VARS>"){
            if (inGlobal) {
                    globalOffset++;
                    checkGlobalForDuplicates(tk2);
                    push(tk2);
                } else {
                    checkLocalForDuplicates(tk2);
                    push(tk2);
                }
        } else {
            int stackCheck = find(tk2);
            if (stackCheck == -1) missingDeclarationError(tk2);
        }
    }
    if (tree->tk3->tokenType == IDtk && tree->nodeType == "<VARS>"){
        if (tree->nodeType == "<VARS>"){
            if (inGlobal) {
                    globalOffset++;
                    checkGlobalForDuplicates(tk3);
                    push(tk3);
                } else {
                    checkLocalForDuplicates(tk3);
                    push(tk3);
                }
        } else {
            int stackCheck = find(tk3);
            if (stackCheck == -1) missingDeclarationError(tk3);
        }
    }
}

void clearLocalStack() {
    for (int i = stack.size(); i > globalOffset; i--){
        stack.pop_back();
    }
}

void buildStack(Node* &tree, int level) {
    if (tree == NULL) return;

    if (tree->nodeType == "<BLOCK>") {
        //clearLocalStack();
        inGlobal = false;
    }

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

void pop() {
    stack.pop_back();
}

void push(string variable) {
    stack.push_back(variable);
}

void doubleDeclarationError(string variable) {
    cout << "STATIC SEMANTICS ERROR: Double declaration of " << variable << endl;
    exit(0);
}

void missingDeclarationError(string variable) {
    cout << "STATIC SEMANTICS ERROR: Missing declaration of " << variable << endl;
    exit(0);
}