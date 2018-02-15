class map : public ArAction
{
public:
	map();
	ArActionDesired * fire(ArActionDesired d);
	
	virtual ~map() {}
	ArActionDesired desiredState;

	int count;
	double r;
	double objectTheta;
	double robotX;
	double robotY;
	double robotTh;
	double radius;
	double objectX;
	double objectY;
	double xs;
	double ys;
};
