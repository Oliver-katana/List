#include<iostream>

using namespace std;

//Реализация двусвязного списка

template<class DL>
class Dlist
{
public:
	Dlist();
	~Dlist();

	void push_front(DL data);
	void pop_front();
	void push_back(DL data);
	void pop_back();
	void insert(DL data, int index);
	void removeAt(int index);
	int get_size() { return size; }
	void clear();
	DL& operator[](const int index);


private:
	template <class DL>
	class Node
	{
	public:
		DL data;
		Node* p_next;
		Node* p_prev;
		Node(DL data = DL(), Node* p_next = nullptr, Node* p_prev = nullptr)
		{
			this->data = data;
			this->p_next = p_next;
			this->p_prev = p_prev;
		}
	};

	int size;
	Node<DL>* head;
	Node<DL>* tail;

	template<class DL>
	class Iterator
	{
	public:
		Iterator()
		{
			ptr = nullptr;
		};
		Iterator(Node<DL>* it) 
		{
			ptr = it;
		};
		DL& operator *()
		{
			return ptr->data;
		}
		Iterator& operator++()
		{
			ptr = ptr->p_next;
			return *this;
		}
		bool operator!=(const Iterator& other)
		{
			return ptr != other.ptr;
		}

		Node<DL>* ptr;
	};

public:
	Iterator<DL> begin()
	{
		return head;
	};
	Iterator<DL> end()
	{
		return tail->p_next;
	};
};

template<class DL>
Dlist<DL>::Dlist()
{
	size = 0;
	head = tail = nullptr;
}

template<class DL>
Dlist<DL>::~Dlist()
{
	clear();
}

template<class DL>
void Dlist<DL>::push_front(DL data)
{
	if (head == nullptr)
	{
		head = tail = new Node<DL>(data);
	}
	else
	{
		head = new Node<DL>(data, head, nullptr);
		head->p_next->p_prev = head;
	}
	size++;
}

template<class DL>
void Dlist<DL>::pop_front()
{
	Node<DL>* to_delete = head;
	if (head->p_next)
	{
		head = head->p_next;
		head->p_prev = nullptr;
	}
	else
	{
		head = nullptr;
	}
	delete to_delete;
	size--;
}

template<class DL>
void Dlist<DL>::push_back(DL data)
{
	if (head == nullptr)
	{
		head = tail = new Node<DL>(data);
	}
	else
	{
		tail->p_next = new Node<DL>(data, nullptr, tail);
		tail = tail->p_next;
	}
	size++;
}

template<class DL>
void Dlist<DL>::pop_back()
{
	Node<DL>* to_delete = tail;
	if (tail->p_prev)
	{
		tail = tail->p_prev;
		tail->p_next = nullptr;
	}
	else
	{
		tail = nullptr;
	}
	delete to_delete;
	size--;
}

template<class DL>
void Dlist<DL>::insert(DL data, int index)
{
	Node<DL>* current = head;
	if (index == 0)
	{
		push_front(data);
	}
	else if (index < (size / 2))
	{
		for (size_t i = 0; i < index; i++)
		{
			current = current->p_next;
		}
		current = new Node<DL>(data, current, current->p_prev);
		current->p_next->p_prev = current;
		current->p_prev->p_next = current;
		size++;
	}
	if (index == size)
	{
		tail = new Node<DL>(data, nullptr, tail);
		tail->p_prev->p_next = tail;
		size++;
	}
	else if (index >= size / 2 && index < size)
	{
		current = tail;
		for (size_t i = size; i > index; i--)
		{
			current = current->p_prev;
		}
		current = new Node<DL>(data, current->p_next, current);
		current->p_prev->p_next = current;
		current->p_next->p_prev = current;
		size++;
	}
}

template<class DL>
void Dlist<DL>::removeAt(int index)
{
	Node<DL>* to_delete = nullptr;
	Node<DL>* current = head;
	if (index == 0)
	{
		pop_front();
	}
	else if (index < (size / 2))
	{
		for (size_t i = 0; i < index - 1; i++)
		{
			current = current->p_next;
		}
		to_delete = current->p_next;
		current->p_next = current->p_next->p_next;
		current->p_next->p_prev = current;
		delete to_delete;
		size--;
	}
	if (index == (size - 1))
	{
		pop_back();
	}
	else if (index >= size / 2 && index < (size - 1))
	{
		current = tail;
		for (size_t i = size - 1; i > index + 1; i--)
		{
			current = current->p_prev;
		}
		to_delete = current->p_prev;
		current->p_prev = current->p_prev->p_prev;
		current->p_prev->p_next = current;
		delete to_delete;
		size--;
	}

}

template<class DL>
DL& Dlist<DL>::operator[](const int index)
{
	Node<DL>* current = head;
	if (index == 0)
	{
		return current->data;
	}

	if (index <= (size / 2))
	{
		current = current->p_next;
		for (size_t i = 0; i < index - 1; i++)
		{
			current = current->p_next;
		}
	}
	else if (index > size / 2 && index < size)
	{
		current = tail;
		if (index == size)
		{
			return tail->p_next->data;
		}
		for (size_t i = size; i > index + 1; i--)
		{
			current = current->p_prev;
		}
	}
	return current->data;
}

template<class DL>
void Dlist<DL>::clear()
{
	while (size)
	{
		pop_front();
	}
}

int	main()
{
	setlocale(LC_ALL, "Rus");



	Dlist<int> dlst;
	int Dlist_size;
	cout << "Введите размер списка" << endl;
	cin >> Dlist_size;
	for (int i = 0; i < Dlist_size; i++)
	{
		dlst.push_back(i + 1);
	}
	for (int i = 0; i < dlst.get_size(); i++)
	{
		cout << dlst[i] << "  ";
	}
	cout << endl << endl;

	dlst.push_front(99);
	//dlst.pop_front();
	//dlst.pop_back();
	dlst.insert(100, 1);
	dlst.removeAt(2);

	cout << "Размер списка= " << dlst.get_size() << endl << endl;

	for (auto it = dlst.begin(); it != NULL; it = it.ptr->p_next)
	{
		cout << *it << "  ";
	}
	cout << endl;
	cout << endl << endl;

	for (auto it : dlst)
	{
		cout << it << "  ";
	}


	return 0;
};
