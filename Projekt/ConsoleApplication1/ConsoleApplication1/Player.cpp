#include "Player.h"
#include <string>
#include <vector>

int Player::getPoints() {
	return this->points;
}

void Player::addPoints(int points) {
	this->points += points;
}

void Player::setPoints(int points) {
	this->points = points;
}

int Player::getCurrentRecord() {
	return this->currentRecord;
}

void Player::setCurrentRecord(int record) {
	this->currentRecord = record;
}

std::string Player::getLogin(){
	return this->Login;
}

void Player::setLogin(std::string login){
	this->Login = login;
}

std::string Player::getPassword(){
	return this->Password;
}

void Player::setPassword(std::string password) {
	this->Password = password;
}

void Player::setTimeRecord(std::string timeRecord) {
	this->timeRecord = timeRecord;
}

std::string Player::getTimeRecord() {
	return this->timeRecord;
}

Player::Player(std::string login, std::string password, int record, std::string timeRecord) {
	this->Login = login;
	this->Password = password;
	this->points = 0;
	this->currentRecord = record;
	this->timeRecord = timeRecord;
}

Player Player::operator+(int points) {
	this->points = this->points + points;
	return *this;
}

Player Player::operator-(int points) {
	this->points = this->points - points;
	return *this;
}

void Player::checkTimeRecord(Text& time, int hours, int minutes, int seconds){
	std::vector<int> timeArray;
	std::stringstream ss;
	if (hours < 10)
		ss << "0" << hours;
	else
		ss << hours;
	if (minutes < 10)
		ss << ":" << "0" << minutes;
	else
		ss << ":" << minutes;
	if (seconds < 10)
		ss << ":" << "0" << seconds;
	else
		ss << ":" << seconds;
	std::string newTime = ss.str();
	std::string oldTime = time.getString();
	if (oldTime != "0") {
		timeArray.push_back(std::stoi(oldTime.substr(0, 2)));
		timeArray.push_back(std::stoi(oldTime.substr(3, 2)));
		timeArray.push_back(std::stoi(oldTime.substr(6, 2)));
	}
	if (oldTime != "0") {
		if (hours < timeArray[0]) {
			//std::cout << "Zmiana przez godziny" << std::endl;
			this->setTimeRecord(newTime);
		}
		else if (hours == timeArray[0]) {
			if (minutes < timeArray[1]) {
				//std::cout << "Zmiana przez minuty" << std::endl;
				this->setTimeRecord(newTime);
			}
			else if (minutes == timeArray[1]) {
				if (seconds < timeArray[2]) {
					//std::cout << "Zmiana przez sekundy" << std::endl;
					this->setTimeRecord(newTime);
				}
			}
		}
	}
	else {
		this->setTimeRecord(newTime);
	}
}
