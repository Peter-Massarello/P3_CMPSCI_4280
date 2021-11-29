#ifndef SEM_H
#define SEM_H
#include "token.hpp"
#include "node.hpp"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

void staticSemantics(Node* &tree);

void buildStack(Node* &tree, int level);

int find();

void push();

void pop();
#endif