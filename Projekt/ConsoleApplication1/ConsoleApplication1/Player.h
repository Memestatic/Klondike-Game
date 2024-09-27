/*****************************************************************//**
 * \file   Player.h
 * \brief  Current player data class
 * 
 * \author Karol Ziaja
 * \date   August 2023
 *********************************************************************/

#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;

class Player {
	/** Earned points */
	int points;
	/** Saved record */
	int currentRecord;
	/** Login */
	std::string Login;
	/** Password */
	std::string Password;
	/** Time record */
	std::string timeRecord;
public:
	/**
	 * Adding points method.
	 * 
	 * \param points Points value
	 */
	void addPoints(int points);
	/** Getting points method */
	int getPoints();
	/** Setting a fixed value of points method */
	void setPoints(int points);
	/**
	 * Setting current record method.
	 * 
	 * \param record Record (points) value
	 */
	void setCurrentRecord(int record);
	/** Getting current record value */
	int getCurrentRecord();
	/**
	 * Setting login method.
	 * 
	 * \param login Login
	 */
	void setLogin(std::string login);
	/** Getting login method */
	std::string getLogin();
	/**
	 * Setting password method.
	 * 
	 * \param password Password
	 */
	void setPassword(std::string password);
	/** Getting password method */
	std::string getPassword();
	/**
	 * Setting time record method.
	 * 
	 * \param timeRecord Time record (xx::yy::zz)
	 */
	void setTimeRecord(std::string timeRecord);
	/** Getting time record method */
	std::string getTimeRecord();
	/**
	 * Operator made in order to add player points in a different way.
	 * 
	 * \param points value
	 */
	Player operator+(int points);
	/**
	 * Operator made in order to subtract player points in a different way.
	 *
	 * \param points value
	 */
	Player operator-(int points);
	/**
	 * Player constructor.
	 * 
	 * \param login Login
	 * \param password Password
	 * \param record Record
	 * \param timeRecord Time record
	 */
	Player(std::string login, std::string password, int record, std::string timeRecord);
	/**
	 * Method that checks if player set new time record.
	 * 
	 * \param time Previous saved time record text
	 * \param hours Current time hours
	 * \param minutes Current time minutes
	 * \param seconds Current time seconds
	 */
	void checkTimeRecord(Text& time, int hours, int minutes, int seconds);
};
