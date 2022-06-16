#pragma once
#include "Polinoms.h"
#include "Tables.h"

template <typename T>
class HashTable;

template <typename T>
class List2;

template <typename T>
class Polinom;

template <typename T1>
class Node2
{
    friend List2<T1>;

    template <typename V>
    friend void push(Polinom<V> data, int data1, List2<Polinom<V>>& lst);

    template <typename V>
    friend void push_polinom_ht(Polinom<V> elem, int key, HashTable<Polinom<V>>& hash_table);

    template <typename V>
    friend void remove_by_key(int key, HashTable<Polinom<V>>& hash_table);

    template <typename V>
    friend void show_list_of_polinoms(List2<Polinom<V>>& lst);

    template <typename V>
    friend void show_list_of_polinoms(HashTable<Polinom<V>>& hash_table);

protected:
    T1 data;//коэффициент
    int data1;//степени
    Node2<T1>* pNext;
    Node2<T1>* pPrev;

public:

    Node2(T1 data = T1(), int data1 = 0, Node2* pNext = nullptr, Node2* pPrev = nullptr)
    {
        this->data = data;
        this->data1 = data1;
        this->pNext = pNext;
        this->pPrev = pPrev;
    }

};

template <typename T>
class List2
{
    template <typename V>
    friend void push(Polinom<V> data, int data1, List2<Polinom<V>>& lst);

    template <typename V>
    friend void remove_by_key(int key, HashTable<Polinom<V>>& hash_table);

    template <typename V>
    friend void show_list_of_polinoms(List2<Polinom<V>>& lst);

protected:

    Node2<T>* head;
    int Size;

public:

    List2();
    List2(int Size);
    List2(List2<T>& other);
    ~List2();

    int GetSize() { return Size; }//
    void push_back(T data, int data1);//
    void push_front(T data, int data1);//
    void pop_back();//
    void pop_front();//
    void clear();//отчистка списка
    void insert(T data, int data1, const int index);//вставка узла
    void removeAt(const int index);//удаление узла по индексу
    Node2<T>* operator[](const int index);//
    void swap(int left, int right);//перестановка узлов
    bool operator==(const List2<T>& other);
    Node2<T>* find_by_key(int data1);
    void remove_by_key(int key);

};

template <typename T>
bool List2<T>::operator==(const List2<T>& other)
{
    bool flag = true;

    Node2<T>* current1 = this->head;
    Node2<T>* current2 = other.head;

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
List2<T>::List2()
{
    this->head = nullptr;
    this->Size = 0;
}

template <typename T>
List2<T>::List2(int Size)
{
    this->head = nullptr;
    for (int i = 0; i < Size; i++)
    {
        T data;
        this->push_back(data, i);
    }
}

template <typename T>
List2<T>::List2(List2<T>& other)
{
    this->head = nullptr;
    this->Size = 0;
    for (int i = 0; i < other.Size; i++)
    {
        this->push_back((*other[i]).data, (*other[i]).data1);
    }
}

template <typename T>
List2<T>::~List2()
{
    this->clear();
}

template <typename T>
void List2<T>::push_back(T data, int data1)
{
    if (head == nullptr)
    {
        this->head = new Node2<T>(data, data1);
    }
    else
    {
        Node2<T>* current = this->head;

        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new Node2<T>(data, data1, nullptr, current);
    }
    Size++;
}

template <typename T>
void List2<T>::pop_front()
{
    if (head != nullptr)
    {
        if (this->head->pNext != nullptr)
        {
            Node2<T>* saver = this->head->pNext;
            delete head;
            saver->pPrev = nullptr;
            head = saver;
            Size--;
        }
        else
        {
            delete head;
            head = nullptr;
            Size = 0;
        }
    }
    else {
        throw "List is empty";
    }
}

template <typename T>
void List2<T>::clear()
{
    while (Size)
    {
        this->pop_front();
    }
}

template <typename T>
Node2<T>* List2<T>::operator[](const int index)
{
    if (index >= Size || index < 0)
    {
        throw "Out of bounds list";
    }

    int k = 0;

    Node2<T>* current = this->head;

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
    return current;
}

template<typename T>
inline void List2<T>::swap(int left, int right)
{
}

template <typename T>
void List2<T>::push_front(T data, int data1)
{
    if (head == nullptr)
    {
        this->push_back(data, data1);
    }
    else
    {
        Node2<T>* new_head = new Node2<T>(data, data1);
        this->head->pPrev = new_head;
        new_head->pNext = this->head;
        this->head = new_head;
    }
    Size++;
}

template <typename T>
void List2<T>::pop_back()
{
    if (head == nullptr)
    {
        throw "List is empty";
    }

    Node2<T>* current = this->head;

    while (current->pNext->pNext != nullptr)
    {
        current = current->pNext;
    }

    delete current->pNext;
    current->pNext = nullptr;
    Size--;
}

template <typename T>
void List2<T>::insert(T data, int data1, const int index)
{
    if (head == nullptr)
    {
        this->push_back(data, data1);
    }

    int k = 0;
    Node2<T>* current = this->head;

    while (current->pNext != nullptr)
    {
        if (k + 1 != index)
        {
            current = current->pNext;
            k++;
        }
        else
        {
            break;
        }
    }

    if (current->pNext == nullptr && (k + 1 != index))
    {
        throw "Выход за границы списка";
    }

    Node2<T>* saver = current->pNext;

    Node2<T>* new_node = new Node2<T>(data, data1);

    current->pNext = new_node;

    new_node->pPrev = current;

    new_node->pNext = saver;

    saver->pPrev = new_node;

    Size++;
}

template <typename T>
void List2<T>::removeAt(const int index)
{

    if (index >= Size || index < 0)
    {
        throw "Out of bounds list";
    }


    if (index == 0)
    {
        Node2<T>* new_head = this->head->pNext;
        delete head;
        head = new_head;
        head->pPrev = nullptr;
    }
    else
    {
        int k = 0;
        Node2<T>* current = this->head;

        while (current->pNext != nullptr)
        {
            if (k + 1 != index)
            {
                current = current->pNext;
                k++;
            }
            else
            {
                break;
            }
            
        }

        if (current->pNext != nullptr)
        {
            Node2<T>* saver = current->pNext->pNext;

            delete current->pNext;

            current->pNext = saver;

            saver->pPrev = current;
        }
        //
    }
    Size--;
}

template <typename T>
void List2<T>::remove_by_key(int data1)
{
    if (Size != 0)
    {
        if (this->head->data1 == data1)
        {
            Node2<T>* new_head = this->head->pNext;
            delete head;
            head = new_head;
            
            if (this->head != nullptr)
            {
                head->pPrev = nullptr;
            }
            
        }
        else
        {
            Node2<T>* current = this->head;

            while (current->pNext != nullptr)
            {
                if (current->pNext != nullptr)
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
                Node2<T>* saver = current->pNext->pNext;

                delete current->pNext;

                current->pNext = saver;

                saver->pPrev = current;
            }
        }
        Size--;
    }
    
}

template <typename T>
void swap(int left, int right)
{
    if (left > right)
    {
        int saver = right;
        right = left;
        left = saver;
    }

    Node2<T> l_node = this->operator[](left);
    Node2<T> r_node = this->operator[](right);

    this->removeAt(left);
    this->removeAt(right);

    this->insert(r_node.data, r_node.data1, left);
    this->insert(l_node.data, l_node.data1, right);
}

template <typename T>
Node2<T>* List2<T>::find_by_key(int data1)
{

    if (this->GetSize() != 0)
    {
        int l_border = 0;
        int r_border = this->GetSize();

        Node2<T>* saver = nullptr;

        bool flag = 0;

        Node2<T>* current = nullptr;

        do
        {
            current = this->operator[]((l_border + r_border) / 2);
            if (current->data1 < data1)
            {
                l_border = (l_border + r_border) / 2;
                flag = 0;
            }
            else if (current->data1 > data1)
            {
                r_border = (l_border + r_border) / 2;
                flag = 1;
            }
            else if (current->data1 == data1)
            {
                saver = current;
                break;
            }
        } while (r_border - l_border > 1);

        return saver;
    }
    else
    {
        throw "Список пуст";
    }
}

template <typename T>
void push(Polinom<T> data, int data1, List2<Polinom<T>>& lst)
{
    if (lst.GetSize() != 0)
    {
        int l_border = 0;
        int r_border = lst.GetSize() - 1;

        bool flag = 0;

        Node2<Polinom<T>>* current = nullptr;

        while (r_border - l_border > 1)
        {
            current = lst[(l_border + r_border) / 2];
            if (current->data1 < data1)
            {
                l_border = (l_border + r_border) / 2;
            }
            else if (current->data1 > data1)
            {
                r_border = (l_border + r_border) / 2;
                
            }
            else if (current->data1 == data1)
            {
                throw "Элемент с данным ключом уже находится в списке";
            }
            flag = 1;
        }

        current = lst[(l_border + r_border) / 2];

        if (data1 <= current->data1)
        {
            lst.push_front(data, data1);
        }
        else if (data1 >= current->data1 && flag == 0)
        {
            lst.push_back(data, data1);
        }
        else
        {
            Node2<Polinom<T>>* saver = current->pNext;

            Node2<Polinom<T>>* new_node = new Node2<Polinom<T>>(data, data1);

            current->pNext = new_node;

            new_node->pPrev = current;

            new_node->pNext = saver;

            if (saver != nullptr)
            {
                saver->pPrev = new_node;
            }
            

            lst.Size++;
        }
    }
    else
    {
        lst.push_back(data, data1);
    }
}

//template <typename T>
//void push(int data1, List2<List<T>>& lst, List<T> data = List<T>())
//{
//    if (lst.GetSize() != 0)
//    {
//        int l_border = 0;
//        int r_border = lst.GetSize();
//
//        bool flag = 0;
//
//        Node2<Polinom<T>>* current = nullptr;
//
//        do
//        {
//            current = lst[(l_border + r_border) / 2];
//            if (current->data1 < data1)
//            {
//                l_border = (l_border + r_border) / 2;
//                flag = 0;
//            }
//            else if (current->data1 > data1)
//            {
//                r_border = (l_border + r_border) / 2;
//                flag = 1;
//            }
//            else if (current->data1 == data1)
//            {
//                throw "Элемент с данным ключом уже находится в списке";
//            }
//        } while (r_border - l_border > 1);
//
//        if (flag == 1)
//        {
//            current = current->pPrev;
//        }
//
//
//
//        if (current->pNext != nullptr)
//        {
//            Node2<Polinom<T>>* saver = current->pNext;
//
//            Node2<Polinom<T>>* new_node = new Node2<Polinom<T>>(data, data1);
//
//            current->pNext = new_node;
//
//            new_node->pPrev = current;
//
//            new_node->pNext = saver;
//
//            saver->pPrev = new_node;
//
//            lst.Size++;
//        }
//        else
//        {
//            lst.push_back(data, data1);
//        }
//    }
//    else
//    {
//        lst.push_back(data, data1);
//    }
//
//
//}

template <typename V>
void show_list_of_polinoms(List2<Polinom<V>>& lst)
{
    Node2<Polinom<V>>* current = lst.head;
    for (int i = 0; i < lst.GetSize(); i++)
    {
        std::cout << "( ";
        current->data.Show();
        std::cout << " , " << current->data1 << ")" << std::endl;
        current = current->pNext;
    }
}
