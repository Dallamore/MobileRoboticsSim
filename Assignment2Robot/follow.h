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

	bool leftOrRight;//L=0, R=1

	double errorHistory;
	double prevError;
	double distance;

	double leftSonar;
	double rightSonar;
};
