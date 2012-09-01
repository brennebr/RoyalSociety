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

#include "Diamond.h"
#include "cinder/gl/gl.h"

using namespace ci;

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
	float dist = abs(x-x_) + abs(y-y_);
	return (dist <= radius_);
}

void Diamond::update(){
	Diamond* cur = children_;
	if(cur != NULL){
		do {
			cur->update();
			cur = cur->next_;
		} while (cur->next_ != children_);
	}
}

void Diamond::draw(){
	//First, draw myself
	//TODO: The actual drawing
	gl::color(Color8u(255,0,0));
	gl::drawSolidRect(Rectf(x_-radius_,y_-radius_,x_+radius_,y_+radius_));
	gl::color(Color8u(255,255,0));
	gl::drawSolidRect(Rectf(x_-0.9*radius_,y_-0.9*radius_,x_+0.9*radius_,y_+0.9*radius_));
	gl::color(Color8u(255,0,0));
	gl::drawSolidRect(Rectf(x_-0.8*radius_,y_-0.8*radius_,x_+0.8*radius_,y_+0.8*radius_));
	
	//Next, draw my children
	Diamond* cur = children_;
	if(cur != NULL){
		do {
			cur->draw();
			cur = cur->next_;
		} while (cur->next_ != children_);
	}
	
}