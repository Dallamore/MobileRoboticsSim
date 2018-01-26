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
	double iGain;
	double dGain;

	double pOut;
	double iOut;
	double dOut;

	double radius;
	double last_angle;
	double last_out;
	double errorHistory;
	double prevError;
	
	double angle;
	bool first;

	double leftSonar;
	double rightSonar;

};
