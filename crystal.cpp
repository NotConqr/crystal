#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

void wait(int sec);
void Header(const std::string& Head);

void Header(const std::string& Head) {
    #ifdef _WIN32
        SetConsoleTitle(Head.c_str());
    #else
        std::cout << "\033]0;" << Head << "\007";
    #endif
}

void wait(int sec) {
    #ifdef _WIN32
        system("color 6");  // Set color to yellow on Windows
    #endif
    std::this_thread::sleep_for(std::chrono::seconds(sec));
    #ifdef _WIN32
        system("color a");  // Set color back to green on Windows
    #endif
}

int main() {
    Header("Crystal - CY.0.3");
    wait(5);
    std::cout << "Crystals - CY.0.3" << std::endl;
    wait(5);
    return 0;
}
