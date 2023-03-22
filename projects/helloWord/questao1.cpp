#include <stdio.h>
#include <string.h>

int number_of_observations, count;
float minutes_displayed, seconds_measured;
float seconds_sum, minutes_sum;

int main()
{
    scanf("%d", &number_of_observations);

    if (number_of_observations > 0 && number_of_observations <= 1000)
    {
	    for (count = 0; count < number_of_observations; count++){

		    scanf("%f%f",  &minutes_displayed, &seconds_measured);
		    seconds_sum = seconds_sum+seconds_measured;
		    minutes_sum = (minutes_sum+minutes_displayed);

		}
	    double real_time_remaining;
	    real_time_remaining = ((double)seconds_sum/(minutes_sum*60));
	    if (real_time_remaining > 1)
	    {
	    	printf("%.9f\n", real_time_remaining);
	    } else 
	    {
	    	printf("measurement error\n");
	    }    
    }

 	else
 	{
 		printf("measurement error\n");
 	} 
 	return 0;
 }//main