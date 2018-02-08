class map : public ArAction
{
public:
	map();
	ArActionDesired * fire(ArActionDesired d);
	
	virtual ~map() {}
	ArActionDesired desiredState;

	int window();

	double rX;
	double rY;

	std::list<double> xs;

};
