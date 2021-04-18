#pragma once
#include<string>
#include<vector>
#include <iostream>
#include<sstream>
#include <fstream>
using namespace std;

class Movie
{
public:
	string title; 
	int year;
	int rating;
	string genre;
	int duration;
	string country;

	Movie(string _title, int _year, int _rating, string _genre, int _duration, string _country);

};

//construct the movie class functions
Movie::Movie(string _title, int _year, int _rating, string _genre, int _duration, string _country) {
	title = _title;
	year = _year;
	rating = _rating;
	genre = _genre;
	duration = _duration;
	country = _country;
}
