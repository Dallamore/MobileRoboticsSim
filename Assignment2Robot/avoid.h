class avoid : public ArAction
{
public:
	avoid();
	ArActionDesired * fire(ArActionDesired d);
	virtual ~avoid() {}
	ArActionDesired desiredState;

protected:
	double leftSonar;
	double rightSonar;
	double distance;

	enum STATE {
		idle,
		turn
	};
	int speed;
	int state;
	double proximity;
	double heading;
	double theta;
};
