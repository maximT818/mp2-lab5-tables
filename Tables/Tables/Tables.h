#pragma once
#include "List.h"
#include "List2.h"
#include "Polinoms.h"

template <typename T>
class HashTable;

template <typename T>
class UnorderTable : public List<T>
{

};

template <typename T>
class OrderTable : public List2<T>
{


};

template <typename T>
class HashTable : public List2<List<T>>
{
	template <typename V>
	friend void show_list_of_polinoms(HashTable<Polinom<V>>& hash_table);

	template <typename V>
	void push_polinom_ht(Polinom<V> elem, int key, HashTable<Polinom<V>>& hash_table);

public:
	HashTable(int Size) : List2<List<T>>(Size) {};
};

template <typename T>
void push_polinom_ht(Polinom<T> elem, int key, HashTable<Polinom<T>>& hash_table)
{
	int hash = 0;
	Node<T>* current_h = elem.head;

	for (int i = 0; i < elem.GetSize(); i++)
	{
		hash += current_h->data1;
		current_h = current_h->pNext;
	}

	hash = hash % 100;

	Node2<List<Polinom<T>>>* saver = hash_table.find_by_key(hash);

	if (saver->data.head != nullptr)
	{
		Node<Polinom<T>>* current = saver->data.head;

		for (int i = 0; i < saver->data.GetSize(); i++)
		{
			if ((*current).data1 != key)
			{
				current = current->pNext;
			}
			else
			{
				throw "В таблице уже имеется запись с данным ключом";
			}
		}
		if (current != nullptr)
			current->pNext = new Node<Polinom<T>>(elem, key);
		else
			current = new Node<Polinom<T>>(elem, key);
	}
	else
	{
		(*saver).data.push_back(elem, key);
	}
}

template <typename T>
void remove_by_key(int key, HashTable<Polinom<T>>& hash_table)
{
	Node2<List<Polinom<T>>>* saver = hash_table.head;

	for (int i = 0; i < hash_table.GetSize(); i++)
	{
		saver->data.remove_by_key(key);
		saver = saver->pNext;
	}
}

template <typename T>
void show_list_of_polinoms(HashTable<Polinom<T>>& hash_table)
{
	Node2<List<Polinom<T>>>* saver = hash_table.head;

	for (int i = 0; i < hash_table.GetSize(); i++)
	{
		
		if ((*saver).data.GetSize() != 0)
		{
			std::cout << (*saver).data1 << ": ";
			Node<Polinom<T>>* current = (*saver).data.head;
			for (int j = 0; j < (*saver).data.GetSize(); j++)
			{
				std::cout << "( ";
				current->data.Show();
				std::cout << " , " << current->data1 << ") ";
				current = current->pNext;
			}
			std::cout << std::endl;

			
		}
		saver = saver->pNext;
	}
}