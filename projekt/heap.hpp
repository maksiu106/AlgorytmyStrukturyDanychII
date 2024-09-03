#ifndef HEAP_HPP_
#define HEAP_HPP_

#include <iostream>

template <class T>
class PriorityQueue {
private:
	struct QueueElement {
		int priority;
		T object;
		QueueElement(T x, int p) {
			priority = p;
			object = x;
		}
		QueueElement() = default;
		void newPriority(int p) {
			priority = p;
		}
	};

	QueueElement* data;
	int no_elements = 0;
	int array_size;

	int parent(int i) {return (i-1)/2;} //funkcja zwraca indeks rodzica
	int left(int i) { //funkcja zwraca indeks lewego dziecka
		int index = 2*i + 1;
		if (index >= no_elements) return -1;
		else return index;
	}
	int right(int i) { //funkcja zwraca indeks prawego dziecka
		int index = 2*i + 2;
		if (index >= no_elements) return -1;
		else return index;
	}

	void heapifyDown (int i) { //sprawdzanie od góry, czy kopiec jest zrównoważony. Wywołuje się od data[0]
		int lowest = i;
		if (data[left(i)].priority < data[lowest].priority && left(i) != -1) lowest = left(i);
		if (data[right(i)].priority < data[lowest].priority && right(i) != -1) lowest = right(i);
		if (lowest != i) {
			std::swap(data[i], data[lowest]);
			heapifyDown(lowest);
		}
	}

	void heapifyUp (int i) { //funkcja sprawdza od dołu, czy kopiec jest uporządkowany
		while (i > 0 && data[parent(i)].priority > data[i].priority) {
			std::swap(data[i], data[parent(i)]);
			i = parent(i);
		}
	}

	int find(T x) { //zwraca indeks w tablicy elementu o wybranej wartości
		for (int i=0; i<no_elements; ++i) {
			if (data[i].object == x) return i;
		}
		return -1;
	}

public:
	PriorityQueue(int n) {
		data = new QueueElement[n];
		array_size = n;
	}

	~PriorityQueue() {
		delete[] data;
	}

	void buildHeap() { //funkcja buduje kopiec z nieuporządkowanej tablicy
		for (int i = (no_elements-1)/2; i>=0; --i) {
			heapifyDown(i);
		}
	}

	void insert(T x, int p) {
		data[no_elements] = QueueElement(x, p);
		++no_elements;
		heapifyUp(no_elements-1);
	}

	void remove(T x) {
		int index = find(x);
		if (index == -1) return;
		std::swap(data[index], data[no_elements-1]);
		--no_elements;
		heapifyDown(index);
	}

	void change(T x, int p) { //metoda aktualizuje wagę danego elementu
		int index = find(x);
		data[index].newPriority(p);
		heapifyUp(index);
	}

	T extractMin() {
		if (no_elements == 0) {
			return -1;
		}
		T to_return = data[0].object;
		remove(to_return);
		return to_return;
	}

	T peek() {
		if (no_elements == 0) {
			return -1;
		}
		return data[0].object;
	}

	bool empty() {
		return no_elements == 0;
	}
};
#endif /* HEAP_HPP_ */
