
#ifndef VIDEO_SIMILARITY_GRAPH_ENGINE_H
#define VIDEO_SIMILARITY_GRAPH_ENGINE_H
#include "video.h"
#include "wordvector.h"

class Engine {
public:
    Video originalVideo;
    Video comparedVideos;
    WordVector& wordVector;
    Engine(const Video& originalVideo, const Video& comparedVideos, WordVector& wordVector);
    void processVideo(Video& video);
    float similarityCheck(const Video& originalVideo, const Video& comparedVideo);
};


#endif //VIDEO_SIMILARITY_GRAPH_ENGINE_H
