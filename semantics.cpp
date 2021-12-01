#include "semantics.hpp"
using namespace std;

vector<string> stack;
int globalOffset = 0;
int localVars = 0;
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
    cout << "not dec" << variableString << endl;
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
    for (int i = stack.size()-1; i >= 0; i--){
        if (stack.at(i) == token) {
            return (stack.size()) - i;
        }
    }
    return -1;
}

void clearLocalStack() {
    for (int i = stack.size(); i > globalOffset; i--){
        cout << "poping " << stack.at(i-1) << endl;
        stack.pop_back();
        localVars--;
    }

}

void getVars(Node* &tree) {
    if (tree->tk1->tokenType != IDtk) return;
    if (tree->nodeType != "<VARS>") return;

    cout << "trying to find " << tree->tk1->token << endl;
    int notFound = find(tree->tk1->token);

    if (notFound == -1) {
        push(tree->tk1->token);
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
    if (tree->nodeType == "<BLOCK>") {
        addBlockToStack(tree);
        inGlobal = false;
    } else {
        string tk1 = tree->tk1->token;
        string tk2 = tree->tk2->token;
        string tk3 = tree->tk3->token;

        if (tree->tk1->tokenType == IDtk && find(tk1) == -1) missingDeclarationError(tk1);
        if (tree->tk2->tokenType  == IDtk && find(tk1) == -1) missingDeclarationError(tk2);
        if (tree->tk3->tokenType  == IDtk && find(tk1) == -1) missingDeclarationError(tk3);

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
    cout << "pushing " << variable << endl; 
    if (!inGlobal) localVars++;
    stack.push_back(variable);
      for (auto it = stack.rbegin(); it != stack.rend(); it++)
        cout << "current stack " <<  *it << endl;
}

void doubleDeclarationError(string variable) {
    cout << "STATIC SEMANTICS ERROR: Double declaration of " << variable << endl;
    exit(0);
}

void missingDeclarationError(string variable) {
    cout << "STATIC SEMANTICS ERROR: Missing declaration of " << variable << endl;
    exit(0);
}
