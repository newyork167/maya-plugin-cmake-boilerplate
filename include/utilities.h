#pragma once

#include <string>

std::string load_file_to_string(std::string file_path) {
    // Load file from path to ifstream
    std::ifstream file(file_path);
    if (!file) {
        cout << "unable to open file";
        return "";
    }

    // Load file into string
    std::string file_str, return_str;
    while (getline(file, file_str)) {
        return_str += file_str;
    }

    return return_str;
}