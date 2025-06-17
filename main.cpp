#include <iostream>
#include "engine.h"
#include "video.h"
int main(){
    Video video(1, 93, "Sushi videos!", "Top 5 sushi", {"sushi", "food", "asian", "japanese"});
    Video video2(250, 250, "Scuba diving adventure.", "Exploring the Great Barrier Reef!", {"scuba", "ocean", "adventure", "wildlife"});
    Video video3(3, 90, "Space rocket launch.", "Behind the Scenes at SpaceX!", {"space", "technology", "rockets", "exploration"});
    Video video4(4, 45, "Fitness home workout.", "10-minute Core Workout!", {"fitness", "health", "workout", "core"});
    Video video5(5, 300, "Guitar tutorial.", "Learn to Play 'Wonderwall' in 5 Minutes!", {"guitar", "tutorial", "music", "beginner"});
    Video video6(6, 160, "Pottery making process.", "Turning Clay into Art!", {"pottery", "art", "crafts", "creative"});
    std::vector<Video> videos = {video2, video3, video4, video5, video6};
    WordVector wordVector;
    Engine engine(video, video2, wordVector);
    engine.processVideo(video);
//    for (int i = 0; i < videos.size(); i++){
//        processedComparedVideo = processVideo(videos[i]); // Video where each attribute is a vector
//        double score = similarityCheck(processedVideo, processedComparedVideo);
//        std::cout<<processedComparedVideo.title<<" vs " << processedComparedVideo.title<<": " << score<<"\n";
//    }
std::cout<<"Engine finished \n";
    return 0;
}