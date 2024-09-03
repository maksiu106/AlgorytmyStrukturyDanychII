#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cctype>

inline std::vector<std::string> readAndTokenize(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::string processedText;
    
    if (file.is_open()) {
        while (std::getline(file, line)) {
            for (char &ch : line) {
                if (std::isalpha(ch)) {
                    processedText += std::tolower(ch);
                } else if (!processedText.empty() && processedText.back() != ' ') {
                    processedText += ' ';
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
        exit(1);
    }
    
    std::istringstream iss(processedText);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        if (token.size() > 2)
            tokens.push_back(token);
    }
    
    return tokens;
}
