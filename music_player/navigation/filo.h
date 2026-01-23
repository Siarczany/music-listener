#pragma once

template<typename T>
struct node
{
    T value;
    node* next;
};

template<typename T>
class filo
{
private:

    node<T>* root;

public:
    filo();
    ~filo();

    void add(const T &value);
    void push(const T &value);

    T get();
    T pop();

    void clear();
};

#include "filoimpl.h"
