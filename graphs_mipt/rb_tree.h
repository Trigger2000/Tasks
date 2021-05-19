#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cassert>
#include <chrono>
#include <fstream>

enum class colour
{ 
    red,
    black
};


template <typename T>
struct node
{
    node<T> *parent = nullptr;
    node<T> *left = nullptr;
    node<T> *right = nullptr;
    colour color = colour::black;
    T data;
};

#define NIL &helper
node<int> helper = {NIL, NIL, 0, colour::black, 0};

template <typename T>
class rb_tree
{
public:
    node<T>* insert_node(T data);
    void delete_node(node<T> *node);
    void print_tree();
    void delete_tree();
    node<T>* find_node(T data);

private:
    void rotate_left(node<T> *x);
    void rotate_right(node<T> *x);
    void insert_fixup(node<T> *x);
    void delete_fixup(node<T> *x);
    void print_tree_private(node<T> *x);
    void delete_tree_private(node<T> *x);

    node<T> *root = NIL;
};

std::vector<int> parse_input(std::string input);