/*
 * prec.cpp
 * calculate a circle perimeter with step values
 * 
 * prec requires two integer arguments for angle and scale
 * run ./prec 45 100 (demo txt file)
 * run ./prec 360 100 (more points, slower)
 */
 
 #include <iostream>
 #include <fstream>
 #include <math.h>
 
 void preCalc(int points, int scale)
 {
	const float PI = 3.1415926;
	 
	std::cout << "\nUsing " << points << " points " << scale << " scale\n";
	const std::string sout {"preceded.txt"};
	std::ofstream ostr {sout, std::ios_base::trunc};
	if(!ostr)
	{
		std::cout << "Error: no out file successful.\n";
		return;
	}
	
	for(int i = 1; i < points; ++i)
	{
		float angle = 360.0/points;
		float x = sin(angle*i*PI/180) * scale;
		float y = cos(angle*i*PI/180) * scale;
		
		int ix = (int)x;
		int iy = (int)y;
		
		ostr << "floatxy " << ix << " " << iy << "\n";
	}
 }
 
 int main(int argc, char* argv[])
 {
	if(argc<3)
	{
		std::cout << "Program needs two parameters. Quit.\n";
		return 1;
	}
	
	std::cout << "Entered " << argv[1] << " points for circle and "
		<< argv[2] << " for scale\n " << std::endl;
	
	
	std::string s1 = argv[1];
	std::string s2 = argv[2];
	
	int param1 = std::stoi(s1);
	int param2 = std::stoi(s2);
	 
	preCalc(param1, param2);
	 
	return 0;
 }
