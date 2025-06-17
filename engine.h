
#ifndef VIDEO_SIMILARITY_GRAPH_ENGINE_H
#define VIDEO_SIMILARITY_GRAPH_ENGINE_H
#include "video.h"
#include "wordvector.h"

class Engine {
public:
    Video originalVideo;
    Video comparedVideos;
    WordVector wordVector;
    Engine(const Video& originalVideo, Video comparedVideos, WordVector wordVector);
    void processVideo(const Video& video);
};


#endif //VIDEO_SIMILARITY_GRAPH_ENGINE_H
