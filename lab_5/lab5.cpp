#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

struct Elem
{
    int data;
    Elem* left;
    Elem* right;
    Elem* parent;
};

Elem* MAKE(int data, Elem* p)
{
    Elem* q = new Elem;

    q->data = data;
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;
    return q;
}

void ADD(int data, Elem*& root)
{
    if (root == nullptr)
    {
        root = MAKE(data, nullptr);
        return;
    }
    Elem* v = root;
    while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr))
        if (data < v->data)
            v = v->left;
        else
            v = v->right;
    if (data == v->data)
        return;
    Elem* u = MAKE(data, v);
    if (data < v->data)
        v->left = u;
    else
        v->right = u;
}

void PASS(Elem* v)
{
    if (v == nullptr)
        return;
    PASS(v->left);
    std::cout << v->data << std::endl;
    PASS(v->right);

}

Elem* SEARCH(int data, Elem* v)
{
    if (v == nullptr)
        return v;
    if (v->data == data)
        return v;
    if (data < v->data)
        return SEARCH(data, v->left);
    else
        return SEARCH(data, v->right);
}

void DELETE_ELEM(int data, Elem*& root)
{  
    Elem* u = SEARCH(data, root);
    if (u == nullptr)
        return;

    if (u->left == nullptr && u->right == nullptr && u == root)
    {
        delete root;
        root = nullptr;
        return;
    }

    if (u->left == nullptr && u->right != nullptr && u == root) 
    {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }

    if (u->left != nullptr && u->right == nullptr && u == root)
    {
        Elem* t = u->left;
        while (t->right != nullptr)
            t = t->right;
        u->data = t->data;
        u = t;
    }   
    if (u->left != nullptr && u->right != nullptr)
    {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
    Elem* t;
    if (u->left == nullptr)
        t = u->right;
    else
        t = u->left;
    if (u->parent->left == u)
        u->parent->left = t;
    else
        u->parent->right = t;
    if (t != nullptr)
        t->parent = u->parent;
    delete u;

}

int Depth(Elem* v, int digit)
{
    int depth = 1;
    Elem* p = SEARCH(digit, v);

    if (p != nullptr)
    {
        if (v->data == digit)
            return depth;

        while (v->data != digit)
        {
            if (v->data < digit)
                v = v->right;
            else
                v = v->left;
            depth++;
        }
        return depth;
    }
    else
        return depth = 0;
}
   
int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    Elem* root = nullptr;
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    char sign;
    int digit;
    while (!in.eof())
    {
        in >> sign;
        if (sign == '+')
        {
            in >> digit;
            ADD(digit, root);
        }

        if (sign == '-')
        {
            in >> digit;
            DELETE_ELEM(digit, root);
        }

        if (sign == 'E')
            break;

        if (sign == '?')
        {
            in >> digit;
            if ((Depth(root, digit)) == 0)
            {
                out << "n";
                std::cout << "n";
            }
            else
            {
                out << (Depth(root, digit));
                std::cout << (Depth(root, digit));
            }
        }
    }
    return 0;
}
