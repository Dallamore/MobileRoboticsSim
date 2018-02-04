class edgeFollow : public ArAction
{
public:
	edgeFollow();
	ArActionDesired * fire(ArActionDesired d);
	virtual ~edgeFollow() {}
	ArActionDesired desiredState;

protected:
	int speed;
	double deltaHeading;
	enum state {
		idle,
		following
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
