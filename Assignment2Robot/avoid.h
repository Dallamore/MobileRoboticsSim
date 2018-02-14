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
		left,
		right
	};
	int speed;
	int state;
	double proximity;
	double heading;
	double theta;
	double objectTheta;
	bool leftOrRight;
};
