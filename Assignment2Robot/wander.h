class wander : public ArAction
{
public:
	wander();
	ArActionDesired * fire(ArActionDesired d);
	virtual ~wander() {}
	ArActionDesired desiredState;

protected:
	enum state {forwards, turn};
	int state;

	double heading;
	double distance;
	double travelled;
	double oldX;
	double oldY;
	double angle;
	double oldTheta;
	int speed;

	double currentTheta;
	double aim;

};
