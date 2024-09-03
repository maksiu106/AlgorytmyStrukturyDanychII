#include <iostream>
#include <vector>

#include "set.hpp"

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cout << "Dostarczono niewłaściwą liczbę argumentów wywołania programu" << std::endl;
		return -1;
	}

	//wczytywanie plików i budowanie zbiorów
	std::string command = argv[1];
	Set<std::string> s1;
	Set<std::string> s2;
	s1.file_to_set(argv[2]);
	s2.file_to_set(argv[3]);

	if (command == "common_words") {
		Set<std::string> result = s1.set_intersection(s2);
		result.print();
	} else if (command == "unique_words") {
		std::cout << argv[2] << ":" << std::endl;
		Set<std::string> result1 = s1.set_difference(s2);
		result1.print();
		std::cout << argv[3] << ":" << std::endl;
		Set<std::string> result2 = s2.set_difference(s1);
		result2.print();
	} else if (command == "all_words") {
		Set<std::string> result = s1.set_union(s2);
		result.print();
	}
}
