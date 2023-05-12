#pragma once
#include "AnimationWindow.h"
#include "widgets/Button.h" 

// De forskjellige tilstandene en Tile kan vaere i
enum class Cell { closed, open, flagged }; 

class Tile : public TDT4102::Button
{
	Cell state = Cell::closed;
	bool isMine = false;
	void set_label(std::string s) { this->setLabel(s);}
	void set_label_color(TDT4102::Color c) {this->setLabelColor(c);}
public:
	Tile(TDT4102::Point pos, int size);

	// Vis hvor mange miner det er i naborutene
	void setAdjMines(int n);

	void open();
	void reset();
	void flag();

	bool getIsMine() const { return isMine; };
	void setIsMine(bool isMine) { this->isMine = isMine; };
	Cell getState() const { return state; };
};
