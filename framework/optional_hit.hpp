#ifndef BUW_OPTIONAL_HIT_HPP
#define BUW_OPTIONAL_HIT_HPP 


struct Optional_hit{
	
	Optional_hit() : hit{0}, Strahlparam{0.0f}{} 

	bool hit;
	Shape* shape;
	float Strahlparam; //Oberflächenpunkt


};

#endif