#include "video.h"
Video::Video(int id, int length, std::string description, std::string title, std::vector<std::string> tags):
    id(id),
    length(length),
    description(description),
    title(title),
    tags(tags)
{}