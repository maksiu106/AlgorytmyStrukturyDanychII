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
	};

	QueueElement* data;
	int no_elements = 0;
	int array_size;

	void enlarge() {
		QueueElement* temp = data;
		data = new QueueElement[2*array_size];
		array_size = 2*array_size;
		for (int i=0; i<no_elements; ++i) {
			data[i] = temp[i];
		}
		delete[] temp;
	}

	void reduce() {
		QueueElement* temp = data;
		data = new QueueElement[array_size/2];
		array_size = array_size/2;
		for (int i=0; i<no_elements; ++i) {
			data[i] = temp[i];
		}
		delete[] temp;
	}

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
		int largest = i;
		if (data[left(i)].priority > data[largest].priority && left(i) != -1) largest = left(i);
		if (data[right(i)].priority > data[largest].priority && right(i) != -1) largest = right(i);
		if (largest != i) {
			std::swap(data[i], data[largest]);
			heapifyDown(largest);
		}
	}

	void heapifyUp (int i) { //funkcja sprawdza od dołu, czy kopiec jest uporządkowany
		while (i > 0 && data[parent(i)].priority < data[i].priority) {
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
	PriorityQueue() {
		data = new QueueElement[100];
		array_size = 100;
	}

	~PriorityQueue() {
		delete[] data;
	}

	void buildHeap() { //funkcja buduje kopiec z nieuporządkowanej tablicy
		for (int i = (no_elements-1)/2; i>0; --i) {
			heapifyDown(i);
		}
	}

	void insert(T x, int p) {
		data[no_elements] = QueueElement(x, p);
		++no_elements;
		if (no_elements == array_size) enlarge();
		heapifyUp(no_elements-1);
	}

	void remove(T x) {
		int index = find(x);
		if (index == -1) return;
		std::swap(data[index], data[no_elements-1]);
		--no_elements;
		heapifyDown(index);
		if (no_elements < array_size/4) reduce();
	}

	T extractMax() {
		if (no_elements == 0) {
			return "EMPTY";
		}
		T to_return = data[0].object;
		remove(to_return);
		return to_return;
	}

	T peek() {
		if (no_elements == 0) {
			return "EMPTY";
		}
		return data[0].object;
	}
};
#endif /* HEAP_HPP_ */
