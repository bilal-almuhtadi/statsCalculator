#define _CRT_SECURE_NO_WARNINGS
#include "array_t.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string.h>
#include<math.h>


//creates an empty array_t object with initial values
//behaves like a constructor

/*
\fn:		array()
\brief:		descriptive comment about function
\param:		nothing.
\return:	describe return value
*/
array_t array()
{
	array_t array = { NULL, 0, 0 };
	return array;
}


/*
\fn:		add_to_array()
\brief:		adds an element to the end of the array
\param:		pointer to the array , and the value we want to add.
\return:	boolean to be able to test is push_back is successful
*/
bool add_to_array(array_t* arr, dbl value)
{
	//1.expand capacity if necessary
	if (arr->size == arr->capacity)
	{
		//create a temp capacity with double the capacity
		size_t newCapacity = (*arr).capacity * 2;
		//in case of empty state on first push_back, set capacity to at least one 
		if (newCapacity == 0)
			++newCapacity;

		//allocate new memory
		dbl* newBlock = (dbl*)realloc(arr->data, newCapacity * sizeof(dbl));
		//check that allocation works
		if (newBlock == NULL)
			return false;

		//update the new values to this object's members
		arr->data = newBlock;
		arr->capacity = newCapacity;
	}

	//2. assign new value to the array, and increment size
	arr->data[arr->size] = value;
	++arr->size;

	return true;
}

/*
\fn:		array_free()
\brief:		free the array
\param:		pointer to the array
\return:	nothing
*/
void array_free(array_t* arr)
{
	free(arr->data);		//releases allocation		
	*arr = array();			//resets the object to an empty state		
}

/*
\fn:		swap()
\brief:		swap values of 2 passed elements 
\param:		two doubles that we want to swap
\return:	VOID
*/
void swap(dbl* a, dbl* b)
{
	dbl t = *a;
	*a = *b;
	*b = t;
}

/*
\fn:		partition()
\brief:		will set the value of the pivot to the last element in the array and then 
			find its  right place in the array,
			NOTE: This function will sort 2 parallel arrays
\param:		the array you want to sort , the parallel array, low index value, the highest index value
\return:	int that represent the pivot index
*/
int partition(array_t main_arr[],array_t * parallel_arr , int low, int high)
{
	dbl pivot = main_arr->data[high];
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		if (main_arr->data[j] <= pivot)
		{
			i++;
			swap(&main_arr->data[i], &main_arr->data[j]);
			swap(&parallel_arr->data[i], &parallel_arr->data[j]);
		}
	}
	swap(&main_arr->data[i + 1], &main_arr->data[high]);
	swap(&parallel_arr->data[i + 1], &parallel_arr->data[high]);
	return (i + 1);
}

/*
\fn:		quickSort()
\brief:		this function will sort 2 parallel arrays using quil sort algorithim
\param:		the primary array we want to sort it , the parallel array,  low index value, the highest index value
\return:	will return nothing but out=r arrays will be sorted
*/
void quickSort(array_t arr[], array_t * parallel_arr, int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, parallel_arr,low, high);
		quickSort(arr, parallel_arr,low, pi - 1);
		quickSort(arr, parallel_arr,pi + 1, high);
	}
}

/*
\fn:		countDigits()
\brief:		this function will count the number of digits in the passed number
\param:		a number of type double that u want to count its digit
\return:	int that represent the number of digits for the passed num 
*/
int countDigits(double num)
{
	num = fabs(num);
	if (num < 1 )
		return 5;
	int count =0;
	int num1 = floor(num);
	while (num1 != 0)
	{
		count++;
		num1 /= 10;
	}
	return (count + 4);
}

/*
\fn:		countIntDigit()
\brief:		this function will count the number of digits in the passed number
\param:		int number that u want to counts its digit
\return:	int that represent the number of the passed number digits
*/
int countIntDigits(int num)
{
	int count = 0;
	int num1 = num;
	while (num1 != 0)
	{
		count++;
		num1 /= 10;
	}
	return count;
}

/*
\fn:		calcArrayMedian()
\brief:		calculate the median for an array
\param:		the array u want to calc its median
\return:	a double that represent the median
*/
double calcArrayMedian(array_t* arr)
{
	int middleIndex;
	int rightMiddleIndex;
	int leftMiddleIndex;
	if ((arr->size % 2) == 1)
	{
		middleIndex = arr->size / 2;
		return arr->data[middleIndex];
	}
	else
	{
		rightMiddleIndex = arr->size / 2;
		leftMiddleIndex = rightMiddleIndex - 1;
		return(arr->data[leftMiddleIndex] + arr->data[rightMiddleIndex]) / (double)2;
	}
}

/*
\fn:		calcArrayTotal()
\brief:		calculate the sum of array elements
\param:		the array u want to calculate its sum
\return:	double that represent the sum of the array elements
*/
double calcArrayTotal(array_t* arr)
{
	int i;
	double total = 0;

	for (i = 0; i < (int)arr->size; i++)
	{
		total = total + arr->data[i];
	}
	return total;
}

/*
\fn:		calcArrayMean()
\brief:		this function will array the mean for the array 
\param:		a pointer to the array we want to calculate the mean for it
\return:	a double that represents the mean of the array
*/
double calcArrayMean(array_t* arr)
{
	double total = calcArrayTotal(arr);
	return (total/ arr->size );
}

/*
\fn:		checkAllEqual()
\brief:		this function will check if all the array element is equal
\param:		pointer to the array we want to check
\return:	boolean
*/
bool checkAllEqual(array_t * arr)
{
	bool flag = true;
	for (int j = 1; j < (int)arr->size; j++)
	{
		for (int k = j + 1; k < (int)arr->size; k++)
		{
			if (arr->data[j] != arr->data[k])
			{
				flag = false;
			}
		}//inner for	
	}//outer for
	return flag;
}

/*
\fn:		calcArrayMode()
\brief:		this function will find the mode in the passed array
\param:		pointer to the array we want to find its mode and a variable to catch the frequeny of the mode
\return:	double that represents the mode of the array
*/
dbl calcArrayMode(array_t* arr, int* freq)
{
	dbl mode = 0;
	int maxCount = 0, i, j;
	int count = 0;
	array_t freqArr = array();
	array_t valuesArr = array();

	for (i = 0; i < (int)arr->size; i++)
	{
		count = 0;

		for (j = 0; j < (int)arr->size; j++)
		{
			if (arr->data[j] == arr->data[i])
				count++;
		}

		if (count > maxCount)
		{
			maxCount = count;
			mode = arr->data[i];
		}

		add_to_array(&freqArr, count);
		add_to_array(&valuesArr, arr->data[i]);
	}

	quickSort(&freqArr, &valuesArr, 0, freqArr.size);

	if (checkAllEqual(&freqArr))
	{
		*freq = 0;
		return 0;
	}
	else
	{
		*freq = (int)freqArr.data[freqArr.size - 1];
		return mode;
	}
	array_free(&freqArr);
	array_free(&valuesArr);
}

/*
\fn:		reportMode()
\brief:		this method will calculate the modes and their frequencies for the passed arrays and then print them to the connsole 
\param:		the arrays we want find their modes and variables to catch the values
\return:	nothing will print for the console
*/
void reportMode(array_t* x_arr, array_t* y_arr, dbl* x_mode, dbl* y_mode)
{
	int x_freq = 0;
	int y_freq = 0;
	*x_mode = calcArrayMode(x_arr, &x_freq);
	*y_mode = calcArrayMode(y_arr, &y_freq);

	int x_freq_dig = countIntDigits(x_freq);
	int y_freq_dig = countIntDigits(y_freq);

	if (y_freq > 0 && x_freq > 0)
	{
		printf("%-20s %*s%d %*s%d\n", "mode", (30 - x_freq_dig), "freq.= ", x_freq, (30 - y_freq_dig), "freq.= ", y_freq);
		printf("%-20s %30.3lf %30.3lf\n", " ", *x_mode, *y_mode);
	}
	else if (x_freq > 0 && y_freq == 0)
	{
		printf("%-20s %*s%d %30s\n", "mode", (30 - x_freq_dig), "freq.= ", x_freq, "no mode");
		printf("%-20s %30.3lf %30s\n", " ", *x_mode, " ");
	}
	else if (y_freq > 0 && x_freq == 0)
	{
		printf("%-20s %30s %*s%d\n", "mode", "no mode", (30 - y_freq_dig), "freq.= ", y_freq);
		printf("%-20s %30s %30.3lf\n", " ", " ", *y_mode);
	}
	else
	{
		printf("%-20s %30s %30s\n", "mode", "no mode", "no mode");
	}
}

/*
\fn:		calcArrayVariance()
\brief:		find the variance for an array
\param:		pointer to the array we want to caculate its variance, the mean of the array 
\return:	double that represent the variance of the array
*/
 double calcArrayVariance(array_t * arr, double mean)
 {
	double sumDeviations = 0;
	for (int i = 0; i < (int)arr->size; i++)
	{
		sumDeviations += pow((arr->data[i] - mean), 2);
	}

	return sumDeviations / arr->size;
 }

 /*
\fn:		calcArrayStdDev()
\brief:		this function will calculate the array standard deviation 
\param:		poiner to the array we want calculate the sandard deviation for it
\return:	double that represents the standard deviation of the array
*/
 double calcArrayStdDev(array_t* arr)
 {
	 double mean = calcArrayMean(arr);
	 double variance = calcArrayVariance(arr, mean);
	 return sqrt(variance);
 }

 /*
\fn:		calculate_absolute_deviations()
\brief:		calculate the absolute deviation
\param:		pointer to the array , the point wee want to calculate about it
\return:	describe return value
*/
 double calculate_absolute_deviations(array_t* arr, double x)
 {
	 double sum = 0;

	 for (int i = 0; i < (int)arr->size; i++)
	 {
		 double difference = arr->data[i] - x;
		 sum += fabs(difference);
	 }

	 return sum / arr->size;
 }

 /*
\fn:		report_mode_absolute_deviations()
\brief:		will report about the mode results
\param:		pointers to the arrays we want to calculate about the mode for them
\return:	nothing print to the console
*/
 void report_mode_absolute_deviations(array_t* x_arr, array_t* y_arr)
 {
	 int x_freq = 0;
	 int y_freq = 0;
	 double x_mode = calcArrayMode(x_arr, &x_freq);
	 double y_mode = calcArrayMode(y_arr, &y_freq);
	 double x_about_the_mode = calculate_absolute_deviations(x_arr, x_mode);
	 double y_about_the_mode = calculate_absolute_deviations(y_arr, y_mode);

	 


	 if (y_freq > 0 && x_freq > 0)
	 {
		 printf("%-20s %30.3lf %30.3lf\n", "-> about the mode", x_about_the_mode, y_about_the_mode);
	 }
	 else if (x_freq > 0 && y_freq == 0)
	 {
		 printf("%-20s %30.3lf %30s\n", "-> about the mode", x_about_the_mode, "no mode");
	 }
	 else if (y_freq > 0 && x_freq == 0)
	 {
		 printf("%-20s %30s %30.3lf\n", "-> about the mode", "no mode", y_about_the_mode);
	 }
	 else
	 {
		 printf("%-20s %30s %30s\n", "-> about the mode", "no mode", "no mode");
	 }
 }
 
 /*
\fn:		calc_ab()
\brief:		find the regresion line values
\param:		pointers to the arrays we want find the regrression line for , and variables to catch the values for a and b
\return:	nothing void method
*/
 void calc_ab(array_t* x_arr, array_t* y_arr, dbl* a, dbl* b)
 {
	 dbl x_mean = calcArrayMean(x_arr);
	 dbl y_mean = calcArrayMean(y_arr);
	 dbl sum_squares = 0;
	 dbl sum_products = 0;

	 for (int i = 0; i < (int)x_arr->size; i++)
	 {
		 dbl x_diff = (x_arr->data[i] - x_mean);
		 dbl y_diff = (y_arr->data[i] - y_mean);
		 sum_squares += pow(x_diff,2);
		 sum_products += x_diff * y_diff;
	 }

	 *b = sum_products / sum_squares;
	 *a = y_mean - (*b * x_mean);
 }

 /*
\fn:		calc_x()
\brief:		calc value of X
\param:		pointer to the array
\return:	double that represents the value of x
*/
 double calc_x(array_t * arr) 
 {
	 double x = ((arr->data[arr->size - 1] - arr->data[0]) / 2) + arr->data[0];
	 return x;
 }

 /*
\fn:		calc_y()
\brief:		calc value of Y
\param:		the regression line values and value of x
\return:	value of y
*/
 double calc_y(double a, double b, double x) 
 {
	 return (a + (b * x));
 }

 /*
\fn:		findOutliers()
\brief:		this function will find outliers and then report them
\param:		pointers to the arrays
\return:	nothing print to the console
*/
 void findOutliers(array_t* y_arr, array_t* x_arr)
 {
	 
	 int i;
	 double difference, difference1;
	 double mean = calcArrayMean(y_arr);
	 double std_dev = calcArrayStdDev(y_arr);
	 int x2outliersCount = 0;
	 int x3outliersCount = 0;
	 
	 array_t x2_arr = array();
	 array_t x3_arr = array();
	 
	 quickSort(x_arr, y_arr, 0, x_arr->size - 1);

	 for (i = 0; i < (int)y_arr->size; i++)
	 {
		 difference = mean - y_arr->data[i];
		 if (fabs(difference) > (std_dev * 3))
		 {
			 x3outliersCount++;
			 x2outliersCount++;
			 add_to_array(&x2_arr, (double)i);
			 add_to_array(&x3_arr, (double)i);
		 }
		 else if(fabs(difference) > (std_dev * 2))
		 {
			 x2outliersCount++;
			 add_to_array(&x2_arr, (double)i);
		 }
	 }//end for 

	 

	 int x2_outliers_count_numOfDigits = countIntDigits(x2outliersCount);
	 int x3_outliers_count_numOfDigits = countIntDigits(x3outliersCount);

	 if (x2outliersCount > 0 && x3outliersCount > 0)
	 {
		 printf("%-20s %*s%d\n", "Outliers(2x)", (30-x2_outliers_count_numOfDigits),"# outliers = ",x2outliersCount);
		 for (int j = 0; j < (int)x2_arr.size; j++)
		 {
			 printf("%-20s %30.3lf %30.3lf\n", " ", x_arr->data[(int)x2_arr.data[j]], y_arr->data[(int)x2_arr.data[j]]);
		 }
		 printf("%-20s %*s%d\n", "Outliers(3x)", (30 - x3_outliers_count_numOfDigits),"# outliers = " ,x3outliersCount);
		 for (int j = 0; j < (int)x3_arr.size; j++)
		 {
			 printf("%-20s %30.3lf %30.3lf\n", " ", x_arr->data[(int)x3_arr.data[j]], y_arr->data[(int)x3_arr.data[j]]);
		 }
	 }
	 else if (x2outliersCount > 0 && x3outliersCount == 0)
	 {
		 printf("%-20s %*s%d\n", "Outliers(2x)", (30 - x2_outliers_count_numOfDigits), "# outliers = ", x2outliersCount);
		 for (int j = 0; j <(int)x2_arr.size; j++)
		 {
			 printf("%-20s %30.3lf %30.3lf\n", " ", x_arr->data[(int)x2_arr.data[j]], y_arr->data[(int)x2_arr.data[j]]);
		 }
		 printf("%-20s %30s\n", "Outliers(3x)", "no outliers");
		 
	 }
	 else if (x2outliersCount == 0 && x3outliersCount > 0)
	 {
		 printf("%-20s %30s\n", "Outliers(2x)", "no outliers");
		 printf("%-20s %*s%d\n", "Outliers(3x)", (30 - x3_outliers_count_numOfDigits), "# outliers = ", x3outliersCount);
		 for (int j = 0; j < (int)x3_arr.size; j++)
		 {
			 printf("%-20s %30.3lf %30.3lf\n", " ", x_arr->data[(int)x3_arr.data[j]], y_arr->data[(int)x3_arr.data[j]]);
		 }
	 }
	 else
	 {
		 printf("%-20s %30s\n", "Outliers(2x)", "no outliers");
		 printf("%-20s %30s\n", "Outliers(3x)", "no outliers");
	 }
	 array_free(&x2_arr);
	 array_free(&x3_arr);
 }

