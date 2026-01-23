template<typename T>
filo<T>::filo()
{
    root = nullptr;
}

template<typename T>
filo<T>::~filo()
{
    clear();
}

template<typename T>
void filo<T>::push(const T &value)
{
    node<T>* newRoot = new node<T>{value, root};
    root = newRoot;
}

template<typename T>
void filo<T>::add(const T &value)
{
    push(value);
}

template<typename T>
T filo<T>::pop()
{
    T returning;;
    if(root != nullptr)
    {
        returning = root->value;
        node<T>* temp = root;
        root = root->next;
        delete temp;

    }
    return returning;
}

template<typename T>
T filo<T>::get()
{
    return pop();
}

template<typename T>
void filo<T>::clear()
{
    node<T>* temp = root;
    while(temp != nullptr)
    {
        node<T>* temp2 = temp;
        temp = temp->next;
        delete temp2;
    }
    root = nullptr;
}
