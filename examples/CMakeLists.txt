add_executable(main main.cpp)

target_link_libraries(main PRIVATE zip_compress)
target_link_libraries(main PRIVATE ghc_filesystem)