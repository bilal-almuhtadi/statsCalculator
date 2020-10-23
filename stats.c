/*
\file:		filename.c
\author:	Bilal Al-Muhtadi
\date:		28/2/2020
\version:	1.0
\brief:		reads number pairs from file or keyboard then calculates minimum value, maximum value, 
			median value, arithmetic mean, mean absolute deviation – (mean, median, mode),
			variance (of a discrete random variable), standard deviation (of a finite population), 
			mode, least squares regression line and outliers(2x and 3x)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "array_t.h"

int main(int argc, char* argv[])
{
	FILE* stream = stdin;

	if (argc > 2)
	{
		printf("Error, too many args %d \n", argc);
		return EXIT_FAILURE;
	}
	//2. correct args
	else if (argc == 2)
	{
		stream = fopen(argv[1], "r");
		//check for file opening failure
		if (stream == NULL)
		{
			printf("Error %s ", argv[1]);
			return EXIT_FAILURE;
		}
	}

	//declare arrays to catch my readings 
	array_t x_arr = array();
	array_t y_arr = array();

	//declare variables to catch the values in fscanf and then assign their values to the arrays
	dbl x;
	dbl y;
	char ch;

	//ask user to input
	printf("Enter a list of comma-seperated real numbers pairs terminated by EOF or non numeric input.\n");

	//read from stream
	while ((fscanf(stream, "%lf%c%lf", &x, &ch,&y)) == 3)
	{
		
		add_to_array(&x_arr, x);
		add_to_array(&y_arr, y);
	}
	
	//call the method to calculate a, b
	//declare variables that will be passed to my method and catch values of a,b
	dbl a=0;
	dbl b=0;
	calc_ab(&x_arr, &y_arr, &a, &b);

	//count the number of digits for a and b for formating purposes
	int a_digit_num = countDigits(a);
	int b_digit_num = countDigits(b);
	if (a < 0)
		a_digit_num++;
	if (b < 0)
		b_digit_num++;
	
	//Sort the arrays, x_arr will be the primary array and calculate the stats for the x_arr
	quickSort(&x_arr,&y_arr, 0,x_arr.size -1);
	dbl min_x = x_arr.data[0];
	dbl max_x = x_arr.data[x_arr.size-1];
	dbl mean_x = calcArrayMean(&x_arr);
	dbl median_x = calcArrayMedian(&x_arr);
	dbl mode_x = 0;
	dbl variance_x = calcArrayVariance(&x_arr,mean_x);
	dbl std_dev_x = calcArrayStdDev(&x_arr);
	dbl abs_dev_mean_x = calculate_absolute_deviations(&x_arr, mean_x);
	dbl abs_dev_median_x = calculate_absolute_deviations(&x_arr, median_x);

	//call the methods to calculate x,y
	double x_y_intercept = calc_x(&x_arr);
	double y_y_intercept = calc_y(a, b, x_y_intercept);
	
	//count the number of digits for x and y for formating purposes
	int x_digit_num = countDigits(x_y_intercept);
	int y_digit_num = countDigits(y_y_intercept);
	
	//check if there are minus values to add extra space for the minus sign
	if (x_y_intercept < 0)
		x_digit_num++;
	if (y_y_intercept < 0)
		y_digit_num++;


	//Sort the arrays, y_arr will be the primary array and calculate the stats for the y_arr
	quickSort(&y_arr, &x_arr, 0, y_arr.size - 1);
	dbl min_y = y_arr.data[0];
	dbl max_y = y_arr.data[y_arr.size-1];
	dbl mean_y = calcArrayMean(&y_arr);
	dbl median_y = calcArrayMedian(&y_arr);
	dbl mode_y = 0;
	dbl variance_y = calcArrayVariance(&y_arr, mean_y);
	dbl std_dev_y = calcArrayStdDev(&y_arr);
	dbl abs_dev_mean_y = calculate_absolute_deviations(&y_arr, mean_y);
	dbl abs_dev_median_y = calculate_absolute_deviations(&y_arr, median_y);

	//report data
	printf("\n\nResults:\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("%-20s %*d %*d\n", "# elements", 30,x_arr.size, 30,y_arr.size);
	printf("%-20s %*.3lf %*.3lf\n","minimum", 30,min_x, 30,min_y);
	printf("%-20s %*.3lf %*.3lf\n","maximum" , 30,max_x, 30,max_y);
	printf("%-20s %*.3lf %*.3lf\n","mean", 30,mean_x, 30,mean_y);
	printf("%-20s %*.3lf %*.3lf\n","median", 30,median_x, 30,median_y);
	reportMode(&x_arr, &y_arr,&mode_x,&mode_y);
	printf("%-20s %*.3lf %*.3lf\n", "variance", 30,variance_x, 30,variance_y);
	printf("%-20s %*.3lf %*.3lf\n", "std. dev.", 30,std_dev_x, 30,std_dev_y);
	printf("mean absolute deviation:\n");
	printf("%-20s %*.3lf %*.3lf\n", "-> about the mean", 30,abs_dev_mean_x, 30,abs_dev_mean_y);
	printf("%-20s %*.3lf %*.3lf\n", "-> about the median", 30, abs_dev_median_x, 30,abs_dev_median_y);
	report_mode_absolute_deviations(&x_arr, &y_arr);
	printf("%-20s %*s%.3lf %*s%.3lf\n", "regression line", (30 - a_digit_num), "a = ", a, (30 - b_digit_num), "b = ", b);
	printf("%-20s %*s%.3lf %*s%.3lf\n", "Y at mid(x)", (30 - x_digit_num) ,"x = " ,x_y_intercept, (30 - y_digit_num),"y = " ,y_y_intercept);
	findOutliers(&y_arr, &x_arr);
	array_free(&x_arr);
	array_free(&y_arr);
	fclose(stream);
}