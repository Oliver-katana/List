#include<iostream>
#include<string>

using namespace std;

//Реализация двусвязного списка

template<class Dt>
class Dlist
{
public:
	Dlist();
	~Dlist();

	void push_front(Dt data);
	void pop_front();
	void push_back(Dt data);
	void pop_back();
	void insert(Dt data, int index);
	void removeAt(int index);
	Dt& operator[](const int index);
	int get_size() {return size;}
	void clear();

private:
	template <class Dt>
	class Node
	{
	public:
		Dt data;
		Node* pnext_H;
		Node* pnext_T;
		Node(Dt data = Dt(), Node* pnext_H = nullptr, Node* pnext_T = nullptr)
		{
			this->data = data;
			this->pnext_H = pnext_H;
			this->pnext_T = pnext_T;
		}
	};

	int size;
	Node<Dt>* head;
	Node<Dt>* tail;
};

template<class Dt>
Dlist<Dt>::Dlist()
{
	size = 0;
	head = tail = nullptr;
}

template<class Dt>
Dlist<Dt>::~Dlist()
{
	clear();
}

template<class Dt>
void Dlist<Dt>::push_front(Dt data)
{
	head = new Node<Dt>(data, head, nullptr);
	head->pnext_H->pnext_T = head;
	size++;
}

template<class Dt>
void Dlist<Dt>::pop_front()
{
	Node<Dt>* to_delete = head;
	if (head->pnext_H)
	{
		head = head->pnext_H;
		head->pnext_T = nullptr;
	}
	delete to_delete;
	size--;
}

template<class Dt>
void Dlist<Dt>::push_back(Dt data)
{
	if (head == nullptr)
	{
		head = tail = new Node<Dt>(data);
	}
	else
	{
		tail->pnext_H = new Node<Dt>(data, nullptr, tail);
		tail = tail->pnext_H;
	}
	size++;
}

template<class Dt>
void Dlist<Dt>::pop_back()
{
	Node<Dt>* to_delete = tail;
	if (tail->pnext_T)
	{
		tail = tail->pnext_T;
		tail->pnext_H = nullptr;
	}
	delete to_delete;
	size--;
}

template<class Dt>
void Dlist<Dt>::insert(Dt data, int index)
{
	Node<Dt>* current = head;
	if (index == 0)
	{
		push_front(data);
	}
	else if (index < (size / 2))
	{
		for (size_t i = 0; i < index; i++)
		{
			current = current->pnext_H;
		}
		current = new Node<Dt>(data, current, current->pnext_T);
		current->pnext_H->pnext_T = current;
		current->pnext_T->pnext_H = current;
		size++;
	}
	if (index == size)
	{
		tail = new Node<Dt>(data, nullptr, tail);
		tail->pnext_T->pnext_H = tail;
		size++;
	}
	else if (index >= size / 2 && index < size)
	{
		current = tail;
		for (size_t i = size; i > index; i--)
		{
			current = current->pnext_T;
		}
		current= new Node<Dt>(data, current->pnext_H, current);
		current->pnext_T->pnext_H = current;
		current->pnext_H->pnext_T = current;
		size++;
	}
}

template<class Dt>
void Dlist<Dt>::removeAt(int index)
{
	Node<Dt>* to_delete = nullptr;
	Node<Dt>* current = head;
	if (index == 0)
	{
		pop_front();
	}
	else if (index < (size / 2))
	{
		for (size_t i = 0; i < index - 1; i++)
		{
			current = current->pnext_H;
		}
		to_delete = current->pnext_H;
		current->pnext_H = current->pnext_H->pnext_H;
		current->pnext_H->pnext_T = current;
		delete to_delete;
		size--;
	}
	if (index == (size-1))
	{
		pop_back();
	}
	else if (index >= size / 2 && index < (size-1))
	{
		current = tail;
		for (size_t i = size-1; i > index + 1; i--)
		{
			current = current->pnext_T;
		}
		to_delete = current->pnext_T;
		current->pnext_T = current->pnext_T->pnext_T;
		current->pnext_T->pnext_H = current;
		delete to_delete;
		size--;
	}

}

template<class Dt>
Dt& Dlist<Dt>::operator[](const int index)
{
	Node<Dt>* current=head;
	if (index == 0)
	{
		return current->data;
	}
	
	if (index<=(size/2))
	{
		current = current->pnext_H;
		for (size_t i = 0; i < index-1; i++)
		{
			current = current->pnext_H;
		}
	}
	else if (index > size / 2 && index < size)
	{
		current = tail;
		if (index == size)
		{
			return tail->pnext_H->data;
		}
		for (size_t i = size; i > index+1; i--)
		{
			current = current->pnext_T;
		}
	}
	return current->data;
}

template<class Dt>
void Dlist<Dt>::clear()
{
	while (size)
	{
		pop_front();
	}
}

int	main()
{
	setlocale(LC_ALL, "Rus");
	//Двусвязный список

	Dlist<int> dlst;
	int Dlist_size;
	cout << "Введите размер списка" << endl;
	cin >> Dlist_size;
	for (int i = 0; i < Dlist_size; i++)
	{
		dlst.push_back(i+1);
	}
	for (int i = 0; i < dlst.get_size(); i++)
	{
		cout << dlst[i] << "  ";
	}
	cout << endl << endl;
	//dlst.push_front(99);
	//dlst.pop_front();
	//dlst.pop_back();
	//dlst.insert(100, 1);
	dlst.removeAt(5);
	cout << "Размер списка= " << dlst.get_size() << endl << endl;
	for (int i = 0; i < dlst.get_size(); i++)
	{
		cout << dlst[i] << "  ";
	}
	
	return 0;
};
