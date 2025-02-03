/*
 * Copyright Kevin Barnard 2025 ... blah blah
 * 
 * __Man running in circle__
 */

#include <vector>
#include <fstream>
#include <iostream>
#include "irrlicht.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace gui;
using namespace scene;

struct SContext
{
	IrrlichtDevice *device;
	//IGUITable *table;
	bool play_man = false;
};

enum MyGUI
{
	GUI_QUIT = 101,
	GUI_TABLE,
};

class MyEventReceiver : public IEventReceiver
{
	public:
	MyEventReceiver(SContext &Context) : context(Context) {}
	
	virtual bool OnEvent(const SEvent &event)
	{
		if(event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			
			switch(event.GUIEvent.EventType)
			{
			case EGET_BUTTON_CLICKED:
			{
				switch(id)
				{
				case MyGUI::GUI_QUIT:
				{
					context.play_man = true;	
					return true;
				}
				}
			}
			default:
				return false;
			}
		}
		
		return false;
	}
	
	private:
	SContext &context;
};


//
// functions
//

std::vector<vector3df> getPoints()
{
	std::vector<vector3df> vec(0);
	
	std::string s = "preceded.txt";
	std::ifstream istr {s};
	if(!istr) return vec;
	
	std::vector<vector3df> numbers;
	std::vector<std::string> vecwaste;
	
	int tempx, tempz = 0;
	std::string waste;
	
	while(istr >> waste >> tempx >> tempz)
	{
		vector3df tempf(tempx, 0, tempz);
		std::cout << waste << " (" << tempx << "," << tempz << ")\n";
		numbers.push_back(tempf);
		vecwaste.push_back(waste);
	}
	
	std::cout << "\nIn getPoints " << vecwaste[0] << "\n";
	return numbers;
}

void playMan(ISceneNode *man, std::vector<vector3df> p, u32 & index)
{
	if(index<p.size())
	{
		man->setPosition(p[index]);
		index++;
	}
	else
		index = 0;
}


//
// main
//



int main()
{
	//
	// Irrlicht
	//
	
	IrrlichtDevice *device = createDevice(EDT_SOFTWARE, dimension2d<u32>(600,600),
		16, false, false, false, 0);
	if(!device) return -1;
	
	device->setWindowCaption(L"Hello Line Code");
	IVideoDriver *driver = device->getVideoDriver();
	ISceneManager *smgr = device->getSceneManager();
	IGUIEnvironment *gui_env = device->getGUIEnvironment();

	//
	// mesh
	//

	IAnimatedMesh *man = smgr->getMesh("man3.ms3d");
	ISceneNode *man_node = smgr->addMeshSceneNode(man);
	if(man_node)
	{
		man_node->setMaterialFlag(EMF_LIGHTING, false);
		man_node->setPosition(vector3df(0,0,0));
	}
	
	
	//
	// textures
	//
	
	ITexture *sky = driver->getTexture("crop_skyhill.jpg");
	rect<s32> fullsky(0,0,600,600);
	
	//
	// camera
	//
	
	smgr->addCameraSceneNode(0, vector3df(240,300,-300), vector3df(0,0,0));
		
	//
	// game
	//

	gui_env->addButton(rect<s32>(0,0, 100, 50), 0, MyGUI::GUI_QUIT, L"RUN", L"Run Man");

	SContext context;
	context.device = device;
	MyEventReceiver receiver(context);
	device->setEventReceiver(&receiver);

	// are the numbers stored now if I compile?
	std::vector<vector3df> points = getPoints();
	// man
	u32 index=0;
		
	while(device->run() && driver)
	{
		if(device->isWindowActive())
		{
			driver->beginScene(true, true, SColor(255,0,0,0));
		
			driver->draw2DImage(sky, position2d<s32>(0,0), fullsky); 	
			if(context.play_man)
			{
				playMan(man_node, points, index);
				device->sleep(500);
			}
			
			smgr->drawAll();
			gui_env->drawAll();
			
			driver->endScene();
		}
		else
		{
			device->yield();
		}
	}
	
	device->drop();
	
	return 0;
}
