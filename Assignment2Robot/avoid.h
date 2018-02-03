class avoid : public ArAction
{
public:
	avoid();
	ArActionDesired * fire(ArActionDesired d);
	virtual ~avoid() {}
	ArActionDesired desiredState;

protected:
	enum STATE {
		idle,
		left,
		right
	};
	int state;
	int speed;

	double proximity;
	double limit;
	double angle;
	double heading;
};
