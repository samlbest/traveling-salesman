//city.cpp - Implementation of the city class, which manages data relating
//to a single city. x is the x coord of the city, y is the y coord. Distance
//to other cities is calculated using the Euclidean distance formula rounded
//to the nearest integer.
//Written by Sam Best for CS325
//Prototypes of city class
//Last modified 3/12/2013

#include "city.h"
#include "tree.h"
#include <iostream>
#include <fstream>
using namespace std;

const int LIST_SIZE = 5;

//Constructor that takes all members as input
city::city(int idin, int xin, int yin, int posin, bool visitedin) : id(idin), x(xin), y(yin), pos(posin), visited(visitedin) {}

//Copy constructor
city::city(city & source)
{
    x = source.x;
    y = source.y;
    pos = source.pos;
    id = source.id;
    visited = source.visited;
    neighbor_list = source.neighbor_list;
}

//Destructor (no dynamic memory)
city::~city()
{
}

//Calculates the Euclidean distance to city_in
int city::dist(city * city_in)
{
    float x2 = city_in->get_x();
    float y2 = city_in->get_y();
    
    x2 -= x;
    y2 -= y;
    
    x2 *= x2;
    y2 *= y2;
    
    return floor(sqrt(x2 + y2) + 0.5);  //Rounds down from 0.0 to .499_, rounds up from 0.5 to .99_
}

int city::get_x()
{
    return x;
}

int city::get_y()
{
    return y;
}

int city::get_id()
{
    return id;
}

int city::get_pos()
{
    return pos;
}

city *& city::get_neighbor(int index)
{
    return neighbor_list[index];
}

int city::get_nl_size()
{
    return LIST_SIZE;
}

void city::set_pos(int pos_in)
{
    pos = pos_in;
}

void city::display_coords()
{
    cout << id << " " << x << " " << y;
    return;
}

void city::output_id(ostream & output)
{
    output << id;
}

//Writes to file that is already open, takes ofstream object as parameter
int city::write_out(ofstream & write)
{
    if (write.is_open())
    {
        write << id << '\n';
        return 1;
    }
    
    return 0;
}

//Copies in a city and its neighbor list
int city::copy_city(city * city_in)
{
    if (city_in == NULL)
        return 0;
        
    id = city_in->id;
    x = city_in->x;
    y = city_in->y;
    pos = city_in->pos;
    visited = city_in->visited;
    
    neighbor_list = city_in->neighbor_list;
    return 1;
}

//Returns 1 if id, x, y are equivalent to those in city_in, otherwise returns 0
int city::compare(const city * city_in)
{
    if (city_in->id == id && city_in->x == x && city_in->y == y)
        return 1;
        
    else
        return 0;
}

//Builds a neighbor list from cities, sorted by distance
void city::build_neighbor_list(deque <city*> & cities, int num_cities)
{
    tree sorted(this); //Creates a tree with the current city as owner (to calculate distances for sorting)
    neighbor_list.clear(); //Erase existing neighbor list
    
    for (int i = 0; i < num_cities; ++i)
        sorted += cities[i]; //Add cities to BST
    
    //Build neighbor list of size LIST_SIZE or num_cities, whichever is smaller
    //(issues with this because my tree doesn't correctly sort when the recursive
    //function is cut off before going through the whole tree)
    if (LIST_SIZE < num_cities)
        sorted.build_neighbor_list(neighbor_list, LIST_SIZE);       
        
    else
        sorted.build_neighbor_list(neighbor_list, num_cities);
    
    //sorted.display_detailed_tree();

    cout << pos << " NEIGHBOR LIST SIZE: " << neighbor_list.size() << endl;
    sorted.clear_tree();

    return;
}

bool city::nl_is_empty()
{
    return neighbor_list.empty();
}

void city::push_to_list(city *& to_add)
{
    neighbor_list.push_back(new city(*to_add));
}

void city::display_neighbor_list()
{
    int size = neighbor_list.size();
    
    for (int i = 0; i < size; ++i)
    {
        cout << dist(neighbor_list[i]);
        cout << "actual index: " << i;
        cout << " stored pos: " << neighbor_list[i]->get_pos();
        cout << endl;
    }
    
    return;
}

int city::get_neighbor_pos(int index)
{
    return neighbor_list[index]->pos;
}

