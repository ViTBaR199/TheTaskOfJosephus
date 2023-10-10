#include <iostream>

template<typename T>

//класс, реализующий кольцевой список
class circular_linked_list {
public:
	//узел для создания кольцевого списка
	//содержит информацию элемента, указатель на следующий и предыдущий элемент
	struct nodes {
		T data;
		int position;
		nodes* next;
		nodes* last;

		nodes(T _data, int _position) {
			data = _data;
			position = _position;
			next = nullptr;
			last = nullptr;
		}
	};
	nodes* top, * lower;

public:

	circular_linked_list() = default;
	//конструктор копирования
	circular_linked_list(const circular_linked_list& cll) {
		nodes* current = cll.top;
		if (current == nullptr) {
			return;
		}
		do
		{
			push_back(current->data);
			current = current->next;
		} while (current != cll.top);
	}
	//деструктор
	~circular_linked_list()
	{
		while (top != nullptr) {
			pop(top);
		}
	}
	//оператор присваивания
	circular_linked_list& operator=(const circular_linked_list& cll)
	{
		if (this == &cll || cll.top == nullptr) {
			return *this;
		}
		nodes* current = cll.top;
		do
		{
			push_back(current->data);
			current = current->next;
		} while (current != cll.top);
		return *this;
	}
	//конструктор перемещения
	circular_linked_list(circular_linked_list&& cll) {
		top = cll.top; //передача из передаваемого объекта cll
		lower = cll.lower;
		cll.top = nullptr;
		cll.tower = nullptr;
	}
	//присваивание перемещением
	circular_linked_list& operator=(circular_linked_list&& cll) {
		if (this == &cll) {
			return *this;
		}
		top = cll.top;
		lower = cll.lower;
		cll.top = nullptr;
		cll.lower = nullptr;
		return *this;
	}

	int size() {
		if (top == nullptr) {
			return 0;
		}
		int count = 0;
		nodes* current = top;
		do {
			count++;
			current = current->next;
		} while (current != top);
		return count;
	}

	//занесение нового-заданного значения
	void push_back(T data) {
		int current_size = size();
		nodes* new_nodes = new nodes{ data, current_size };
		if (top == nullptr) {
			top = new_nodes;
			top->next = lower;
			top->last = lower;
			lower = new_nodes;
			lower->next = top;
			lower->last = top;
		}
		else {
			new_nodes->last = lower;
			new_nodes->next = top;
			lower->next = new_nodes;
			top->last = new_nodes;
			lower = new_nodes;
		}
	}

	//удаление текущего-заданного объекта
	void pop(nodes* current) {
		if (current == top && current == lower) {
			top = nullptr;
			lower = nullptr;
		}
		else if (current == top) {
			top = current->next;
			lower->next = top;
			top->last = lower;
		}
		else if (current == lower) {
			lower = current->last;
			top->last = lower;
			lower->next = top;
		}
		else {
			current->last->next = current->next;
			current->next->last = current->last;
		}
		delete current;
	}
};

enum class direction {
	clockwise, counterclockwise
};

//Прототип функции, решающей задачу Иосифа Флавия
template<typename T>

std::pair<int, T> Josephus_problem(circular_linked_list<T>& list, direction dir, unsigned step) {
	typename circular_linked_list<T>::nodes* current = list.top;
	while (current->next != current) {
		for (unsigned i = 1; i < step; i++) {
			if (dir == direction::clockwise) {
				current = current->next;
			}
			else {
				current = current->last;
			}
		}

		typename circular_linked_list<T>::nodes* another_node;
		if (dir == direction::clockwise) {
			another_node = current->next;
		}
		else {
			another_node = current->last;
		}
		list.pop(current);
		current = another_node;
	}
	return std::make_pair(current->position, current->data);
}
//circulat_linked_list - кольцевой список
//dir - направление
//step - шаг, на котором идёт удаление объекта


int main()
{
	circular_linked_list<int> list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	circular_linked_list<int> copy_of_the_list = list; //проверка копирование

	circular_linked_list<int> assigning_a_list;
	assigning_a_list = list; //проверка присваивания
	std::pair<int, int> exemple = Josephus_problem(list, direction::clockwise, 2);
	std::cout << "Position: " << exemple.first << "\tcurrent: " << exemple.second << std::endl;
}
