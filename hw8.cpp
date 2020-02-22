#include <iostream>
#include <stdio.h> 
#include <limits.h> 
#include <fstream>
#include <string>
#include <iomanip>
#include "ArgumentManager.h"

/*
Geeks4Geeks article used as reference:
www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
Mohammed Habib helped with debugging printing function and heling me read the pathfile without getting segmentation fault on server.
*/

// Function to pick the minimum distance vertex from the set of vertices not yet processed.
int minDistance(double dist[], bool sptSet[], int matrix_size)
{
	// Initialize minimum value to maximum int value
	double minimum = INT_MAX;
	double min_vertex;

	for (int i = 0; i < matrix_size; i++)
	{
		if (sptSet[i] == false && dist[i] <= minimum)
		{
			minimum = dist[i];
			min_vertex = i;
		}
	}
	return min_vertex;
}

// Function that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation
void dijkstra(double **graph, int source, int destination, int matrix_size, ofstream &ofs)
{

	// The output array. dist[i] will hold the shortest distance from source to destination 
	double *dist = NULL;
	dist = new double[matrix_size];  

	// sptSet[i] will be true if vertex i is included in the shortest path tree or shortest distance from source to destination is finalized 
	bool *sptSet = NULL;
	sptSet = new bool[matrix_size]; 

	// Initialize all distances as INFINITE and stpSet[] as false 
	for (int i = 0; i < matrix_size; i++)
	{
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	// Distance of source vertex from itself is always 0 
	dist[source] = 0;

	// For loop finds the shortest path for all vertices 
	for (int count = 0; count < matrix_size - 1; count++)
	{
		/* Pick the minimum distance vertex from the set of vertices not yet processed. 
		Minimum distance vertex is always equal to source vertex in the first iteration. */
		int minDistanceVertex = minDistance(dist, sptSet, matrix_size);

		// Mark the picked vertex as processed 
		sptSet[minDistanceVertex] = true;
		
		/*In order to prevent calculating the minimum distance form source to all vertices,
		break the for loop when the minumum distance vertex equals our destination  */
		if (minDistanceVertex == destination)
		{
			break;
		}

		// Update dist value of the adjacent vertices of the picked vertex. 
		for (int i = 0; i < matrix_size; i++)
		{
			/* Update dist[i] only if:
			1. It is not in sptSet
			2. there is an edge from minimum distance vertex to source vertex
			3. total weight of path from source to destination through minimum distance vertex is smaller than current value of dist[i] */
			if (!sptSet[i] && graph[minDistanceVertex][i] && dist[minDistanceVertex] != INT_MAX && dist[minDistanceVertex] + graph[minDistanceVertex][i] < dist[i])
			{
				dist[i] = dist[minDistanceVertex] + graph[minDistanceVertex][i];
			}
		}
	}

	// print the constructed distance array 
	if (dist[destination] == INT_MAX)
	{
		ofs << "Infinite";
		return;
	}
	else
	{
		ofs << fixed << setprecision(1) << dist[destination];
		return;
	}

	return;
}

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string path = am.get("path");


	fstream pathfile(path);
	fstream infile(input);
	ofstream outfile(output);

	int coordinate_x; //will store i index of adjacency matrix for each edge value from input file
	int coordinate_y; //will store j index of adjacency matrix for each edge value from input file
	double edge_weight; //will store edge value of each vertex connection from input file to be stored in 2-s adjacency matrix
	int matrix_size = 0; //size of the matrix which will be stored form reading the largest index value in the input file

	//get the matrix size by comparing it against each index value and saving the largest value in matrix_size variable
	while (infile >> coordinate_x >> coordinate_y >> edge_weight)
	{
		if (matrix_size < coordinate_x)
		{
			matrix_size = coordinate_x;
		}
		if (matrix_size < coordinate_y)
		{
			matrix_size = coordinate_y;
		}
	}

	/*have to add 1 to the matrix_size variable to accomodate the fact that
	we are indexing starting from 1, but the computer starts from 0 index*/
	matrix_size = matrix_size + 1; 

	//initialize dynamic 2-d array
	double **graph = new double*[matrix_size];
	for (int i = 0; i < matrix_size; i++)
	{
		graph[i] = new double[matrix_size];
	}

	//fill 2-d array with all 0 values
	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 0; j < matrix_size; j++)
		{
			graph[i][j] = 0;
		}
	}

	//filling edge values in proper indexes of 0-filled array
	infile.clear(); //clearing buffer
	infile.seekg(0, ios::beg); //setting cursor back to beginning of input file for proper parsing

	//updating the zero-filled vertex with edge values in appropriate indices gathered form inputfile
	while (!infile.eof())
	{
		if (infile >> coordinate_x >> coordinate_y >> edge_weight)
		{
			graph[coordinate_x][coordinate_y] = edge_weight;
		}
	}

	int vertex_source; //will store first value in path file, which we will treat as the beginning of minumum distance path(source vertex)
	int vertex_destination; //will store second value in the path file, which we will treat as the end of the minimum distance path(destination vertex)

	//gather source and target vertex
	while (!pathfile.eof())
	{
		pathfile >> vertex_source >> vertex_destination;
	}
	
	//check if the target vertex exists in the graph before applying disjkstra
	if (vertex_source <= 0 || vertex_source >= matrix_size || vertex_destination <= 0 || vertex_destination >= matrix_size) 
	{
		outfile << "Infinite";
		return 0;
	}

	//check if source and target are the same before applying djikstra
	if (vertex_source == vertex_destination)
	{
		outfile << "0.0";
		return 0;
	}
	
	//calling diskstra function if none of the special cases are true
	dijkstra(graph, vertex_source, vertex_destination, matrix_size, outfile);

	return 0;
}