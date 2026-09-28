/*****************************************************************************************
*Date: 2026-09-28
*File: Bacteria
*Description: Bacteria header file
******************************************************************************************/

#ifndef BACTERIA_H
#define BACTERIA_H

class Bacteria {
public:
	Bacteria();
	explicit Bacteria(bool alive);

	bool isAlive() const;
	void setAlive(bool alive);
	void update(int livingNeighbors);

private:
	bool alive;
};

#endif // BACTERIA_H