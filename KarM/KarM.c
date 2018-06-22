#include "KarM.h"

float prevData=0.0; 
float p=10; 
float q=0.0001;
float kGain=0; 
	float outData;
	float r=0.05; 

uint16_t KaeM(uint16_t input)
{
 

	p=p+q; 
	kGain=p/(p+r); 
	temp=input; 
	temp=prevData+(kGain*(temp-prevData)); 
	p=(1-kGain)*p; 
	prevData=temp; 
	outData=temp; 

	return outData;

}
