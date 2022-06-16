#pragma once
#include "Tables.h"

template <typename T>
class HashTable;

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

    template <typename V>
    friend void push(V data, int data1, List<V>& lst);

    template <typename V>
    friend void push_polinom_ht(Polinom<V> elem, int key, HashTable<Polinom<V>>& hash_table);

    template <typename V>
    friend void show_list_of_polinoms(List<Polinom<V>>& lst);

    template <typename V>
    friend void show_list_of_polinoms(HashTable<Polinom<V>>& hash_table);

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
    friend void Sort(Polinom<V>& lst);//сортировка списка по data1(степен€м)

    template <typename V>
    friend Polinom<V>& MergePolinoms(Polinom<V>& pol_1, Polinom<V>& pol_2, Polinom<V>& merge);

    template <typename V>
    friend Polinom<V>& MultiplyPolinoms(Polinom<V>& pol_1, Polinom<V>& pol_2, Polinom<V>& mult);

    template <typename V>
    friend void push(V data, int data1, List<V>& lst);

    template <typename V>
    friend void push_polinom_ht(Polinom<V> elem, int key, HashTable<Polinom<V>>& hash_table);

    template <typename V>
    friend void show_list_of_polinoms(List<Polinom<V>>& lst);

    template <typename V>
    friend void show_list_of_polinoms(HashTable<Polinom<V>>& hash_table);


protected:

    Node<T>* head;
    int Size;

public:

    List();
    //List(int Size);
    List(List<T>& other);
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
    bool key_is_busy(int data1);

    void remove_by_key(int data1);
    Node<T>* find_by_key(int data1);


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
List<T>::List(List<T>& other)
{
    this->head = nullptr;
    this->Size = 0;
    for (int i = 0; i < other.Size; i++)
    {
        this->push_back(other[i].data, other[i].data1);
    }
}

template <typename T>
List<T>::~List()
{
    this->clear();
    this->head = nullptr;
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

    if (current->pNext == nullptr && (k + 1 != index))
    {
        throw "¬ыход за границы списка";
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

    if (this->Size != 0)
    {
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
}

template <typename T>
void List<T>::remove_by_key(int data1)
{
    if (this->Size != 0)
    {
        if (this->head->data1 == data1)
        {
            Node<T>* new_head = this->head->pNext;
            delete head;
            head = new_head;
            Size--;
        }
        else
        {
            Node<T>* current = this->head;

            while (current->pNext != nullptr)
            {
                if (current->pNext->data1 != data1)
                {
                    current = current->pNext;
                }
                else
                {
                    break;
                }
            }

            if (current->pNext != nullptr)
            {
                Node<T>* saver = current->pNext->pNext;

                delete current->pNext;

                current->pNext = saver;
                Size--;
            }
        }

    }
}


template <typename T>
void push(T data, int data1, List<T>& lst)
{
    if (lst.head == nullptr)
    {
       lst.head = new Node<T>(data, data1);
    }
    else
    {
        Node<T>* current = lst.head;

        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new Node<T>(data, data1);
    }
    lst.Size++;
}

template <typename V>
void show_list_of_polinoms(List<Polinom<V>>& lst)
{
    Node<Polinom<V>>* current = lst.head;
    for (int i = 0; i < lst.GetSize(); i++)
    {
        std::cout << "( ";
        current->data.Show();
        std::cout << " , " << current->data1 << ")" << std::endl;
        current = current->pNext;
    }
}

template <typename T>
bool List<T>::key_is_busy(int data1)
{
    Node<T>* current = this->head;
    bool flag = 0;
    if (current != nullptr)
    {
        do
        {
            if (current->data1 == data1)
            {
                flag = 1;
                break;
            }
            current = current->pNext;

        } while (current != nullptr);
    }
    return flag;
}