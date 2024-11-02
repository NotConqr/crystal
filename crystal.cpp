#include <iostream>
#include <thread>
#include <chrono>

void wait(int sec);

void wait(int sec) {
  system("color 6");
  std::this_thread::sleep_for(std::chrono::seconds(sec));
  system("color a");
}

int main() {
  wait(5);
  std::cout << "Crystals - CY.0.2" << std::endl;
  wait(5);
}