class edgeFollow : public ArAction
{
public:
	edgeFollow();
	ArActionDesired * fire(ArActionDesired d);
	virtual ~edgeFollow() {}
	ArActionDesired desiredState;

protected:
	int speed;
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

	double lastAngle;
	double lastOut;
	double errorHistory;
	double prevError;
	double angle;
	double distance;

	double leftSonar;
	double rightSonar;

};
