//city.h - Prototypes for city class, which contains data and functions
//relating to the position of a city in the TSP problem and its distance
//from other cities.
//Written by Sam Best for CS325
//Last modified 3/12/2013

#ifndef _city_h
#define _city_h

#include "math.h"
#include <fstream>
#include <vector>
#include <deque>


using namespace std;

class city
{
    public:
        city(int idin, int xin, int yin, int posin, bool visitedin);
        city(city & source);
        ~city();
        int dist(city * city_in); //calculates the Euclidean distance to another city
        int get_x(); //Returns x
        int get_y(); //Returns y
        int get_id(); //Returns id
        int get_pos(); //Returns pos
        int get_nl_size(); //Returns size of neighbor list
        city *& get_neighbor(int index); //Returns reference to city contained at neighbor_list[index]
        int get_neighbor_pos(int index); //Returns pos stored in city at neighbor_list[index]
        void set_pos(int pos_in); //Sets pos to pos_in
        void display_coords(); //Displays the x and y coords of the city
        void output_id(ostream & output); //Displays the id of the city
        int write_out(ofstream & write); //Writes the city id to file followed by \n
        int copy_city(city * city_in); //Copies a city from city_in
        int compare(const city * city_in); //Checks if city has equivalent id, x, y
        void build_neighbor_list(deque <city*> & cities, int num_cities); //Builds neighbor list sorted by distance, taking a deque of cities as input
        void push_to_list(city *& to_add); //Adds a city to the neighbor list
        bool nl_is_empty(); //Checks if neighbor list is empty
        void display_neighbor_list(); //Displays the neighbor list
    private:
        int id;
        int x;
        int y;
        int pos;
        bool visited;
        deque <city*> neighbor_list; //positions
};

#endif
