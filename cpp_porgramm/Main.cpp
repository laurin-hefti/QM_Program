#include <iostream>
#include <cmath>
#include "array.h"
#include "particle.h"
#include "system.h"
#include "editor.h"
#include "graphics.h"
#include "HF.h"
#include "gto.h"


#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

CGTO* cgto = new CGTO();
GTO* gto = new GTO(1, 0, 0, 0);
Vector2D* vec = new Vector2D();
Vector2D* center = new Vector2D();
int yy = 0;

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		/*
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand() % 255));
				*/

		//center->set_vec((int)ScreenWidth() / 2, (int)ScreenHeight() / 2);
		//gto1->components->insert(0,gto1->components->get_element(0) + 0.01);
		for (int x = 0; x < ScreenWidth(); x++) {
			for (int y = 0; y < ScreenHeight(); y++) {
				yy = (ScreenHeight() - y);
				//vec->set_vec(x, yy);
				if (graph(x,yy-100,0,0,400,400,gto,1) || graph2(x, yy - 100, 0, 0, 400, 400, gto, 1)) {
					Draw(x, y, olc::Pixel(255, 255, 255));
				}
				else {
					Draw(x, y, olc::Pixel(0, 0, 0));
				}
			}
		}
		

		return true;
	}
};

int main() {


	cgto->init_cgto(4, 0, 0);
	cgto->add_new_gto(1);
	cgto->add_new_gto(0.5);
	cgto->add_new_gto(0.2);

	if (false) {
		Example demo;
		if (demo.Construct(400, 400, 1, 1))
			demo.Start();
	}
	

	Handelprog* prog = new Handelprog();
	

	//std::cout << cgto->num_integrate(-15, 15, 0.1);
	//std::cout << gto1->num_integrate_one_d(-20, 20, 0.01, 2) << std::endl;
	//std::cout << cgto->num_integrate_one_d(-20, 20, 0.001, 1);
	//std::cout << gto1->get_value_one_d(-1, 1);
	prog->run();

	return 0;
}