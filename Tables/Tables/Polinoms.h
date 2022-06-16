#pragma once

#include "List.h"

template <typename T>
class Polinom : public List<T>
{
    template <typename V>
    friend void Merge(Polinom<V>* pol_1, Polinom<V>* pol_2);

    template <typename V>
    friend int HashFunction(const Polinom<V>& pol);

public:
    Polinom() {}
    Polinom(Polinom<T>& other);
    ~Polinom() {}

    void Show();

    Polinom<T>& operator= (Polinom<T>& pol);

    void scMult(const T scalar);

    bool operator==(const Polinom<T>& other) const;
};

template <typename T>
Polinom<T>::Polinom(Polinom<T>& other)
{
    this->head = nullptr;
    for (int i = 0; i < other.Size; i++)
    {
        this->push_back(other[i].data, other[i].data1);
    }
}

template <typename T>
bool Polinom<T>::operator==(const Polinom<T>& other) const
{
    bool flag = true;

    Node<T>* current1 = this->head;
    Node<T>* current2 = other.head;

    while (current1->pNext != nullptr && current2->pNext != nullptr)
    {
        if (current1->data == current2->data && current1->data1 == current2->data1)
        {
            current1 = current1->pNext;
            current2 = current2->pNext;
        }
        else
        {
            flag = false;
            break;
        }
    }

    return flag;
}

template <typename T>
void List<T>::swap(int left, int right)
{
    if ((left >= Size) || (left < 0) || (right >= Size) || (right < 0))
        throw "Out of bounds list";

    if (left > right)
    {
        int temp = left;
        left = right;
        right = temp;
    }

    if (left != right)
    {
        int k = 0;

        Node<T>* current = this->head;

        while (current->pNext != nullptr)
        {
            if (k != left)
            {
                current = current->pNext;
            }
            else
            {
                break;
            }
            k++;
        }

        k = 0;

        Node<T>* current2 = this->head;

        while (current2->pNext != nullptr)
        {
            if (k != right)
            {
                current2 = current2->pNext;
            }
            else
            {
                break;
            }
            k++;
        }

        T dataCt = current->data;
        int dataCt1 = current->data1;

        current->data = current2->data;
        current->data1 = current2->data1;

        current2->data = dataCt;
        current2->data1 = dataCt1;
    }
}

template <typename T>
void Sort(Polinom<T>& lst)
{
    for (int i = 0; i < lst.GetSize(); i++)
    {
        for (int j = 0; j < lst.GetSize() - i - 1; j++)
        {
            if (lst[j].data1 > lst[j + 1].data1)
            {
                lst.swap(j, j + 1);
            }
        }
    }
}

template <typename V>
void CompressionPolinom(Polinom<V>& lst)
{
    Sort(lst);
    for (int i = 0; i < lst.GetSize() - 1; i++)
    {
        if (lst[i].data1 == lst[i + 1].data1)
        {
            lst[i].data = lst[i].data + lst[i + 1].data;
            lst.removeAt(i + 1);
            i--;
        }
    }
}

template <typename T>
void RemoveZeros(Polinom<T>& lst)
{
    for (int i = 0; i < lst.GetSize(); i++)
    {
        if (lst[i].data == 0)
        {
            lst.removeAt(i);
        }
    }
}

template <typename T>
void Polinom<T>::Show()
{
    Node<T>* current = this->head;
    for (int i = 0; i < this->GetSize(); i++)
    {
        std::cout << current->data << "*";

        if (current->data1 == 0)
        {
            current = current->pNext;
            continue;
        }

        if ((current->data1 - current->data1 % 100) / 100 != 0)
            std::cout << "x^" << (current->data1 - current->data1 % 100) / 100;
        if ((current->data1 % 100 - current->data1 % 10) / 10 != 0)
            std::cout << "y^" << (current->data1 % 100 - current->data1 % 10) / 10;
        if (current->data1 % 10 != 0)
            std::cout << "z^" << current->data1 % 10;

        if (current->pNext != nullptr && current->pNext->data > 0)
        {
            std::cout << " + ";
        }

        if (current->pNext != nullptr)
        {
            current = current->pNext;
        }
    }
}

template <typename T>
Polinom<T>& MergePolinoms(Polinom<T>& pol_1, Polinom<T>& pol_2, Polinom<T>& merged)
{

    Node<T>* current_1 = pol_1.head;
    Node<T>* current_2 = pol_2.head;

    while (current_1 != nullptr && current_2 != nullptr)
    {
        if (current_1->data1 <= current_2->data1)
        {
            merged.push_back(current_1->data, current_1->data1);
            current_1 = current_1->pNext;
        }
        else
        {
            merged.push_back(current_2->data, current_2->data1);
            current_2 = current_2->pNext;
        }
    }

    if (current_1 == nullptr)
    {
        while (current_2 != nullptr)
        {
            merged.push_back(current_2->data, current_2->data1);
            current_2 = current_2->pNext;
        }
    }
    else
    {
        while (current_1 != nullptr)
        {
            merged.push_back(current_1->data, current_1->data1);
            current_1 = current_1->pNext;
        }
    }

    CompressionPolinom(merged);

    return merged;
}

template <typename T>
Polinom<T>& SubtractPolinoms(Polinom<T>& pol_1, Polinom<T>& pol_2, Polinom<T>& subtract)
{
    pol_2.scMult(-1);
    MergePolinoms(pol_1, pol_2, subtract);
    return subtract;
}

template <typename T>
Polinom<T>& MultiplyPolinoms(Polinom<T>& pol_1, Polinom<T>& pol_2, Polinom<T>& mult)
{

    Node<T>* current_2 = pol_2.head;

    for (int k = 0; k < pol_2.GetSize(); k++)
    {
        Node<T>* current_1 = pol_1.head;

        while (current_1 != nullptr)
        {
            if ((((current_1->data1 % 100 - (current_1->data1 % 10)) / 10 + (current_2->data1 % 100 - (current_2->data1 % 10)) / 10) >= 10) ||
                (((current_1->data1 - (current_1->data1 % 100)) / 100 + (current_2->data1 - (current_2->data1 % 100)) / 100) >= 10) ||
                ((current_1->data1 % 10 + current_2->data1 % 10) >= 10))
            {
                throw "Too high degrees";
            }
            mult.push_back(current_1->data * current_2->data, current_1->data1 + current_2->data1);

            current_1 = current_1->pNext;
        }

        current_2 = current_2->pNext;
    }

    CompressionPolinom(mult);

    return mult;
}

template <typename T>
Polinom<T>& Polinom<T>::operator= (Polinom<T>& pol)
{
    if (this->head != nullptr)
        this->clear();

    for (int i = 0; i < pol.GetSize(); i++)
    {
        this->push_back(pol[i].data, pol[i].data1);
    }

    return *this;
}

template <typename T>
void Polinom<T>::scMult(const T scalar)
{
    Node<T>* current = this->head;
    for (int i = 0; i < this->GetSize(); i++)
    {
        current->data *= scalar;
        current = current->pNext;
    }
}