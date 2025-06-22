## Data Loading - In Progress
    - Using Word2Vec, load 3M words into a dictionary to store key value pairs
        - Currently using .bin as a .txt file was too large (10 minutes load), but .bin is still rather slow (31 seconds to read all words)
        - Works, but takes upwards of 20 minutes. Need to optimize further
                - Optimize data read
                    -Utilize mmap function to map file into memory, read from memory into word vector
                        New time (1m03s) is much slower
                - Optimize function call
    - Memory Map Implementation:
        #include "wordvector.h"
        #include <sstream>
        #include <string>
        #include <vector>
        #include <sys/file.h>
        #include <sys/mman.h>
        #include <unistd.h>
        
        #define FILEPATH "/Users/shawnspitzel/Video Similarity Graph/word2vec.bin"
        #define VECTOR_SIZE 300
        #define NUM_WORDS 3000000
        void WordVector::readWordVectors() {
        
            int fd = open(FILEPATH, O_RDONLY);
            if (fd == -1) {
                std::cerr << "Error opening file\n";
                return;
            }
            off_t fileSize = lseek(fd, 0, SEEK_END);
            lseek(fd, 0, SEEK_SET);
            void* raw = mmap(0, fileSize, PROT_READ, MAP_SHARED, fd, 0);
            if (raw == MAP_FAILED){
                close(fd);
                perror("Error mmapping the file");
                exit(EXIT_FAILURE);
            }
            char* data = static_cast<char*>(raw);
            size_t offset = 0;
            size_t index = 0;
            std::cout << "Number of words: " << NUM_WORDS << ", Vector size: " << VECTOR_SIZE << "\n";
            std::cout << "Reading file...\n";
            while (data[offset] != '\n' && offset < fileSize) {
                offset++;
            }
            offset++;
            for (size_t i = 0; i < NUM_WORDS; ++i) {
                std::string word;
                while (data[index] != ' ' && index < fileSize){
                    word += data[index];
                    index++;
                }
                index++;
                std::vector<float> vec(VECTOR_SIZE);
                if ((offset + VECTOR_SIZE * sizeof(float)) > fileSize){
                    perror("File size exceeded");
                    exit(EXIT_FAILURE);
                } else {
                    std::memcpy(vec.data(), data + offset, VECTOR_SIZE * sizeof(float));
                    offset += VECTOR_SIZE * sizeof(float);
                }
                if (data[offset] == '\n') {
                    offset++;
                }
                wordVector[word] = vec;
                vectorSize++;
            }
            if (munmap(data, fileSize) == -1){
                std::cerr<<"Error closing memory mapping";
            }
            close(fd);
            std::cout << "Completed reading " << vectorSize << " words!\n";
        }
        WordVector::WordVector() {
        readWordVectors();
        }