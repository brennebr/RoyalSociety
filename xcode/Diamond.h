/*
 * @file Diamond.h
 * A diamond that can contain other diamonds. This is really a
 * linked data structure as well.
 *
 * @author Bo Brinkman
 * @date 2012-08-31
 *
 * @note This file is (c) 2012. It is licensed under the 
 * CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
 * which means you are free to use, share, and remix it as long as you
 * give attribution. Commercial uses are allowed.
 */ 

class Diamond{
public:
	Diamond();
	
	//Pointers to my siblings
	Diamond* next_;
	Diamond* prev_;
	
	//Pointer to the sentinel for my list of children.
	Diamond* children_;
	
	float x_;
	float y_;
	float z_; //The depth of the diamond. Keep the list sorted by z_. z_ must be <= 0.0f
	float radius_;
	
	//Return true of the (x,y) provided is inside the diamond
	bool isInside(float x, float y);
	void draw(ci::Vec2i mouse_pos);
	void update(float parent_x, float parent_y, float parent_r);
	
	void addRandomChild();
};

void insertAfter(Diamond* new_item, Diamond* insert_here);