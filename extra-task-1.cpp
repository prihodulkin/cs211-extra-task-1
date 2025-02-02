#include <iostream>;
#include <assert.h>;

using namespace std;



double seconds_difference(double time_1, double time_2)
{
	return time_2 - time_1;    
}

double hours_difference(double time_1, double time_2)
{
	return (time_2 - time_1) / 3600;
   
}

double to_float_hours(int hours, int minutes, int seconds)
{
	assert(minutes >= 0 && minutes < 60);
	assert(seconds >= 0 && seconds < 60);
	assert(hours >= 0);
	return hours*1.0 + (minutes * 60 + seconds) / 3600.0;
   
}

double to_24_hour_clock(double hours)
{
	int h = hours;
	return hours -h+h % 12;
   
}



double get_hours(double seconds)
{
	return (int)(seconds / 3600);
}

double get_minutes(double seconds)
{
	return (int) (seconds-get_hours(seconds)*3600)/60;
}

double get_seconds(double seconds)
{
	return (int)seconds % 60+ seconds-(int)seconds;
}
double time_to_utc(int utc_offset, double time)
{
	assert(time >= 0 && time <= 24);
	double result = time - utc_offset;
	if (result <= 0) result += 24;
	if (result >= 24) result -= 24;
	return result;
    
}

double time_from_utc(int utc_offset, double time)
{
	assert(time >= 0 && time <= 24);
	double result = time + utc_offset;
	if (result <= 0) result += 24;
	if (result >= 24) result -= 24;
	return result;
   
}

int main()
{
	double eps = 0.00000001;
	assert(fabs(seconds_difference(1800.0, 3600.0) - 1800) < eps);
	assert(fabs(seconds_difference( 3600.0,1800.0) + 1800) < eps);
	assert(fabs(seconds_difference(1800, 2160) - 360) < eps);
	assert(fabs(seconds_difference(1800, 1800) - 0) < eps);

	assert(fabs(hours_difference(1800.0, 3600.0) - 0.5) < eps);
	assert(fabs(hours_difference( 3600.0,1800) +0.5) < eps);
	assert(fabs(hours_difference(1800.0, 2160.0) - 0.1) < eps);
	assert(fabs(hours_difference(1800.0, 1800.0) - 0.0) < eps);
	
	assert(fabs(to_float_hours(0, 15, 0) - 0.25) < eps);
	assert(fabs(to_float_hours(2,45,9) - 2.7525) < eps);
	assert(fabs(to_float_hours(1,0,36) - 1.01) < eps);
	
	assert(fabs(to_24_hour_clock(24) - 0) < eps);
	assert(fabs(to_24_hour_clock(48) - 0) < eps);
	assert(fabs(to_24_hour_clock(25) - 1) < eps);
	assert(fabs(to_24_hour_clock(4) - 4) < eps);
	assert(fabs(to_24_hour_clock(28.5) - 4.5) < eps);

	assert(fabs(get_hours(3800) - 1) < eps);
	assert(fabs(get_minutes(3800) - 3) < eps);
	assert(fabs(get_seconds(3800) - 20) < eps);

	assert(fabs(time_to_utc(+0, 12.0) - 12) < eps);
	assert(fabs(time_to_utc(+1, 12.0) - 11) < eps);
	assert(fabs(time_to_utc(-1, 12.0) - 13) < eps);
	assert(fabs(time_to_utc(-11, 18) - 5) < eps);
	assert(fabs(time_to_utc(-1, 0.0) -1) < eps);
	assert(fabs(time_to_utc(-1, 23.0) - 0) < eps);

	assert(fabs(time_from_utc(+0, 12.0) - 12) < eps);
	assert(fabs(time_from_utc(+1, 12.0) - 13) < eps);
	assert(fabs(time_from_utc(-1, 12.0) - 11) < eps);
	assert(fabs(time_from_utc(+6, 6.0) - 12) < eps);
	assert(fabs(time_from_utc(-7, 6.0) - 23) < eps);
	assert(fabs(time_from_utc(-1, 0.0) - 23) < eps);
	assert(fabs(time_from_utc(-1, 23) - 22) < eps);
	assert(fabs(time_from_utc(+1, 23) - 0) < eps);
	


	system("pause");

}
