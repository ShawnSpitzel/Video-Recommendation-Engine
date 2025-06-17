#include "iostream"
class WordVector {
    public:
        WordVector(){};
        void readWordVectors();
        std::unordered_map<std::string, std::vector<float>> wordVector;
    private:
        size_t vectorSize = 0;
};

