#include "includes.h"

//���¿հ׻�����ӹ��ú���


float map(float input,float input_min,float input_max,float output_min,float output_max)
{
     float out_put;
     out_put=(input-input_min)/(input_max-input_min)*(output_max-output_min)+output_min;
     return out_put;
}

