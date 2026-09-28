/*****************************************************************************************
*Date: 2026-09-28
*File: Bacteria.cpp
*Description: Bacteria def file
******************************************************************************************/

#include "Bacteria.h"

#include <stdexcept>

Bacteria::Bacteria() : alive(false) {
}

Bacteria::Bacteria(bool aliveState) : alive(aliveState) {
}

bool Bacteria::isAlive() const {
	return alive;
}

void Bacteria::setAlive(bool aliveState) {
	alive = aliveState;
}

void Bacteria::update(int livingNeighbors) {
	if (livingNeighbors < 0 || livingNeighbors > 8) {
		throw std::invalid_argument("A cell can have between zero and eight living neighbors");
	}

	if (alive) {
		alive = livingNeighbors == 2 || livingNeighbors == 3;
	} else {
		alive = livingNeighbors == 3;
	}
}