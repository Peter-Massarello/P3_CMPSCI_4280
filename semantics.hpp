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

void doubleDeclarationError(string variable);

void missingDeclarationError(string variable);

void pop();

void push(string variable);

int find(string variable);

void clearStack();
#endif