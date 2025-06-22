#include "engine.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
Engine::Engine(const Video& originalVideo, const Video& comparedVideos, WordVector& wordVector) :
    originalVideo(originalVideo),
    comparedVideos(comparedVideos),
    wordVector(wordVector)
{
    std::cout<< "Comparing " << originalVideo.title << " and " << comparedVideos.title <<"\n";
    std::cout<<"\n";
}
std::vector<float> averageVector(const std::vector<std::vector<float>>& vectors) {
    if (vectors.empty()) return {};
    size_t dim = vectors[0].size();
    std::vector<float> avg(dim, 0.0f);
    for (const auto& vec : vectors) {
        for (size_t i = 0; i < dim; ++i) {
            avg[i] += vec[i];
        }
    }
    for (float& val : avg) {
        val /= static_cast<float>(vectors.size());
    }
    if (avg.empty()){
        std::cerr<<"Average vector is empty \n";
        exit(-1);
    }
    return avg;
}
float cosineSimilarity(std::vector<float> a, std::vector<float> b){
    float dot = 0.0f, normA = 0.0f, normB = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        dot += a[i] * b[i];
        normA += a[i] * a[i];
        normB += b[i] * b[i];
    }
    float score = dot / (std::sqrt(normA) * std::sqrt(normB));
    if (std::isnan(score)){
        std::cerr<<"Error computing score, score is NaN \n";
        return -1.0;
    }
    return dot / (std::sqrt(normA) * std::sqrt(normB));
}

std::vector<std::vector<float>> vectorizeString(const std::string& string, std::unordered_map<std::string, std::vector<float>>& wordVector){
    std::vector<std::vector<float>> vectorized_string;
    std::istringstream stream (string);
    std::string word;
    while ( stream >> word ) {
        std::string stripped;
        for( char c : word ) if( std::isalnum(c) ) stripped += c ;
        word = stripped;
        auto it = wordVector.find(word);
        if (it == wordVector.end()) {
            std::cout << "Word " << word << " not found in WordVector\n";
        } else {
            const std::vector<float> &vec = it->second;
            vectorized_string.push_back(vec);
        }
    }
    return vectorized_string;
}
void Engine::processVideo(Video& video){
    std::vector<std::vector<float>> vectorized_title = vectorizeString(video.title, wordVector.wordVector);
    std::vector<std::vector<std::vector<float>>> vectorized_tags;
    for (const auto & i : video.tags){
        std::vector<std::vector<float>> tag = vectorizeString(i, wordVector.wordVector);
        vectorized_tags.push_back(tag);
    }
    std::vector<std::vector<float>> vectorized_desc = vectorizeString(video.description, wordVector.wordVector);
    video.vectorized_title = vectorized_title;
    video.vectorized_tags = vectorized_tags;
    video.vectorized_description = vectorized_desc;
}
float Engine::similarityCheck(const Video& video, const Video& comparedVideo){
    float score = 0.0;
    //Check similarity of titles
    if (!video.vectorized_title.empty() && !comparedVideo.vectorized_title.empty()){
        std::vector<float> avgTitles1 = averageVector(video.vectorized_title);
        std::vector<float> avgTitles2 = averageVector(comparedVideo.vectorized_title);
        if (avgTitles1.empty()){
            std::cerr<<"Original video's title is empty. \n";
        }
        if (avgTitles2.empty()){
            std::cerr<<"Compared video's title is empty. \n";
        }
        float title_similarity = cosineSimilarity(avgTitles1, avgTitles2);
        score += title_similarity;
    }
    else{
        std::cerr<<"A video's vectorized title is empty. \n";
        score = -1.0;
    }
    //Check similarity of tags
    if (!video.vectorized_tags.empty() && !comparedVideo.vectorized_tags.empty()){
        std::vector<std::vector<float>> averagedTags1;
        std::vector<std::vector<float>> averagedTags2;
        for (const auto& tag : video.vectorized_tags){
            std::vector<float> avgTagScore = averageVector(tag);
            averagedTags1.push_back(avgTagScore);
        }
        for (const auto& tag : comparedVideo.vectorized_tags){
            std::vector<float> avgTagScore = averageVector(tag);
            averagedTags2.push_back(avgTagScore);
        }
        std::vector<float> avgTags1 = averageVector(averagedTags1);
        std::vector<float> avgTags2 = averageVector(averagedTags2);
        if (avgTags1.empty()){
            std::cerr<<"Original video's tags is empty. \n";
        }
        if (avgTags2.empty()){
            std::cerr<<"Compared video's tags is empty. \n";
        }
        float tag_similarity = cosineSimilarity(avgTags1, avgTags2);
        score += tag_similarity;
    }
    else{
        std::cerr<<"A video's vectorized description is empty. \n";
        score = -1.0;
    }
    //Check similarity of descriptions
    if (!video.vectorized_description.empty() && !comparedVideo.vectorized_description.empty()){
        std::vector<float> avgTitles1 = averageVector(video.vectorized_description);
        std::vector<float> avgTitles2 = averageVector(comparedVideo.vectorized_description);
        if (avgTitles1.empty()){
            std::cerr<<"Original video's descripton is empty. \n";
        }
        if (avgTitles2.empty()){
            std::cerr<<"Compared video's description is empty. \n";
        }
        float title_similarity = cosineSimilarity(avgTitles1, avgTitles2);
        score += title_similarity;
    }
    else{
        std::cerr<<"A video's vectorized description is empty. \n";
        score = -1.0;
    }
    //Check similarity of lengths
    //Add up all the scores
    return score/3;
}