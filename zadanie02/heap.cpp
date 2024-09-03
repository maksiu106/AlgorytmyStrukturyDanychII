#include <iostream>
#include <vector>
#include <sstream>

#include "heap.hpp"

void split(std::string input, std::vector<std::string>& v) {
	std::istringstream iss(input);
	std::string word;
	while (std::getline(iss, word, ' ')) {
		v.push_back(word);
	}
}

void send() {std::cout << "Invalid command" << std::endl;}

int main(int argc, char* argv[]) {
	PriorityQueue<std::string> pq;
	std::string input;
	while (std::getline(std::cin, input)) {
		std::vector<std::string> v;
		split(input, v);
		if (v[0] == "ADD") {
			if ((v.size() < 3)) send();
			else pq.insert(v[1], std::stoi(v[2]));
		} else if (v[0] == "REMOVE") {
			std::cout << pq.extractMax() << std::endl;
		} else if (v[0] == "PEEK") {
			std::cout << pq.peek() << std::endl;
		}
	}
}
