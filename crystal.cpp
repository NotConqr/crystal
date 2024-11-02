#include <iostream>
#include <thread>
#include <chrono>

void wait(int sec);
void Header(std::string Head);

void Header(std::string Head) {
    #ifdef _WIN32
        SetConsoleTitle(Head.c_str());
    #else
        std::cout << "\033]0;" << Head << "\007";
    #endif
}

void wait(int sec) {
  system("color 6");
  std::this_thread::sleep_for(std::chrono::seconds(sec));
  system("color a");
}

int main() {
  Header("Crystal - CY.0.2")
  wait(5);
  std::cout << "Crystals - CY.0.2" << std::endl;
  wait(5);
}
