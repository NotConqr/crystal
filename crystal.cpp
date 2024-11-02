#include <iostream>
#include <thread>
#include <chrono>

void wait(int sec);

void wait(int sec) {
  std::this_thread::sleep_for(std::chrono::seconds(sec));
}

int main() {
  std::cout << "crystal sever not avalible" << std::endl;
  wait(20);
}
