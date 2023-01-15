#ifndef RADIUS_H_
#define RADIUS_H_

typedef struct Radius {
	int offset;
	int outsideCirc;
	int aspectCirc;
	int secondCirc;
	int degreeTick;
	int signTick;
	int decanTick;
	int midCirc;
	int mainCirc;
	int margin;
	int points;
	int inCirc;
	int getOffset() { return offset; }
	int getOutsideCirc() { return outsideCirc; }
	int getAspectCirc() { return aspectCirc; }
	int getSecondCirc() { return secondCirc; }
	int getDegreeTick() { return degreeTick; }
	int getSignTick() { return signTick; }
	int getDecanTick() { return decanTick; }
	int getMidCirc() { return midCirc; }
	int getMainCirc() { return mainCirc; }
	int getMargin() { return margin; }
	int getPoints() { return points; }
	int getInCirc() { return inCirc; }
	int isInOusideCirc(int r) { return r < outsideCirc; }
	int isInAspectCirc(int r) { return r < aspectCirc; }
	int isInSecondCirc(int r) { return r < secondCirc; }
	int isInMainCirc(int r) { return r < mainCirc; }

} Radius;


#endif /* RADIUS_H_ */