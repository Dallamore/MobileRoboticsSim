class follow : public ArAction
{
public:
	follow();
	ArActionDesired * fire(ArActionDesired d);
	virtual ~follow() {}
	ArActionDesired desiredState;

protected:
	int speed;
	double deltaHeading;
	enum STATE {
		IDLE,
		FOLLOW
	};
	int state;

	double setPoint;
	double error;
	double output;
	double pGain;
	double proportional;
	double iGain;
	double integral;
	double dGain;
	double derivative;
	double radius;
	double last_angle;
	double last_out;
	double errorHistory;
	double prevError;
	bool first;
};
