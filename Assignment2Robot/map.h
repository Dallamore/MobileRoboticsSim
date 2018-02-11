class map : public ArAction
{
public:
	map();
	ArActionDesired * fire(ArActionDesired d);
	
	virtual ~map() {}
	ArActionDesired desiredState;

	int window();

	double robotX;
	double robotY;
	double robotTh;
	double x;
	double y;
	double hypot;
	double ths;
	double xs;
	double ys;
	double thetaS;
	double radius;
	double sonarNum;

	int count;

	double r, angle;

	double leftSonar;
	double rightSonar;

};
