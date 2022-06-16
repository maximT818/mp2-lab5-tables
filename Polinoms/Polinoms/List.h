#pragma once
//#include "Polinom.h"

template <typename T>
class List;

template <typename T>
class Polinom;

template <typename T1>
class Node
{
    friend List<T1>;
    friend Polinom<T1>;

    template <typename V>
    friend void Sort(Polinom<V>& lst);

    template <typename V>
    friend void CompressionPolinom(Polinom<V>& lst);//приведение подобных слагаемых

    template <typename V>
    friend void RemoveZeros(Polinom<V>& lst);

    template <typename V>
    friend Polinom<V>& MergePolinoms(Polinom<V>& pol_1, Polinom<V>& pol_2, Polinom<V>& merge);

    template <typename V>
    friend Polinom<V>& MultiplyPolinoms(Polinom<V>& pol_1, Polinom<V>& pol_2, Polinom<V>& mult);

protected:
    T1 data;//коэффициент
    int data1;//степени
    Node<T1>* pNext;

public:

    Node(T1 data = T1(), int data1 = 0, Node* pNext = nullptr)
    {
        this->data = data;
        this->data1 = data1;
        this->pNext = pNext;
    }
};

template <typename T>
class List
{
    template <typename V>
    friend void Sort(Polinom<V>& lst);//сортировка списка по data1(степеням)

    template <typename V>
    friend Polinom<V>& MergePolinoms(Polinom<V>& pol_1, Polinom<V>& pol_2, Polinom<V>& merge);

    template <typename V>
    friend Polinom<V>& MultiplyPolinoms(Polinom<V>& pol_1, Polinom<V>& pol_2, Polinom<V>& mult);

protected:

    Node<T>* head;
    int Size;

public:

    List();
    ~List();

    int GetSize() { return Size; }//
    void push_back(T data, int data1);//
    void push_front(T data, int data1);//
    void pop_back();//
    void pop_front();//
    void clear();//отчистка списка
    void insert(T data, int data1, const int index);//вставка узла
    void removeAt(const int index);//удаление узла по индексу
    Node<T>& operator[](const int index);//
    void swap(int left, int right);//перестановка узлов
    bool operator==(const List<T>& other);

};

template <typename T>
bool List<T>::operator==(const List<T>& other)
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
List<T>::List()
{
    this->head = nullptr;
    this->Size = 0;
}

template <typename T>
List<T>::~List()
{
    this->clear();
}

template <typename T>
void List<T>::push_back(T data, int data1)
{
    if (head == nullptr)
    {
        this->head = new Node<T>(data, data1);
    }
    else
    {
        Node<T>* current = this->head;

        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new Node<T>(data, data1);
    }
    Size++;
}

template <typename T>
void List<T>::pop_front()
{
    if (head != nullptr)
    {
        Node<T>* saver = this->head->pNext;
        delete head;
        head = saver;
        Size--;
    }
    else {
        throw "List is empty";
    }
}

template <typename T>
void List<T>::clear()
{
    while (Size)
    {
        this->pop_front();
    }
}

template <typename T>
Node<T>& List<T>::operator[](const int index)
{
    if (index >= Size || index < 0)
    {
        throw "Out of bounds list";
    }

    int k = 0;

    Node<T>* current = this->head;

    while (current->pNext != nullptr)
    {
        if (k != index)
        {
            current = current->pNext;
        }
        else
        {
            break;
        }
        k++;
    }
    return *current;
}

template <typename T>
void List<T>::push_front(T data, int data1)
{
    if (head == nullptr)
    {
        this->push_back(data, data1);
    }
    else
    {
        Node<T>* new_head = new Node<T>(data, data1);
        new_head->pNext = this->head;
        this->head = new_head;
    }
    Size++;
}

template <typename T>
void List<T>::pop_back()
{
    if (head == nullptr)
    {
        throw "List is empty";
    }

    Node<T>* current = this->head;

    while (current->pNext->pNext != nullptr)
    {
        current = current->pNext;
    }

    delete current->pNext;
    current->pNext = nullptr;
    Size--;
}

template <typename T>
void List<T>::insert(T data, int data1, const int index)
{
    if (head == nullptr)
    {
        this->push_back(data, data1);
    }

    int k = 0;
    Node<T>* current = this->head;

    while (current->pNext != nullptr)
    {
        if (k + 1 != index)
        {
            current = current->pNext;
        }
        else
        {
            break;
        }
        k++;
    }

    Node<T>* saver = current->pNext;

    Node<T>* new_node = new Node<T>(data, data1);

    current->pNext = new_node;

    new_node->pNext = saver;

    Size++;
}

template <typename T>
void List<T>::removeAt(const int index)
{

    if (index >= Size || index < 0)
    {
        throw "Out of bounds list";
    }


    if (index == 0)
    {
        Node<T>* new_head = this->head->pNext;
        delete head;
        head = new_head;
    }
    else
    {
        int k = 0;
        Node<T>* current = this->head;

        while (current->pNext != nullptr)
        {
            if (k + 1 != index)
            {
                current = current->pNext;
            }
            else
            {
                break;
            }
            k++;
        }

        if (current->pNext != nullptr)
        {
            Node<T>* saver = current->pNext->pNext;

            delete current->pNext;

            current->pNext = saver;
        }
        else
        {
            delete current->pNext;

            current->pNext = nullptr;
        }
    }
    Size--;
}
