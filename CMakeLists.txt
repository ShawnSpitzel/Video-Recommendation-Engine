cmake_minimum_required(VERSION 3.31)
project(Video_Similarity_Graph)

set(CMAKE_CXX_STANDARD 20)

add_executable(Video_Similarity_Graph main.cpp
        video.cpp
        video.h
        engine.cpp
        engine.h
        wordvector.cpp
        wordvector.h
)
target_include_directories(Video_Similarity_Graph PRIVATE
        "/Users/shawnspitzel/Video Similarity Graph/third-party/eigen-3.4.0"
)