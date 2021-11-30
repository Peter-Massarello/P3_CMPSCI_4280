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

void checkLocalForDuplicates(string variableString) {
    for (int i = stack.size(); i > globalOffset; i--){
        if (stack.at(i-1) == variableString)
            doubleDeclarationError();
    }
}

void checkGlobalForDuplicates(string variableString) {
    if (find(stack.begin(), stack.end(), variableString) != stack.end())
        doubleDeclarationError();
    else return;
}

void checkVariableDeclaration(string variable) {
    cout << "checking " << variable << endl;
    bool foundDec = false;
    for (int i = stack.size(); i > 0; i--){
        if (stack.at(i-1) == variable) {
            cout << "found delcaration of " << variable << endl;
            foundDec = true;
            return;
        } else 
            foundDec = false;
    }

    if (!foundDec) missingDeclarationError(variable);
}

void addIdToStack(Node* &tree, int level){
    if (tree->tk1->tokenType == IDtk){
        if (tree->nodeType == "<VARS>"){
            if (inGlobal) {
                cout << "global offset increased" << endl;
                globalOffset++;
                checkGlobalForDuplicates(tree->tk1->token);
                cout << "found " << tree->tk1->token << endl;
                stack.push_back(tree->tk1->token);
            } else {
                cout << "found " << tree->tk1->token << endl;
                checkLocalForDuplicates(tree->tk1->token);
                stack.push_back(tree->tk1->token);
            }
        } else {
            checkVariableDeclaration(tree->tk1->token);
        }
    }
    if (tree->tk2->tokenType == IDtk){
        if (tree->nodeType == "<VARS>"){
            if (inGlobal) {
                    cout << "global offset increased" << endl;
                    globalOffset++;
                    checkGlobalForDuplicates(tree->tk2->token);
                    cout << "found " << tree->tk1->token << endl;
                    stack.push_back(tree->tk2->token);
                } else {
                    cout << "found " << tree->tk2->token << endl;
                    checkLocalForDuplicates(tree->tk2->token);
                    stack.push_back(tree->tk2->token);
                }
        } else {
            checkVariableDeclaration(tree->tk1->token);
        }
    }
    if (tree->tk2->tokenType == IDtk && tree->nodeType == "<VARS>"){
        if (tree->nodeType == "<VARS>"){
            if (inGlobal) {
                    cout << "global offset increased" << endl;
                    globalOffset++;
                    checkGlobalForDuplicates(tree->tk3->token);
                    cout << "found " << tree->tk1->token << endl;
                    stack.push_back(tree->tk3->token);
                } else {
                    cout << "found " << tree->tk3->token << endl;
                    checkLocalForDuplicates(tree->tk3->token);
                    stack.push_back(tree->tk3->token);
                }
        } else {
            checkVariableDeclaration(tree->tk1->token);
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
        cout << "out of global" << endl;
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

void doubleDeclarationError() {
    cout << "double declaration" << endl;
    exit(0);
}

void missingDeclarationError(string variable) {
    for (int i = stack.size(); i > 0; i--){
        cout << stack.at(i-1) << endl;
    }
    cout << "Missing declaration of " << variable << endl;
    exit(0);
}