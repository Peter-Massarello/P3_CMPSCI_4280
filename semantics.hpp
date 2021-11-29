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

void checkForDuplicates(string variables);

void push();

void pop();

void error();
#endif