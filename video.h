
#ifndef VIDEO_SIMILARITY_GRAPH_VIDEO_H
#define VIDEO_SIMILARITY_GRAPH_VIDEO_H
#include "string"
#include "vector"
class Video {
public:
    int id;
    int length; //length in seconds
    std::string description;
    std::string title;
    std::vector<std::string> tags;
    std::vector<std::vector<float>> vectorized_title;
    std::vector<std::vector<float>> vectorized_description;
    std::vector<std::vector<std::vector<float>>> vectorized_tags;
    Video(int id, int length, std::string description, std::string title, std::vector<std::string> tags);
};

#endif
