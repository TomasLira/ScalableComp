#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

void increment(int &counter, std::mutex &m) {
    for (int i = 0; i < 1000000; i++) {
        std::lock_guard<std::mutex> lock(m);
        counter++;
    }
}

int main() {
    int threads_num = 4; 
    int counter = 0;  
    std::mutex m;  
    std::vector<std::thread> threads;

    for (int i = 0; i < threads_num; i++) {
        threads.emplace_back(increment, std::ref(counter), std::ref(m));
    }

    for (auto &t : threads) {
        t.join();
    }

    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}
