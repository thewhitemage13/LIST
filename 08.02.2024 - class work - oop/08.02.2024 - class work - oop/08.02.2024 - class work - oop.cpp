#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <list>//list<int> l
#include <forward_list>//STL
using namespace std;

class List{

public:
	struct Node
	{
		int data = 0;
		Node* next = nullptr;
	};

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	int count = 0;

public:
	void AddToHead(int data)
	{
		auto newElem = new Node();
		newElem->data = data;
		newElem->next = head;
		if (head == nullptr)
		{
			tail = newElem;
		}
		head = newElem;
		count++;
	}

	~List()
	{

		Clear();
	}

	List()
	{
	}

	List(const List& original)
	{
		if (original.count == 0)return;

		Node* current = original.head;

		while (current != nullptr)
		{
			this->AddToTail(current->data);
			current = current->next;
		}
	}

	void AddToTail(int data)
	{
		auto newElem = new Node();
		newElem->data = data;
		if (tail == nullptr)
		{
			head = newElem;
		}
		else
		{
			tail->next = newElem;
		}
		tail = newElem;
		count++;
	}

	void InsertInto(int data, int position)
	{
		if (position >= count)
		{
			AddToTail(data);
			return;
		}
		else if (position <= 0)
		{
			AddToHead(data);
			return;
		}

		Node* newElem = new Node();
		newElem->data = data;
		int i = 1;
		Node* beforeNew = head;
		while (i++ != position)
		{
			beforeNew = beforeNew->next;
		}
		newElem->next = beforeNew->next;
		beforeNew->next = newElem;

		count++;
	}

	void DeleteFromHead()
	{
		if (count == 0)
		{
			// cout << "Empty list!\n";
			return;
		}
		Node* temp = head;
		head = head->next;
		delete temp;
		count--;
		if (head == nullptr)
		{
			tail = nullptr;
		}
	}

	void SertDesc()
	{
		SortAsc();
		Reverse();
	}

	void DeleteFromTail()
	{
		if (count == 0) {
			// cout << "Empty list!\n";
			return;
		}
		DeleteByIndex(count - 1);
	}

	void DeleteByIndex(int position)
	{
		if (position <= 0)
		{
			DeleteFromHead();
			return;
		}

		if (position >= count)
		{
			position = count - 1;
		}

		int i = 1;
		Node* beforeDel = head;
		while (i++ != position)
		{
			beforeDel = beforeDel->next;
		}
		Node* sacrifice = beforeDel->next;
		beforeDel->next = sacrifice->next;
		delete sacrifice;
		count--;
		if (beforeDel->next == nullptr)
		{
			tail = beforeDel;
		}
	}

	void Clear()
	{
		while (head != nullptr)
		{
			DeleteFromHead();
		}
	}

	void Print() const
	{
		if (count == 0)
		{
			cout << "Empty list!\n";
			return;
		}
		Node* current = head;
		while (current != nullptr)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	int GetCount() const
	{
		return count;
	}

	int IndexOf(int data) const
	{
		if (count == 0)
		{
			// cout << "Empty list!\n";
			return -1;
		}
		Node* temp = head;
		int i = 0;
		while (i < count)
		{
			if (data == temp->data)
			{
				return i;
			}
			i++;
			temp = temp->next;
		}

		return -1;
	}

	void Shuffl()
	{

		if (count == 0 || count == 1)return;

		int* ar = new int[count];
		Node* current = head;

		for (int i = 0; i < count; i++)
		{
			ar[i] = current->data;
			current = current->next;
		}

		random_shuffle(ar, ar + count);

		current = head;

		for (int i = 0; i < count; i++)
		{
			current->data = ar[i];
			current = current->next;
		}

		delete[]ar;
	}

	List* Clone() const
	{
		List* newList = new List();
		if (count == 0) return newList;

		Node* current = head;

		while (current != nullptr)
		{
			newList->AddToTail(current->data);
			current = current->next;
		}
		return newList;
	}

	void SetAt(int new_elem, int index)
	{
		

		if (index < 0 || index >= count)
		{
			cout << "Invalid index!\n";
			return;
		}
		Node* current = head;
		int currentIndex = 0;
		while (currentIndex < index)
		{
			current = current->next;
			currentIndex++;
		}
		current->data = new_elem;
	}

	int* ToArray() const
	{
		if (count == 0) return nullptr;
		int* arr = new int[count];

		Node* current = head;
		for (int i = 0; current != nullptr; i++)
		{
			arr[i] = current->data;
			current = current->next;
		}
		return arr;
	}

	void MergeWith(const List& sll)
	{

		if (sll.count == 0) return;

		if (count == 0)
		{
			*this = sll;
			return;
		}
		Node* lastNode = tail;
		while (lastNode->next != nullptr)
		{
			lastNode = lastNode->next;
		}
		Node* pluslist = sll.head;
		for (; pluslist != nullptr; pluslist = pluslist->next)
		{
			lastNode->next = new Node();
			lastNode->next->data = pluslist->data;
			lastNode = lastNode->next;
		}
		count += sll.count;
	}

	void Reverse()
	{
		if (count == 0 || count == 1)return;

		int* ar = new int[count];
		Node* current = head;

		for (int i = 0; i < count; i++)
		{
			ar[i] = current->data;
			current = current->next;
		}

		reverse(ar, ar + count);

		current = head;

		for (int i = 0; i < count; i++)
		{
			current->data = ar[i];
			current = current->next;
		}
		delete[]ar;
	}

	bool IsEmpty()
	{
		if (count == 0)
		{
			return false;
		}
		else 
			return true;
	}

	int LastIndexOf(int data)
	{
		if (count == 0 || count == 1)return -1;

		Node* current = head;
		int lastIndex = -1;
		int currentIndex = 0;

		while (current != nullptr)
		{
			if (current->data == data)
			{
				lastIndex = currentIndex;
			}
			current = current->next;
			currentIndex++;
		}
		return lastIndex;
	}

	void SortAsc()
	{
		if (count == 0 || count == 1)return;
		
		int* ar = new int[count];
		Node* current = head;
		
		for (int i = 0; i < count; i++)
		{
			ar[i] = current->data;
			current = current->next;
		}

		sort(ar, ar + count);

		current = head;

		for (int i = 0; i < count; i++)
		{
			current -> data = ar[i];
			current = current->next;
		}
		delete[]ar;
	}

	List& operator = (const List& original)
	{
		if (this == &original)return *this;

		this->Clear();

		Node* current = original.head;

		while (current != nullptr)
		{
			this->AddToTail(current->data);
			current = current->next;
		}
	}
};

bool operator == (const List a, const List b)
{
	return a.GetCount() == b.GetCount();
}

bool operator != (const List a, const List b)
{
	return a.GetCount() != b.GetCount();
}

int main()
{
	srand(time(NULL));
	List sll;
	
	for (int i = 0; i < 10; i++)
	{
		sll.AddToHead(rand() % 99);
	}
	sll.Print();

	List other;
	for (int i = 0; i < 10; i++)
	{
		other.AddToHead(rand() % 99);
	}
	/*other.MergeWith(sll);*/
	//cout << "\n\n\n==============================================\n\n\n";
	other.Print();
	cout << "\n\n\n==============================================\n\n\n";
	if (sll == other)
	{
		cout << "==" << "\n";
	}

	if (sll != other)
	{
		cout << "!=" << "\n";
	}

	//sll.SertDesc();
	//sll.Print();
	//cout << "\n\n\n==============================================\n\n\n";
	//cout<<sll.LastIndexOf(1);
	//cout << "\n\n\n==============================================\n\n\n";
 //   sll.Shuffl();
	//sll.Print();
	//List two;
	//sll.Clone();
	//cout << "\n\n\n==============================================\n\n\n";
	//sll.Print();
	//sll.SetAt(2, 2);
	//sll.Print();
	//sll.AddToTail(50);
	//sll.AddToTail(40);
	//sll.AddToTail(30);

	//sll.DeleteFromTail();

	//// вставка в конец списка
	//sll.AddToTail(10);
	//sll.AddToTail(20);
	//sll.AddToTail(30);
	//sll.AddToTail(40);
	//sll.Print();

	//// вставка в начало списка
	//sll.AddToHead(50);
	//sll.AddToHead(60);
	//sll.AddToHead(70);
	//sll.AddToHead(80);
	//sll.Print();

	//// количество элементов, поиск элементов
	//cout << "count: " << sll.GetCount() << "\n";
	//cout << "index of 70: " << sll.IndexOf(70) << ", index of 90: " << sll.IndexOf(90) << "\n";

	//// вставка по позиции
	//sll.InsertInto(-1, -1);
	//sll.Print();
	//sll.InsertInto(2, 2);
	//sll.Print();
	//sll.InsertInto(22, 22);
	//sll.Print();

	//// удаление с начала списка
	//sll.DeleteFromHead();
	//sll.DeleteFromHead();
	//sll.DeleteFromHead();
	//sll.Print();

	//// удаление с конца списка
	//sll.DeleteFromTail();
	//sll.DeleteFromTail();
	//sll.DeleteFromTail();
	//sll.Print();

	//// удаление по указанному индексу
	//sll.DeleteByIndex(0);
	//sll.DeleteByIndex(1);
	//sll.DeleteByIndex(2);
	//sll.Print();

	//// очистка списка
	//sll.Clear();
	//sll.Print();

	//List copy;
	//copy = sll;
	//copy.Print();
}
