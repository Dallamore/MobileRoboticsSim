class wander : public ArAction
{
public:
	wander();
	ArActionDesired * fire(ArActionDesired d);
	virtual ~wander() {}
	ArActionDesired desiredState;

protected:
	enum state {beginForwards, 
		duringForwards, 
		beginTurn, 
		duringTurn};
	int state;
	double range;
	double heading;
	double distance;
	double travelled;
	double angle;
	int speed;
	double theta;
	double beginForwardsX;
	double beginForwardsY;
};
