#include "Node.h"

template<typename T>
class LinkedList
{
private:
	
	Node<T>* search(int index)
	{
		if (index == 0 && head != NULL)
		{
			return head;
		}
		Node<T>* aux = head;
		int c = 0;
		while (aux != NULL && c != index)
		{
			aux = aux->next;
			c++;
			if (c==index)
			{
				return aux;
			}
		}

		return NULL;
	}

public:
	Node<T>* head;
	Node<T>* tail;
	int size;

	LinkedList()
	{
		head=NULL;
		tail=NULL;
		size = 0;
	}

	void add(T* elem)
	{
		if (head==NULL)
		{
			head = new Node<T>(elem);
			tail = head;
			size++;
		}
		else if (tail == head)
		{
			Node<T>* newNode = new Node<T>(elem);
			tail = newNode;
			head->next = tail;
			size++;
		}
		else
		{
			Node<T>* newNode = new Node<T>(elem);
			tail->next = newNode;
			tail = tail->next;
			size++;
		}
	}

	void remove(int index)
	{
		if (index == 0)
		{
			if (head->next != NULL)
				head = head->next;
			else
				head = NULL;
			return;
		}

		if (index >= size) return;

		Node<T>* aux = search(index-1);
		Node<T>* next = aux->next->next;
		Node<T>* curr = aux->next;
		free(curr);
		aux->next = next;
	}

	bool add(T elem, int index)
	{
		if (index > size)
			return false;
		if (index > 0)
		{
			Node<T>* aux = search(index-1);
			Node<T>* aux2 = aux->next;
			aux->next = new Node(elem);
			aux->next->next = aux2;
			size++;
		}
		else
		{
			if (head==NULL)
			{
				head = new Node(elem);
				tail = head;
				size++;
			}
			else
			{
				Node<T>* newNode = new Node<T>(elem);
				newNode->next = head;
				head = newNode;
				size++;
			}
		}
	}

	T* get(int index)
	{
		Node<T>* s = search(index);
		if (s != NULL)
			return &s->element;
		else
			return NULL;
	}

};