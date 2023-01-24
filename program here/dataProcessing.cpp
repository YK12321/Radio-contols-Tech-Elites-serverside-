#include <iostream>
#include <string>

using namespace std;
double stoi(string data);

// Raw Data Variables
double temp;
double pres;
double humidity;
double uv;

// Temperature - Celsius
double temp_ideal = 28.0;
double temp_dangerously_high = 57.0;
double temp_dangerously_low = -70;

// Pressure - kPa
double pres_ideal = 100.0;
double pres_dangerously_high = 10132.0;
double pres_dangerously_low = 6.0;

// Humidity - percent
double humidity_ideal = 40.0;

// Radiation - UV-index
double uv_ideal = 4.0;
double uv_dangerously_high = 11.0;

// Others
double acc_constant;

int main()
{
    // Graphing WIP
    // https://www.youtube.com/watch?v=sGximvTFJpc

    return 0;
}

string temp_Result(double temp)
{
    if (temp <= temp_dangerously_low)
    {
        return "The temperature in this environment is dangerously low and is not habitable for humans.";
    }
    if (temp > temp_dangerously_low && temp < temp_ideal - 30)
    {
        return "The temperature in this environment is low but is habitable for humans with technological adaptation such as temperature controlling suits.";
    }
    if (temp >= temp_ideal - 30 && temp <= temp + 20)
    {
        return "The temperature in this environment is ideal for human hability.";
    }
    if (temp < temp_dangerously_high && temp > temp_ideal + 20)
    {
        return "The temperature in this environment is low but is habitable for humans with technological adaptation such as temperature controlling suits.";
    }
    if (temp >= temp_dangerously_high)
    {
        return "The temperature in this environment is dangerously high and is not habitable for humans.";
    }
}

string pres_Result(double pres)
{
}

string humidity_Result(double humidity)
{
}

string uv_Result(double uv)
{
}