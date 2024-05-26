#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

void printFullPath(std::ostream& os, const fs::path& entryPath, const fs::path& filePath) {
    fs::path relativePath = fs::relative(filePath, entryPath);
    std::vector<std::string> directories;
    for (auto& p : relativePath) {
        directories.push_back(p.string());
    }
    std::reverse(directories.begin(), directories.end());
    for (const auto& dir : directories) {
        os << dir << " ";
    }
    os << filePath.filename() << std::endl;
}

void traverseDirectory(std::ostream& os, const fs::path& entryPath) {
    for (const auto& entry : fs::recursive_directory_iterator(entryPath)) {
        if (!entry.is_directory()) {
            printFullPath(os, entryPath, entry.path());
        }
    }
}

// 接受一个目录的绝对路径参数，将该目录下所有文件按文件链的形式写入到 ../temp/fileChain 中
// 这个绝对路径参数由程序调用者给出
int main(int argc, char **argv)
{
    /* 处理参数并保存读取路径 */
    std::string arg(argv[1]);
    if (argc < 2 || (arg[0] != '-' || arg[1] != 'd')) {
        std::cerr << argv[0] << ": " << "Arguments error!" << std::endl;
        return -1;
    }
    std::string dir(arg.c_str() + 2);

    /* TODO: 创建文件输出流 */
    std::ofstream os("../temp/fileChain");      // 上层应用保证 temp 目录存在
    fs::path entryPath(dir);
    if(fs::is_directory(entryPath)) {
        traverseDirectory(os, entryPath);
    }

    return 0;
}