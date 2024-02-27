#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void displayMenu() {
    std::cout << "\n===== Command-Line File Manager =====\n";
    std::cout << "1. View files in the current directory\n";
    std::cout << "2. Navigate to a directory\n";
    std::cout << "3. Create a directory\n";
    std::cout << "4. Copy a file\n";
    std::cout << "5. Move a file\n";
    std::cout << "6. Exit\n";
    std::cout << "=====================================\n";
}

void viewFiles(const std::string& currentDir) {
    std::cout << "Files in " << currentDir << ":\n";
    for (const auto& entry : fs::directory_iterator(currentDir)) {
        std::cout << entry.path().filename() << "\n";
    }
}

void navigateDirectory(std::string& currentDir) {
    std::string newDir;
    std::cout << "Enter the directory to navigate to: ";
    std::cin >> newDir;

    fs::path newPath = currentDir;
    newPath /= newDir;

    if (fs::exists(newPath) && fs::is_directory(newPath)) {
        currentDir = newPath;
        std::cout << "Current directory changed to: " << currentDir << "\n";
    } else {
        std::cout << "Directory not found.\n";
    }
}

void createDirectory(const std::string& currentDir) {
    std::string newDir;
    std::cout << "Enter the name of the new directory: ";
    std::cin >> newDir;

    fs::path newDirPath = currentDir;
    newDirPath /= newDir;

    if (fs::create_directory(newDirPath)) {
        std::cout << "Directory created: " << newDirPath << "\n";
    } else {
        std::cout << "Failed to create directory.\n";
    }
}

void copyFile(const std::string& currentDir) {
    std::string sourceFileName, destFileName;
    std::cout << "Enter the name of the file to copy: ";
    std::cin >> sourceFileName;

    fs::path sourcePath = currentDir;
    sourcePath /= sourceFileName;

    if (!fs::exists(sourcePath)) {
        std::cout << "File not found.\n";
        return;
    }

    std::cout << "Enter the destination directory: ";
    std::cin >> destFileName;

    fs::path destPath = currentDir;
    destPath /= destFileName;

    try {
        fs::copy(sourcePath, destPath);
        std::cout << "File copied to: " << destPath << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void moveFile(const std::string& currentDir) {
    std::string sourceFileName, destFileName;
    std::cout << "Enter the name of the file to move: ";
    std::cin >> sourceFileName;

    fs::path sourcePath = currentDir;
    sourcePath /= sourceFileName;

    if (!fs::exists(sourcePath)) {
        std::cout << "File not found.\n";
        return;
    }

    std::cout << "Enter the destination directory: ";
    std::cin >> destFileName;

    fs::path destPath = currentDir;
    destPath /= destFileName;

    try {
        fs::rename(sourcePath, destPath);
        std::cout << "File moved to: " << destPath << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    std::string currentDir = fs::current_path();
    int choice;

    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                viewFiles(currentDir);
                break;
            case 2:
                navigateDirectory(currentDir);
                break;
            case 3:
                createDirectory(currentDir);
                break;
            case 4:
                copyFile(currentDir);
                break;
            case 5:
                moveFile(currentDir);
                break;
            case 6:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
