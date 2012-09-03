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
#include "cinder/Rand.h";

using namespace ci;
using namespace ci::app;
using namespace std;

Diamond::Diamond(int depth, Vec2f position, float radius){
	//This is a circular list, so a list of length 1 has
	// next and prev pointing to itself
	next_ = prev_ = this;
	children_ = NULL;
	
	position_ = position_;
	radius_ = radius;
	velocity_ = randVec2f();
	
	if(depth > 0){
		addRandomChild(depth-1);
		addRandomChild(depth-1);
		addRandomChild(depth-1);
	}
}

void insertAfter(Diamond* new_item, Diamond* insert_here){
	new_item->next_ = insert_here->next_;
	new_item->prev_ = insert_here;
	insert_here->next_->prev_ = new_item;
	insert_here->next_ = new_item;
}

bool Diamond::isInside(float x, float y){
	Vec2i trans = x*Vec2f(0.7071f,-0.7071f) + y*Vec2f(0.7071f,0.7071f);
	return (trans.x >= position_.x-radius_ && trans.x <= position_.x+radius_ &&
			trans.y >= position_.y-radius_ && trans.y <= position_.y+radius_);
}

void Diamond::update(Vec2f parent_position, float parent_r){
	position_ = position_ + velocity_;
	//TODO Add a bounds check here, so stuff doesn't drift away
	velocity_ = 0.95*velocity_ +0.05*randVec2f();
	velocity_.safeNormalize();
	
	Diamond* cur = children_;
	if(cur != NULL){
		do {
			cur->update(position_,radius_);
			cur = cur->next_;
		} while (cur->next_ != children_);
	}
}

void Diamond::addRandomChild(int depth){
	Diamond* new_item = new Diamond(depth,position_,0.45*radius_);
	
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
		gl::color(Color8u(255,127,00));
	} else {
		gl::color(Color8u(255,0,0));
	}
	gl::drawSolidRect(Rectf(position_.x-radius_,position_.y-radius_,position_.x+radius_,position_.y+radius_));
	gl::color(Color8u(255,255,0));
	gl::drawSolidRect(Rectf(position_.x-0.95*radius_,position_.y-0.95*radius_,position_.x+0.95*radius_,position_.y+0.95*radius_));
	gl::color(Color8u(255,64,0));
	gl::drawSolidRect(Rectf(position_.x-0.9*radius_,position_.y-0.9*radius_,position_.x+0.9*radius_,position_.y+0.9*radius_));
	
	//Next, draw my children
	Diamond* cur = children_;
	if(cur != NULL){
		do {
			cur->draw(mp);
			cur = cur->next_;
		} while (cur->next_ != children_);
	}
	
}