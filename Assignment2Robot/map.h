class map : public ArAction
{
public:
	map();
	ArActionDesired * fire(ArActionDesired d);
	
	virtual ~map() {}
	ArActionDesired desiredState;

	double robotX;
	double robotY;
	double robotTh;
	double objectX;
	double objectY;
	double ths;
	double xs;
	double ys;
	double radius;
	double sonarNum;
	double objectTheta;

	int count;

	double r;

	double leftSonar;
	double rightSonar;

	std::ofstream output;

};
