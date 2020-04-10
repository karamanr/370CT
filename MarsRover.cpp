// MarsRover.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::condition_variable conditionVar;
std::mutex mtx;
bool isReady = false; 

void alert_message(std::string issue_message, std::string numOfWheel) {
	std::cout << issue_message << numOfWheel << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

void report_back_to_earth(std::string issue) {
	std::cout << "Reporting faults to earth!" << std::endl; 
}

bool success() {
	return 0;
}

void scenario(short num, std::string numOfWheel) {
	if (num > 95) {
		alert_message("Failure on wheel number: ", numOfWheel);
		report_back_to_earth("Failure on wheel number: " + numOfWheel);
	}
	if (num > 80) alert_message("Wheel number " , numOfWheel + " has been dropped.");
	if (num > 70) alert_message("There is something in the way of wheel number: ", numOfWheel);
	else alert_message("No problems yet.", "");
	isReady = true;
	conditionVar.notify_one();
}

void begin() {
	isReady = true;
	conditionVar.notify_one();
}

int main()
{
	short randomInt;
	int scenarioType;

	std::thread wheelOne, wheelTwo, wheelThree, wheelFour, wheelFive, wheelSix;

	do {
		std::unique_lock<std::mutex> lock(mtx); 
		begin();

		while (!isReady) conditionVar.wait (lock);
		randomInt = rand() % 100 + 1;
		wheelOne = std::thread(scenario, randomInt, "1");

		while (!isReady) conditionVar.wait(lock);
		randomInt = rand() % 100 + 1;
		wheelTwo = std::thread(scenario, randomInt, "2");

		while (!isReady) conditionVar.wait(lock);
		randomInt = rand() % 100 + 1;
		wheelThree = std::thread(scenario, randomInt, "3");

		while (!isReady) conditionVar.wait(lock);
		randomInt = rand() % 100 + 1;
		wheelFour = std::thread(scenario, randomInt, "4");

		while (!isReady) conditionVar.wait(lock);
		randomInt = rand() % 100 + 1;
		wheelFive = std::thread(scenario, randomInt, "5");

		while (!isReady) conditionVar.wait(lock);
		randomInt = rand() % 100 + 1;
		wheelSix = std::thread(scenario, randomInt, "6");

		wheelOne.join();
		wheelTwo.join();
		wheelThree.join();
		wheelFour.join();
		wheelFive.join();
		wheelSix.join();
		
		std::this_thread::sleep_for(std::chrono::seconds(2));

	} while (true);
	return 0;
}
