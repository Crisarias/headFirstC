#include <stdio.h>
#include "taxCalculation.h"

float total = 0.0;
short count = 0.0;
short tax_percent = 6;

int main(int argc, char const *argv[])
{
    float val;
    printf("Price of item:");
    while(scanf("%f", &val) == 1) {                        
        printf("Total so far: %.2f\n", add_with_tax(val));
        printf("Price of item: ");
    }
    //Format float to two decimal places
    printf("\nFinal total: %.2f\n", total);
    //hi used to format shorts
    printf("Number of items: %hi\n",count);
    return 0;
}


//This can be put later because we declared in the taxCalulation.h header file.
float add_with_tax(float f)
{
    float tax_rate = 1 + tax_percent / 100.0;
    total = total + (f * tax_rate);
    count = count + 1;
    return total;
}


