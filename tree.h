//"tree.h" - Contains the prototypes for the tree class, which manages a
//tree of items (mixed weapons and vehicles). Also contains the tree_node
//class.

/*The following operators are overloaded:
 * =: replaces a tree with the contents of another
 * +: used with any combination of trees and player_items. Final value is a tree.
 * +=: adds a tree or player_item to an existing tree
 * <<: sends a list of each item name in sorted order to the ostream
 * ==: compares two trees, returns true if the contents are the same (in position and value)
 * !=: compares two trees, returns true if the contents differ (in position or value)
*/ 

//Originally written by Sam Best for CS202, modified for CS325
//Originally written May 2012, last update 3/12/2013

#ifndef _tree_h
#define _tree_h

#include "city.h"
using namespace std;

class tree_node
{
    public:
        tree_node();
        tree_node *& get_left(); //returns pointer to left child
        tree_node *& get_right(); //returns pointer to right child
        int set_city(city *& city_in); //copies item_in into the node
        city *& get_city(); //returns the item contained in the node
    protected:
        city * tree_city;
        tree_node * left;
        tree_node * right;
};

class tree
{
    public:
        tree();
        tree(city * city_in);
        ~tree();
        tree(tree & source);
        void add_to_tree(city *& to_add); //Adds a new item to the tree
        void display_detailed_tree(); //Displays the tree sorted by name with item details
        void clear_tree(); //Removes all items from tree
        void build_neighbor_list(deque <city*> & neighbor_list, int size);
        //OPERATORS: See above for description
        bool operator == (tree & tree_in);
        bool operator != (tree & tree_in);
        tree & operator += (city * to_add);
        tree & operator += (tree & to_add);
        tree & operator = (tree & source);
        tree operator + (city * to_add);
        tree operator + (tree & tree_in);
        friend tree operator + (city * city_in,  tree & tree_in);
        friend ostream & operator << (ostream & output,  tree & source);
    private:
        city * owner_city;
        tree_node * root;
        void copy(tree_node * source, tree_node *& dest); //Recursive copy
        void insert(tree_node *& root, city *& to_add); //Recursive insert
        void traverse_and_display(tree_node * root); //Recursive display
        void traverse_and_add(tree_node * source, tree & dest); //Used to recursively copy a tree into an existing tree)
        void remove_all(tree_node *& root); //Recursive remove all
        void traverse_and_build(tree_node * root, deque <city*> & neighbor_list, int size);
        bool is_equal(tree_node * root_one = NULL, tree_node * root_two = NULL);
};

void traverse_and_output(ostream & output, tree_node * root);
#endif
