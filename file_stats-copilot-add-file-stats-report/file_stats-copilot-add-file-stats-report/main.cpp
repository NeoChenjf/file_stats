#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int main(int argc, char* argv[]) {
    // Check if filename is provided
    if (argc != 2) {
        std::cerr << "用法: " << argv[0] << " <文件名>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream inputFile(filename);

    // Check if file can be opened
    if (!inputFile.is_open()) {
        std::cerr << "Error: 无法打开文件 '" << filename << "'" << std::endl;
        std::cerr << "请检查文件是否存在以及您是否有权限读取它" << std::endl;
        return 1;
    }
	
    // Initialize counters
    int lineCount = 0;
    int wordCount = 0;
    int charCount = 0;

    char ch;
    bool inWord = false;
    
    // Read file character by character
    while (inputFile.get(ch)) {
        charCount++;
        
        if (ch == '\n') {
            lineCount++;
            inWord = false;
        } else if (std::isspace(ch)) {
            inWord = false;
        } else {
            if (!inWord) {
                wordCount++;
                inWord = true;
            }
        }
    }

    // Check if there was an error reading the file
    if (inputFile.bad()) {
        std::cerr << "Error: 读取失败 '" << filename << "'" << std::endl;
        inputFile.close();
        return 1;
    }

    inputFile.close();

    // Output report
    std::cout << "====================" << std::endl;
	std::cout << "文件统计报告" << std::endl;//文件统计报告
    std::cout << "====================" << std::endl;
    std::cout << "File: " << filename << std::endl;
    std::cout << "Lines: " << lineCount << std::endl;
    std::cout << "Words: " << wordCount << std::endl;
    std::cout << "Characters: " << charCount << std::endl;
    std::cout << "====================" << std::endl;

    return 0;
}
