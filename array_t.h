#include <crtdbg.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef double dbl;

typedef struct array_t_tag
{
	dbl* data;			//pointer (reference) to dynamica array
	size_t size;		//track the number of data elements
	size_t capacity;	//track the memory allocation
}array_t;


array_t array();
bool add_to_array(array_t* arr, dbl value);

void swap(dbl* a, dbl* b);
int partition(array_t main_arr[], array_t * parallel_arr, int low, int high);
void quickSort(array_t arr[], array_t * parallel_arr, int low, int high);
int countDigits(double num);
int countIntDigits(int num);
double calcArrayMedian(array_t* arr);
double calcArrayTotal(array_t* arr);
double calcArrayMean(array_t* arr);
bool checkAllEqual(array_t* arr);
dbl calcArrayMode(array_t* arr, int* freq);
void reportMode(array_t* x_arr, array_t* y_arr, dbl* x_mode, dbl* y_mode);
double calcArrayVariance(array_t* arr, double mean);
double calcArrayStdDev(array_t* arr);
double calculate_absolute_deviations(array_t* arr, double x);
void report_mode_absolute_deviations(array_t* x_arr, array_t* y_arr);
void calc_ab(array_t* x_arr, array_t* y_arr, dbl* a, dbl* b);
double calc_x(array_t* arr);
double calc_y(double a, double b, double x);
void findOutliers(array_t* y_arr, array_t* x_arr);
void array_free(array_t* arr);