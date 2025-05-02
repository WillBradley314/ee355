#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <algorithm>

const int NUM_PHILOSOPHERS = 5;
const int NUM_CYCLES = 10;

std::mutex chopsticks[NUM_PHILOSOPHERS];

// This will cause deadlock
void philosopher_resource_ordering(int id) {
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    for (int i = 0; i < NUM_CYCLES; ++i) {
        std::cout << "[P" << id << "] Thinking...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100 + id * 10));

        if (left < right) {
            
            std::cout << "[P" << id << "] Hungry, trying to pick up left " << left << ", then right " << right << "\n";

            chopsticks[left].lock();
            std::cout << "[P" << id << "] Got left chopstick " << left << "\n";
            
            // Add a delay between picking up chopsticks to increase deadlock chance
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            
            chopsticks[right].lock();
            std::cout << "[P" << id << "] Got right chopstick " << right << "\n";

            std::cout << "[P" << id << "] Eating...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            chopsticks[right].unlock();
            chopsticks[left].unlock();
        }
        else {
            
            std::cout << "[P" << id << "] Hungry, trying to pick up right " << right << ", then left " << left << "\n";

            chopsticks[right].lock();
            std::cout << "[P" << id << "] Got right chopstick " << right << "\n";
            
            // Add a delay between picking up chopsticks to increase deadlock chance
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            
            chopsticks[left].lock();
            std::cout << "[P" << id << "] Got left chopstick " << left << "\n";

            std::cout << "[P" << id << "] Eating...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            chopsticks[left].unlock();
            chopsticks[right].unlock();

        }

        std::cout << "[P" << id << "] Finished eating and put down chopsticks.\n";
    }
}


int main() {
    std::vector<std::thread> philosophers;

    std::cout << "Starting Dining Philosophers Simulation (Safe Version)...\n";

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.push_back(std::thread(philosopher_resource_ordering, i)); // Use to test deadlock
    }

    for (size_t i = 0; i < philosophers.size(); ++i) {
        // TODO: Wait until all the threads finished.
        philosophers[i].join(); 
    }

    std::cout << "All philosophers finished their meals. No deadlock detected.\n";
    return 0;
}