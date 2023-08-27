#include<iostream>
#include<config.h>
#include<memory>
#include<cmath>
#include<string.h>
float mysqrt(float a){
	return  std::sqrt(a);
}
int main(int argc, char** argv){
	if(argc ==2){
		float val= std::stof(argv[1]);
		std::cout << mysqrt(val)<<std::endl;
	}	
	return 0;
}
