/*
*	Andrew Ngo, Owen Boxx
*	May 6, 2020
*	CS 302 Final Project - Traveling Salesman Problem
*	Main driver file
*/


#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;

void setCities(vector<Edge> &x);

int main(){
	vector<Edge> edges;
	setCities(edges);
	Graph path(edges);

	return 0;
}

void setCities(vector<Edge> &x){
	x.push_back(Edge{Point{0,"Reno"},Point{1,"San Francisco"},int{218}});
	x.push_back(Edge{Point{0,"Reno"},Point{2,"Salt Lake City"},int{518}});
	x.push_back(Edge{Point{0,"Reno"},Point{3,"Seattle"},int{704}});
	x.push_back(Edge{Point{0,"Reno"},Point{4,"Las Vegas"},int{439}});
	x.push_back(Edge{Point{1,"San Francisco"},Point{3,"Seattle"},int{808}});
	x.push_back(Edge{Point{1,"San Francisco"},Point{4,"Las Vegas"},int{569}});
	x.push_back(Edge{Point{2,"Salt Lake City"},Point{4,"Las Vegas"},int{421}});
	x.push_back(Edge{Point{2,"Salt Lake City"},Point{3,"Seattle"},int{830}});
	x.push_back(Edge{Point{4,"Las Vegas"},Point{3,"Seattle"},int{1115}});
	return;
}