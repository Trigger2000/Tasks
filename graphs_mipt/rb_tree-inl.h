#pragma once

#include "rb_tree.h"

template <typename T>
void rb_tree<T>::rotate_left(node<T> *x) 
{
    node<T> *y = x->right;

    x->right = y->left;
    if (y->left != NIL)
    {
        y->left->parent = x;
    }

    if (y != NIL)
    {
        y->parent = x->parent;
    }

    if (x->parent)
    {
        if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
    }
    else
    {
        root = y;
    }

    y->left = x;
    if (x != NIL)
    {   
        x->parent = y;
    }
}

template <typename T>
void rb_tree<T>::rotate_right(node<T> *x)
{
    node<T> *y = new node<T>;
    y = x->left;

    x->left = y->right;
    if (y->right != NIL)
    {
        y->right->parent = x;
    }

    if (y != NIL)
    {
        y->parent = x->parent;
    }

    if (x->parent) 
    {
        if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
    }
    else
    {
        root = y;
    }

    y->right = x;
    if (x != NIL)
    { 
        x->parent = y;
    }
}

template <typename T>
node<T>* rb_tree<T>::insert_node(T data)
{
    node<T> *current, *parent;
    node<T> *x = new node<T>;

    current = root;
    parent = nullptr;
    while (current != NIL)
    {
        if (data == current->data)
        {
            return current;
        }
        parent = current;
        if (data < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    x->data = data;
    x->parent = parent;
    x->left = NIL;
    x->right = NIL;
    x->color = colour::red;

    if(parent) 
    {
        if(data < parent->data)
        {
            parent->left = x;
        }
        else
        {
            parent->right = x;
        }
    }
    else
    {
        root = x;
    }

    insert_fixup(x);
    return(x);
}

template <typename T>
void rb_tree<T>::insert_fixup(node<T> *x)
{
    while (x != root && x->parent->color == colour::red)
    {
        if (x->parent == x->parent->parent->left)
        {
            node<T> *y = x->parent->parent->right;
            if (y->color == colour::red)
            {
                x->parent->color = colour::black;
                y->color = colour::black;
                x->parent->parent->color = colour::red;
                x = x->parent->parent;
            } 
            else
            {
                if (x == x->parent->right)
                {
                    x = x->parent;
                    rotate_left(x);
                }
                x->parent->color = colour::black;
                x->parent->parent->color = colour::red;
                rotate_right(x->parent->parent);
            }
        }
        else
        {
            node<T> *y = x->parent->parent->left;
            if (y->color == colour::red)
            {
                x->parent->color = colour::black;
                y->color = colour::black;
                x->parent->parent->color = colour::red;
                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->left)
                {
                    x = x->parent;
                    rotate_right(x);
                }
                x->parent->color = colour::black;
                x->parent->parent->color = colour::red;
                rotate_left(x->parent->parent);
            }
        }
    }
    root->color = colour::black;
}

template <typename T>
void rb_tree<T>::delete_node(node<T> *z)
{
    node<T> *x, *y;

    if (!z || z == NIL)
    {
        return;
    }

    if (z->left == NIL || z->right == NIL)
    {
        y = z;
    }
    else
    {
        y = z->right;
        while (y->left != NIL)
        {
            y = y->left;
        }
    }

    if (y->left != NIL)
    {
        x = y->left;
    }
    else
    {
        x = y->right;
    }

    x->parent = y->parent;
    if (y->parent)
    {
        if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }
    }
    else
    {
        root = x;
    }

    if (y != z) 
    {
        z->data = y->data;
    }


    if (y->color == colour::black)
    {
        delete_fixup (x);
    }

    delete y;
}

template <typename T>
void rb_tree<T>::delete_fixup(node<T> *x)
{
    while (x != root && x->color == colour::black)
    {
        if (x == x->parent->left)
        {
            node<T> *w = x->parent->right;
            if (w->color == colour::red)
            {
                w->color = colour::black;
                x->parent->color = colour::red;
                rotate_left (x->parent);
                w = x->parent->right;
            }
            if (w->left->color == colour::black && w->right->color == colour::black)
            {
                w->color = colour::red;
                x = x->parent;
            }
            else
            {
                if (w->right->color == colour::black)
                {
                    w->left->color = colour::black;
                    w->color = colour::red;
                    rotate_right (w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = colour::black;
                w->right->color = colour::black;
                rotate_left (x->parent);
                x = root;
            }
        }
        else
        {
            node<T> *w = x->parent->left;
            if (w->color == colour::red)
            {
                w->color = colour::black;
                x->parent->color = colour::red;
                rotate_right (x->parent);
                w = x->parent->left;
            }
            if (w->right->color == colour::black && w->left->color == colour::black)
            {
                w->color = colour::red;
                x = x->parent;
            }
            else
            {
                if (w->left->color == colour::black)
                {
                    w->right->color = colour::black;
                    w->color = colour::red;
                    rotate_left (w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = colour::black;
                w->left->color = colour::black;
                rotate_right (x->parent);
                x = root;
            }
        }
    }
    x->color = colour::black;
}

template <typename T>
void rb_tree<T>::print_tree()
{
    print_tree_private(root);
    std::cout << '\n';
}

template <typename T>
void rb_tree<T>::print_tree_private(node<T> *x)
{
    if (x->left != NIL)
    {
        print_tree_private(x->left);
    }
    std::cout << x->data << ' ';
    if (x->right != NIL)
    {
        print_tree_private(x->right);
    }
}

template <typename T>
void rb_tree<T>::delete_tree()
{
    delete_tree_private(root);
}

template <typename T>
void rb_tree<T>::delete_tree_private(node<T> *x)
{
    if (x->left != NIL && x->left != NIL && x->right != NIL)
    {
        delete x->left;
        x->left = NIL;
    }
    if (x->right != NIL && x->left != NIL && x->right != NIL)
    {
        delete x->right;
        x->right = NIL;
    }

    if (x->left != NIL)
    {
        delete_tree_private(x->left);
    }
    if (x->right != NIL)
    {
        delete_tree_private(x->right);
    }
}

template<typename T>
node<T>* rb_tree<T>::find_node(T data)
{
    node<T> *current = root;
    while(current != NIL)
    {
        if (data == current->data)
        {
            return (current);
        }
        else
        {
            if (data < current->data)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
    }
    
    return nullptr;
}

std::vector<int> parse_input(std::string input)
{
    std::vector<int> result;

    auto iter1 = input.begin();
    auto iter2 = input.begin();
    for (auto it = input.begin(); it != input.end(); it++)
    {
        if (*it == '(')
        {
            iter1 = it;
        }
        if (*it == ')')
        {
            iter2 = it;
            std::string substr = input.substr(iter1 - input.begin() + 1, iter2 - iter1 - 1);
            result.push_back(std::atoi(substr.c_str()));
        }
    }

    return result;
}