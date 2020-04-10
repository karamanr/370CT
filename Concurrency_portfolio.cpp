#include <iostream>
#include <cmath>
#include <cstdlib>
#include <thread>
#include <fstream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <string>
int pos = 0;

std::mutex mtx;
std::condition_variable conditionVar;
bool isReady = false;

void printArray(std::vector<std::string> array, int pos) {

	std::unique_lock<std::mutex> lock(mtx);		//critical section
	while (!isReady) conditionVar.wait(lock);

	std::cout << array.at(pos) << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));

}
void increasePosition() {
	pos++;
}

void start() {
	std::unique_lock<std::mutex> lck(mtx);		//critical section
	isReady = true;
	conditionVar.notify_all();
}
int main() {

	std::string line;
	std::vector<std::string> poemLines = {};
	std::ifstream poem("poem.txt");
	std::thread t1, t2;


	while (getline(poem, line)) {
		poemLines.emplace_back(line);
	}
	start();
	while (pos < poemLines.size()) {
		t2 = std::thread(printArray, poemLines, pos);
		t2.join();
		t1 = std::thread(increasePosition);
		t1.join();
	}

	return 0;
}
