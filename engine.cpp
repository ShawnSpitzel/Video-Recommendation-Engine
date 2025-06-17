#include "engine.h"
#include <iostream>
#include <numeric>
#include <Eigen/Core>
#include <sstream>
#include <string>
#include <cctype>
Engine::Engine(const Video& originalVideo, Video comparedVideos, WordVector wordVector) :
    originalVideo(originalVideo),
    comparedVideos(comparedVideos),
    wordVector(wordVector)
{
    std::cout<< "Comparing " << originalVideo.title << "..." <<"\n";
}
double cosineSimilarity(const Eigen::Vector3d& x, const Eigen::Vector3d& y){
    double score = (x.dot(y))/(x.norm() * y.norm());
    return score;
}

std::vector<std::vector<float>> vectorizeString(const std::string& string, std::unordered_map<std::string, std::vector<float>> wordVector){
    std::vector<float> vectorized_word;
    std::vector<std::vector<float>> vectorized_string;
    std::istringstream stream (string);
    std::string word;
    auto it = wordVector.find(string);
    if (it == wordVector.end()) {
        std::cout << "Word "<< string <<" not found in WordVector\n";
    } else {
        const std::vector<float> &vec = it->second;

        std::cout << "Vector for "<< string <<" (" << vec.size() << " dimensions):\n";

        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
    }
//    while (stream >> word) {
//        transform(word.begin(), word.end(), word.begin(),::tolower);
//        try {
//            vectorized_word = wordVector.at(word);
//            std::cout << "Reading vector for word: " << word << '\n';
//            vectorized_string.push_back(vectorized_word);
//            std::cout << "Size of vectorized word: " << vectorized_word.size() << "\n";
//        } catch (const std::out_of_range& e) {
//            std::cerr << "Word not found in WordVector: " << word << '\n';
//        }
//    }
    return vectorized_string;
}
void Engine::processVideo(const Video& video){
    //Vectorize title
    wordVector.readWordVectors();
    std::vector<std::vector<float>> vectorized_title = vectorizeString(video.tags[1], wordVector.wordVector);
    std::cout << "Size of vectorized title: " << vectorized_title.size() << "\n";

    //Vectorize tags
    //Vectorize description
    //Vectorize length
}
double similarityCheck(const Video& originalVideo, const Video& comparedVideos){
    double score = 0.0;
    //Check similarity of titles
    //Check similarity of tags
    //Check similarity of descriptions
    //Check similarity of lengths
    //Add up all the scores
    return score;
}