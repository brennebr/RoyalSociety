#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Diamond.h";

using namespace ci;
using namespace ci::app;
using namespace std;

class RoyalSocietyApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	
private:
	Diamond* diamond_list_;
	static const int kAppWidth=1280;
	static const int kAppHeight=720;
	static const Vec2f kUnitX;
	static const Vec2f kUnitY;
	
	int frame_number_;
};

const Vec2f RoyalSocietyApp::kUnitX = Vec2f(0.7071f,-0.7071f);
const Vec2f RoyalSocietyApp::kUnitY = Vec2f(0.7071f,0.7071f);

void RoyalSocietyApp::prepareSettings(Settings* settings){
	settings->setWindowSize(kAppWidth,kAppHeight);
	settings->setResizable(false);
}


void RoyalSocietyApp::setup()
{
	diamond_list_ = new Diamond();
	Vec2f trans = (kAppWidth/2.0f)*kUnitX + (kAppHeight/2.0f)*kUnitY;
	diamond_list_->x_	= trans.x;
	diamond_list_->y_	= trans.y;	
	diamond_list_->radius_	= kAppHeight/2.0f;
	frame_number_ = 0;
}

void RoyalSocietyApp::mouseDown( MouseEvent event )
{
}

void RoyalSocietyApp::update()
{
	Diamond* cur = diamond_list_;
	Vec2f center = kUnitX*kAppWidth/2.0 + kUnitY*kAppHeight/2.0;
	
	if(cur != NULL){
		do {
			cur->update(center.x, center.y, kAppWidth/2.0);
			cur = cur->next_;
		} while (cur != diamond_list_);
	}
	
	frame_number_++;
}

void RoyalSocietyApp::draw()
{
	if(frame_number_ == 1){
		gl::rotate(45);
	}
	
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	
	Diamond* cur = diamond_list_;
	if(cur != NULL){
		do {
			cur->draw(getMousePos());
			cur = cur->next_;
		} while (cur != diamond_list_);
	}
	
	
}

CINDER_APP_BASIC( RoyalSocietyApp, RendererGl )
