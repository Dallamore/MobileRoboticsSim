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
	bool leftyRighty;
	double distance;

	enum STATE {
		idle,
		left,
		right
	};

	int state;
	int speed;
	double proximity;
	double heading;
};
