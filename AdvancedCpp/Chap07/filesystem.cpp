#include <iostream>
#include <vector>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

void newline() {
    std::cout << '\n';
}

void printdir(const fs::path& p) {
    using de = fs::directory_entry;
    std::vector<de> dir;

    auto dircmp = [](const de& lhs, const de& rhs) -> bool {
        return lhs.path().string() < rhs.path().string();
    };

    if (!fs::exists(p)) {
        std::cout << fs::absolute(p) << " does not exist\n";
        return;
    }

    if (fs::is_directory(p)) {
        for (const auto& de : fs::directory_iterator{ p }) {
            dir.emplace_back(de);
        }
        std::sort(dir.begin(), dir.end(), dircmp);
        for (const auto& e : dir) {
            std::cout << fs::relative(e, p) << ' ';
        }
        newline();
    } else {
        std::cout << "not a directory: " << p << '\n';
    }
}

constexpr const char* fp{ "testdir/foo.txt" };
constexpr const char* homedir{ "/Users/billw/Xcode/ExerciseFiles" };

int main() {
    fs::path p{ fp };
    std::cout << "p: " << p << '\n';

    if (!fs::exists(homedir)) {
        std::cout << fs::absolute(homedir) << " does not exist\n";
        return 1;
    }

    try {
        std::cout << "current_path: " << fs::current_path() << '\n';
        std::cout << "change current_path to " << homedir << '\n';
        fs::current_path(homedir);
        newline();

        std::cout << "current_path: " << fs::current_path() << '\n';
        std::cout << "absolute(p): " << fs::absolute(p) << '\n';
        newline();

        std::cout << "concatenate: " << (fs::path{ "testdir" } += "foo.txt") << '\n';
        std::cout << "append: " << (fs::path{ "testdir" } /= "foo.txt") << '\n';
        newline();

        std::cout << "canonical (.): " << fs::canonical(fs::path(".")) << '\n';
        newline();

        auto dirpath = fs::path(".") / "chap01";
        std::cout << "Directory of " << dirpath << ":\n";
        printdir(dirpath);

    } catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << '\n';
        std::cout << "path1: " << e.path1() << '\n';
        std::cout << "path2: " << e.path2() << '\n';
    }
}
