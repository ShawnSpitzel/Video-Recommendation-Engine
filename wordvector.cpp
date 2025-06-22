#include "wordvector.h"
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <sys/mman.h>

#define FILEPATH "/Users/shawnspitzel/Video Similarity Graph/word2vec.bin"
void WordVector::readWordVectors() {
    std::ifstream file(FILEPATH, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }
    std::string header_line;
    std::getline(file, header_line);
    std::istringstream header_stream(header_line);
    size_t num_words = 0;
    size_t vector_len = 0;
    header_stream >> num_words >> vector_len;
    vectorSize = vector_len;
    std::cout << "Reading file (binary)...\n";
    std::cout << "Number of words: " << num_words << ", Vector size: " << vector_len << "\n";
    for (size_t i = 0; i < num_words; ++i) {
        std::string word;
        char ch;
        while (file.get(ch) && ch != ' ') {
            word += ch;
        }
        std::vector<float> vec(vector_len);
        file.read(reinterpret_cast<char*>(vec.data()), vector_len * sizeof(float));
        if (file.fail()) {
            std::cerr << "Error reading vector data for word: " << word << "\n";
            break;
        }
        wordVector[word] = vec;
        vectorSize++;
    }
    std::cout << "Completed reading " << vectorSize << " words!\n";
    std::cout << "\n";
    file.close();
}
WordVector::WordVector() {
    readWordVectors();
}