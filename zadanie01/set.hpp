#include <iostream>

#include "tokenize.hpp"

template <class T>
class Set {
private:
	T* array;
	int no_elements = 0;
	int array_size;

	void enlarge() {
		T* temp = array;
		array = new T[2*array_size];
		array_size = 2*array_size;
		for (int i=0; i<no_elements; ++i) {
			array[i] = temp[i];
		}
		delete[] temp;
	}

	void reduce() {
		T* temp = array;
		array = new T[array_size/2];
		array_size = array_size/2;
		for (int i=0; i<no_elements; ++i) {
			array[i] = temp[i];
		}
		delete[] temp;
	}

	int find(T element) { //metoda szuka elementu w zbiorze
		for (int i=0; i < no_elements; ++i) {
			if (array[i] == element) return i;
		}
		return -1;
	}

public:
	Set() {
		array = new T[100];
		array_size = 100;
	}

	~Set() {
		delete[] array;
	}

	bool isMember(T element) {
		if (find(element) == -1) return false;
		else return true;
	}

	void insert(T element) { //metoda dodaje element do zbioru
		if (find(element) != -1) return; //jeśli jest już, nie dodaje nic
		if (no_elements+1 == array_size) enlarge();
		if (no_elements == 0) {
			array[0] = element;
			++no_elements;
			return;
		} else {
			int i = no_elements-1; //indeks ostatniego elementu
			while (array[i] > element && i>0) {
				array[i+1] = array[i];
				--i;
			}
			array[i+1] = element;
			++no_elements;
		}
	}

	//funkcja używana do operacji na zbiorach - nie sprawdza, czy element już jest w danym zbiorze
	//nie jest to potrzebne ze względu na przyjęty algorytm, a zaoszczędza to na złożoności
	void quick_insert(T element) {
		if (no_elements+1 == array_size) enlarge();
		if (no_elements == 0) {
			array[0] = element;
			++no_elements;
			return;
		}
		else {
			int i = no_elements-1; //indeks ostatniego elementu
			while (array[i] > element && i>0) {
				array[i+1] = array[i];
				--i;
			}
			array[i+1] = element;
			++no_elements;
		}
	}

	void remove(T element) {
		int position = find(element);
		if (position == -1) return;
		for (int i = position; i<no_elements; ++i) {
			array[i] = array[i+1];
		}
		--no_elements;
		if ((no_elements < array_size/4) && (array_size > 100)) reduce();
	}

	int size() {
		return no_elements;
	}

	void file_to_set(std::string filename) { //metoda do wczytywania zbioru z pliku
		std::vector<T> v = readAndTokenize(filename);
		for (T element : v) {
			insert(element);
		}
	}

	void print() {
		for (int i=0; i<no_elements; ++i) {
			std::cout << array[i] << std::endl;
		}
	}

	//w poniższych funkcjach nie używa się zwykłego insertu
	//za każdym razem przechodzi on całą tablicę wyników (aby uniknąć duplikacji), co pogarsza złożoność
	//ponieważ przy takiej implementacji tych funkcji można mieć pewność, że wstawiane wyrazy nie będą się powtarzać
	Set<T> set_intersection(Set<T>& s2) {
		Set<T> result;
		int pivot = 0;
		int index = 0;
		while ((index < no_elements) && (pivot < s2.no_elements)) {
			if (array[index] == s2.array[pivot]) { //kiedy są takie same elementy
				result.quick_insert(array[index]);
				++index;
				++pivot;
			}
			else if (array[index] < s2.array[pivot]) { //kiedy elementy w s2 stają się większe od elementów w s1
				++index;
			}
			else { //kiedy nie są równe, ale trzeba szukać dalej w s2
				++pivot;
			}
		}
		return result;
	}

	Set<T> set_union(Set<T>& s2) {
	    Set<T> result;
	    int index = 0;
	    int pivot = 0;
	    while ((index < no_elements) && (pivot < s2.no_elements)) {
	    	if (array[index] == s2.array[pivot]) { //kiedy znajduje takie same elementy
	    		result.quick_insert(array[index]);
	    		++index;
	    		++pivot;
	    	}
	    	else if (array[index] < s2.array[pivot]) {
	    		result.quick_insert(array[index]);
	    		++index;
	    	}
	    	else {
	    		result.quick_insert(s2.array[pivot]);
	    		++pivot;
	    	}
	    }
	    //kiedy wyjdzie z pętli, trzeba sprawdzić, czy oba zbiory zostały zbadane aż do końca
	    while (pivot < s2.no_elements) {
	    	result.quick_insert(s2.array[pivot]);
	    	++pivot;
	    }
	    while (index < no_elements) {
	    	result.quick_insert(array[index]);
	    	++index;
	    }
	    return result;
	}

	Set<T> set_difference(Set<T>& s2) {
		Set<T> result;
		int index = 0;
		int pivot = 0;
		while ((index < no_elements) && (pivot < s2.no_elements)) {
			if (array[index] == s2.array[pivot]) { //kiedy znajduje takie same elementy
		   		++index;
		   		++pivot;
		   	}
			else if (array[index] < s2.array[pivot]) {
				result.quick_insert(array[index]);
		    	++index;
			}
	    	else {
	    		++pivot;
	    	}
	    }
		while (index < no_elements) {
			result.quick_insert(array[index]);
	    	++index;
	    }
		return result;
	}
};
