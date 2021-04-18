#include "Movie.h"
#include<string>
#include<vector>
#include <iostream>
#include<sstream>
#include <fstream>
#include<algorithm>
#include<chrono>
using namespace std;
using namespace std::chrono;

vector<Movie> GetMoviesFromCVS(string filepath) {
	ifstream inFile(filepath);
	string linefromfile;
	vector<Movie> movies;
	//getline(inFile, linefromfile);
	while (getline(inFile, linefromfile)) {
		istringstream stream(linefromfile);

		string Title;
		getline(stream, Title, '\t');
	//	cout << Title << ", ";

		string tempyear;
		int year;
		getline(stream, tempyear, '\t');
	//	cout << tempyear << endl;
		year = stoi(tempyear);

		string temprating;
		int rating;
		getline(stream, temprating, '\t');
		rating = stoi(temprating);

		string Genre;
		getline(stream, Genre, '\t');

		string throwaway;/*
		getline(stream, throwaway, ';');*/

		string tempdur;
		int duration;
		getline(stream, tempdur, '\t');
		duration = stoi(tempdur);

		string country;
		getline(stream, country, '\t');

		Movie newmovie = Movie(Title, year, rating, Genre, duration, country);
		movies.push_back(newmovie);
	}
	return movies;
}

void PrintMovies(vector<Movie> movies) {
	if (movies.size() > 10) {
		for (int i = 0; i < 10; i++) {
			cout << movies[i].title << ", ";
			cout << movies[i].year << ", ";
			cout << movies[i].rating << ", ";
			cout << movies[i].genre << ", ";
			cout << movies[i].duration << ", ";
			cout << movies[i].country << endl;
		}
	}
	else {
		for (int i = 0; i < movies.size(); i++) {
			cout << movies[i].title << ", ";
			cout << movies[i].year << ", ";
			cout << movies[i].rating << ", ";
			cout << movies[i].genre << ", ";
			cout << movies[i].duration << ", ";
			cout << movies[i].country << endl;
		}
	}
}
//Selection Sorts
vector<Movie> selectionSortYear(vector<Movie> movies) { //ascending sort good

	// moves to the next element within the vector
	for (int i = 0; i < movies.size() - 1; i++)
	{
		// find the minimum in the vector
		int min_idx = i;
		for (int j = i + 1; j < movies.size(); j++) {
			if (movies[j].year > movies[min_idx].year) {
				min_idx = j;
			}

			// swap min element with the first found element
			swap(movies[min_idx], movies[j]);

		}
	}
	return movies;
}
// Bubble sorts
vector<Movie> bubbleSortYear(vector<Movie> movies)
{
	for (int i = 0; i < movies.size() - 1; i++) {
		// Last i elements are already in place
		for (int j = 0; j < movies.size() - i - 1; j++) {
			if (movies[j].year > movies[j + 1].year) {
				swap(movies[j], movies[j + 1]);
			}
		}
	}
	return movies;
}

vector<Movie> bubbleSortDuration(vector<Movie> movies)
{
	for (int i = 0; i < movies.size() - 1; i++) {
		for (int j = 0; j < movies.size() - i - 1; j++) {
			if (movies[j].duration > movies[j + 1].duration) {
				swap(movies[j], movies[j + 1]);
			}
		}
	}
	return movies;
}

vector<Movie> bubbleSortRating(vector<Movie> movies)
{
	for (int i = 0; i < movies.size() - 1; i++) {
		for (int j = 0; j < movies.size() - i - 1; j++) {
			if (movies[j].rating > movies[j + 1].rating) {
				swap(movies[j], movies[j + 1]);
			}
		}
	}
	return movies;
}
////////////////////////////////////////////////////////////////////////////////////searches:
vector<Movie> findRangeDuration(int start, int end, vector<Movie> sorted) {
	vector<Movie> r;
	for (int i = 0; i < sorted.size(); i++) {
		if (sorted[i].duration <= end && sorted[i].duration >= start) {
			r.push_back(sorted[i]);
		}
	}
	return r;
}

vector<Movie> findRangeYear(int start, int end, vector<Movie> sorted) {
	vector<Movie> r;
	for (int i = 0; i < sorted.size(); i++) {
		if (sorted[i].year <= end && sorted[i].year >= start) {
			r.push_back(sorted[i]);
		}
	}
	return r;
}

vector<Movie> findRangeRating(int start, int end, vector<Movie> sorted) {
	vector<Movie> r;
	for (int i = 0; i < sorted.size(); i++) {
		if (sorted[i].rating <= end && sorted[i].rating >= start) {
			r.push_back(sorted[i]);
		}
	}
	return r;
}
int BinarySearchyear(vector<Movie> sortedByYear, int left, int right, int x) {
	if (right >= 1) {
		int mid = left + (right - left) / 2;
		if (sortedByYear[mid].year == x) {
			return mid;
		}
		if (sortedByYear[mid].year > x) {
			return BinarySearchyear(sortedByYear, 1, mid - 1, x);
		}
		else {
			return BinarySearchyear(sortedByYear, mid + 1, right, x);
		}

	}
	return -1; //does not exist
}

int exponentialSearchyear(vector<Movie> sortedByYear, int n, int x) {
	if (sortedByYear[0].year == x) {//edge case
		return 0;
	}
	int i = 1;
	while (i < n && sortedByYear[i].year <= x) {//n is sizeof(arr)/sizeof(vector[0])
		i = i * 2;
	}
	return BinarySearchyear(sortedByYear, i / 2, min(i, n - 1), x);
}
//linear searches
vector<Movie> LinearfindTitle(string s, vector<Movie> sorted) {
	vector<Movie> r;
	for (int i = 0; i < sorted.size(); i++) {
		size_t j = sorted[i].title.find(s);
		if (j != string::npos) {
			r.push_back(sorted[i]);
		}
	}
	return r;
}
vector<Movie> LinearfindGenre(string s, vector<Movie> sorted) {
	vector<Movie> r;
	for (int i = 0; i < sorted.size(); i++) {
		size_t j = sorted[i].genre.find(s);
		if (j != string::npos) {
			r.push_back(sorted[i]);
		}
	}
	return r;
}
vector<Movie> LinearfindYear(int year, vector<Movie> sorted) {
	vector<Movie> r;
	for (int i = 0; i < sorted.size(); i++) {
		if (sorted[i].year == year) {
			r.push_back(sorted[i]);
		}
	}
	return r;
}

vector<Movie> findALL(vector<Movie> v, int n, int year) {
	vector<Movie> r;
	r.push_back(v[n]);
	int i = n + 1;
	while (1) { //loop checks past the return index
		if (v[i].year != year)
			break;
		r.push_back(v[i]);
		i++;
	}
	int j = n - 1;
	while (1) {
		if (v[j].year != year)
			break;
		r.push_back(v[j]);
		j--;
	}
	return r;

}

//to compare the run time of selection and bubble sort. Input the movie vector to be sorted
void compareSelectionandBubble(vector<Movie> movies) {
	auto start1 = high_resolution_clock::now();
	vector<Movie> movies1 = selectionSortYear(movies);
	auto stop1 = high_resolution_clock::now();


	auto duration1 = duration_cast<microseconds>(stop1 - start1);
	cout << "Time taken by Selection sort: "
		<< duration1.count() << " microseconds" << endl;

	auto start2 = high_resolution_clock::now();
	vector<Movie> movies2 = bubbleSortYear(movies);
	auto stop2 = high_resolution_clock::now();

	auto duration2 = duration_cast<microseconds>(stop2 - start2);
	cout << "Time taken by Bubble sort: "
		<< duration2.count() << " microseconds" << endl;
}

void comparebinaryandexponentialandlinear(vector<Movie> movies) {
	auto start1 = high_resolution_clock::now();
	//temp returned is the first year with the 1914
	int temp = BinarySearchyear(movies, 0, movies.size()-1, 1914);
	auto stop1 = high_resolution_clock::now();


	auto duration1 = duration_cast<microseconds>(stop1 - start1);
	cout << "Time taken by Binary Search: "
		<< duration1.count() << " microseconds" << endl;

	auto start2 = high_resolution_clock::now();
	int j = exponentialSearchyear(movies, movies.size(), 1914);
	auto stop2 = high_resolution_clock::now();

	auto duration2 = duration_cast<microseconds>(stop2 - start2);
	cout << "Time taken by Exponential search: "
		<< duration2.count() << " microseconds" << endl;

	auto start3 = high_resolution_clock::now();
	vector<Movie> movies3 = LinearfindYear(1914, movies);
	auto stop3 = high_resolution_clock::now();

	auto duration3 = duration_cast<microseconds>(stop3 - start3);
	cout << "Time taken by Linear search: "
		<< duration3.count() << " microseconds" << endl;
}
int main() {
	//Must have the .cvs file that has the movies in it in the same 
	//folder (parallel to) the .cpp file with the main

	string filename;
	cout << "would you like to load a file? Please input the filename:" << endl;
	cin >> filename;
	vector<Movie> movies = GetMoviesFromCVS(filename);
	//vector<Movie> sortedMovi

	int choice;
	cout << "Would you like to search or sort movie categories?" << endl;
	cout << "Or would you like to compare the run times of search or sort algorithms?" << endl;
	cout << "0 - search" << endl;
	cout << "1 - sort" << endl;
	cout << "2 - Algorithm Complexities" << endl;

	cin >> choice;

	int choice1 ;
	if (choice == 0) { //////////////////////////////////////////////////////////////////Search CLI
		cout << "What category would you like to search by?" << endl;
		//we can search by: title, country, genre
		cout << "0 - Title" << endl;
		cout << "1 - Country" << endl;
		cout << "2 - Genre" << endl;
		cout << "3 - Duration" << endl;
		cout << "4 - Rating" << endl;
		cout << "5 - Year" << endl;
		cin >> choice1;
		if (choice1 == 0) { //////////////////////////////////////////////search by title
			string str;
			cout << "What Title would you like to find?" << endl;
			cin >> str;
			vector<Movie> movies1 = LinearfindTitle(str, movies);
			PrintMovies(movies1);
		}
		else if (choice1 == 1) { ////////////////////////////////////////search by country


		}
		else if (choice1 == 2) {/////////////////////////////////////////search by genre
			string str;
			cout << "What Genre would you like to find?" << endl;
			cin >> str;
			vector<Movie> movies1 = LinearfindGenre(str, movies);
			PrintMovies(movies1);
		}
		else if (choice1 == 3) {/////////////////////////////////////////search by duration
			int timestart;
			int timeend;
			cout << "what is the minimum desired duration?" << endl;
			cin >> timestart;
			cout << "what is the maximum desired duration?" << endl;
			cin >> timeend;
			vector<Movie> movies1 = findRangeDuration(timestart, timeend, movies);
			movies1 = bubbleSortDuration(movies1);
			PrintMovies(movies1);
		}
		else if (choice1 == 4) {/////////////////////////////////////////search by rating
			int ratestart;
			int rateend;
			cout << "what is the minimum desired rating?" << endl;
			cin >> ratestart;
			cout << "what is the maximum desired rating?" << endl;
			cin >> rateend;
			vector<Movie> movies1 =findRangeRating(ratestart, rateend, movies);
			movies1 = bubbleSortRating(movies1);
			PrintMovies(movies1);
		}
		else if (choice1 == 5) {/////////////////////////////////////////search by year
			int yearstart;
			int yearend;
			cout << "what is the oldest desired release year?" << endl;
			cin >> yearstart;
			cout << "what is the newest desired release year?" << endl;
			cin >> yearend;
			vector<Movie> movies1 = findRangeYear(yearstart, yearend, movies);
			movies1 = bubbleSortYear(movies1);
			PrintMovies(movies1);
		}
	}
	else if (choice == 1) { //////////////////////////////////////////////////////////////Sort CLI
		cout << "What category would you like to sort by?" << endl;
		//we can search by: year, rating, duration
		cout << "0 - Year" << endl;
		cout << "1 - Rating" << endl;
		cout << "2 - Duration" << endl;
		cin >> choice1;
		if (choice1 == 0) { ////////////////////////////////////////////////sort by year
			vector<Movie> movies1 = selectionSortYear(movies);
			PrintMovies(movies1);

		}
		else if (choice1 == 1) {/////////////////////////////////////////////sort by rating
			vector<Movie> movies2 = bubbleSortRating(movies);
			PrintMovies(movies2);

		}
		else if (choice1 == 2) {//////////////////////////////////////////////sort by duration
			vector<Movie> movies3 = bubbleSortDuration(movies);
			PrintMovies(movies3);
		}
	}
	else if (choice == 2) {
		cout << "What algorithm pairing would you like to compare the run times of?" << endl;
		//compare: selection sort and 
		cout << "0 - selection and bubble" << endl;
		cout << "1 - binary, exponential, and linear search" << endl;
		cin >> choice1;
		if (choice1 == 0) {
			//compare bubble and selection with year
			cout << "Comparing the selection and bubble sort using the movies years:" << endl;
			compareSelectionandBubble(movies);
		}
		else if (choice1 == 1) {
			//compare binary and exponential search
			comparebinaryandexponentialandlinear(movies);
		}
	}
	else {
		cout << "Incorrect input. Please restart program" << endl;
	}
	return 0;
}
