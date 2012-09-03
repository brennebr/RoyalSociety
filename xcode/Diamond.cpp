/*
 * @file Diamond.cpp
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

#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "Diamond.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Diamond::Diamond(){
	//This is a circular list, so a list of length 1 has
	// next and prev pointing to itself
	next_ = prev_ = this;
	children_ = NULL;
	
	x_ = y_ = z_ = radius_ = 0.0f;
}

void insertAfter(Diamond* new_item, Diamond* insert_here){
	new_item->next_ = insert_here->next_;
	new_item->prev_ = insert_here;
	insert_here->next_->prev_ = new_item;
	insert_here->next_ = new_item;
}

bool Diamond::isInside(float x, float y){
	Vec2i trans = x*Vec2f(0.7071f,-0.7071f) + y*Vec2f(0.7071f,0.7071f);
	return (trans.x >= x_-radius_ && trans.x <= x_+radius_ &&
			trans.y >= y_-radius_ && trans.y <= y_+radius_);
}

void Diamond::update(float parent_x, float parent_y, float parent_r){
	Diamond* cur = children_;
	if(cur != NULL){
		do {
			cur->update(x_,y_,radius_);
			cur = cur->next_;
		} while (cur->next_ != children_);
	}
}

void Diamond::addRandomChild(){
	Diamond* new_item = new Diamond();
	new_item->radius_ = 0.45*radius_;
	//TODO change center
	new_item->x_ = x_;
	new_item->y_ = y_;
	
	if(children_ != NULL){
		insertAfter(new_item, children_);
	} else {
		children_ = new_item;
	}
}

void Diamond::draw(Vec2i mp){
	//First, draw myself
	
	bool is_inside = isInside(mp.x, mp.y);

	if(is_inside){
		gl::color(Color8u(255,92,92));
	} else {
		gl::color(Color8u(255,0,0));
	}
	gl::drawSolidRect(Rectf(x_-radius_,y_-radius_,x_+radius_,y_+radius_));
	gl::color(Color8u(255,255,0));
	gl::drawSolidRect(Rectf(x_-0.95*radius_,y_-0.95*radius_,x_+0.95*radius_,y_+0.95*radius_));
	gl::color(Color8u(255,0,0));
	gl::drawSolidRect(Rectf(x_-0.9*radius_,y_-0.9*radius_,x_+0.9*radius_,y_+0.9*radius_));
	
	//Next, draw my children
	Diamond* cur = children_;
	if(cur != NULL){
		do {
			cur->draw(mp);
			cur = cur->next_;
		} while (cur->next_ != children_);
	}
	
}