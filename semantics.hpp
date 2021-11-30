#ifndef SEM_H
#define SEM_H
#include "token.hpp"
#include "node.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

void staticSemantics(Node* &tree);

void buildStack(Node* &tree, int level);

void checkLocalForDuplicates(string variable);

void checkGlobalForDuplicates(string variable);

void checkVariableDeclaration(string variable);

void push();

void pop();

void doubleDeclarationError();

void missingDeclarationError(string variable);
#endif