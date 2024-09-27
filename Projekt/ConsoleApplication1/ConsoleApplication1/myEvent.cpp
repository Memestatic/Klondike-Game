#include "myEvent.h"

myEvent::~myEvent() {
	
}

myEvent::myEvent() {
	
}

myEvent::myEvent(int type, int movedCardsAmount, Stack* grabbedStackPtr, Card& destinationCard, Stack* destinationStackPtr) {
	this->type = type;
	this->movedCardsAmount = movedCardsAmount;
	this->grabbedStackPtr = grabbedStackPtr;
	this->destinationStackPtr = destinationStackPtr;
	this->changedTexture = false;
	this->destinationCard = destinationCard;
}

myEvent::myEvent(int type, int movedCardsAmount, Stack* grabbedStackPtr, Stack* destinationStackPtr) {
	this->type = type;
	this->movedCardsAmount = movedCardsAmount;
	this->grabbedStackPtr = grabbedStackPtr;
	this->destinationStackPtr = destinationStackPtr;
	this->changedTexture = false;
}

myEvent::myEvent(int type, int movedCardsAmount) {
	this->type = type;
	this->movedCardsAmount = movedCardsAmount;
	this->grabbedStackPtr = nullptr;
	this->destinationStackPtr = nullptr;
	this->changedTexture = false;
}

int myEvent::getType() {
	return this->type;
}

int myEvent::getMovedCardsAmount() {
	return this->movedCardsAmount;
}

Stack* myEvent::getGrabbedStackPtr() {
	return this->grabbedStackPtr;
}

Card myEvent::getDestinationCard() {
	return this->destinationCard;
}

Stack* myEvent::getDestinationStackPtr() {
	return this->destinationStackPtr;
}

bool myEvent::getChangedTexture(){
	return this->changedTexture;
}

void myEvent::setChangedTexture(bool x) {
	this->changedTexture = x;
}
