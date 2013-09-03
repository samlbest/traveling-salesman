//"tree.cpp" - Contains the implementation of the tree class. The data structure
//is a binary search tree of cities, sorted by relative distance to oother cities.
//Originally written by Sam Best for CS202, modified for CS325
//Originally written May 2012, last update 3/12/2013

#include "tree.h"
#include <iostream>
using namespace std;

//TREE NODE:
//tree_node constructor:
tree_node::tree_node() : tree_city(NULL), left(NULL), right(NULL) {}

//Return left pointer
tree_node *& tree_node::get_left()
{
    return left;
}

//Return right pointer
tree_node *& tree_node::get_right()
{
    return right;
}

//Set the item to item_in
int tree_node::set_city(city *& city_in)
{
    if (!city_in)
        return 0;
        
    //tree_city->copy_city(city_in);
    //tree_city = new city(*city_in);
    tree_city = city_in;
    
    return 1;
}

//Return the item
city *& tree_node::get_city()
{
    return tree_city;
}

//TREE
//tree constructor:
tree::tree() : owner_city(NULL), root(NULL) {}

tree::tree(city * city_in) : owner_city(city_in), root(NULL) {}

tree::~tree()
{
    clear_tree();
}

//Copy constructor:
tree::tree(tree & source)
{
    copy(source.root, root);
}

//Recursive copy function:
void tree::copy(tree_node * source, tree_node *& dest)
{
    if (!source)
        dest = NULL;
        
    else
    {
        dest = new tree_node;
        dest->set_city(source->get_city());
        copy(source->get_left(), dest->get_left());
        copy(source->get_right(), dest->get_right());
    }
}

//Adds a new item to the tree
void tree::add_to_tree(city *& to_add)
{
    insert(root, to_add);
}

//Recursive insert function:
void tree::insert(tree_node *& root, city *& to_add)
{
    if (!root)
    {
        root = new tree_node;
        root->set_city(to_add);
        root->get_left() = root->get_right() = NULL;
    }
    
    else if (root->get_city()->dist(owner_city) < owner_city->dist(to_add))
        insert(root->get_left(), to_add);
        
    else
        insert(root->get_right(), to_add);
}

//Wrapper function for displaying the tree recursively
void tree::display_detailed_tree()
{
    traverse_and_display(root);
}

//In-order traversal of the tree, calls the player_item display functions
void tree::traverse_and_display(tree_node * root)
{
    if (!root)
        return;
    else
    {
        traverse_and_display(root->get_right());
        //root->get_city()->display_coords();
        cout << root->get_city()->dist(owner_city) << endl;
        traverse_and_display(root->get_left());
    }
}

//Does post-order traversal, adding each item from the source tree to the dest
void tree::traverse_and_add(tree_node * source, tree & dest)
{
    if (!source)
        return;
        
    else
    {
        traverse_and_add(source->get_left(), dest);
        traverse_and_add(source->get_right(), dest);
        dest.add_to_tree(source->get_city());
    }
}

//Wrapper function for recursive remove all, which removes all nodes from the tree.
void tree::clear_tree()
{
    remove_all(root);
}

//Recursive remove all
void tree::remove_all(tree_node *& root)
{
    if (!root)
        return;
        
    remove_all(root->get_left());
    remove_all(root->get_right());
    
    //delete root->get_city(); **don't want to free city memory
    //delete owner_city;
    delete root;
    root = NULL;
    //owner_city = NULL;
}

//Recursively compares each node of two trees -- if any differ, returns false
bool tree::is_equal(tree_node * root_one, tree_node * root_two)
{   
    if ((!root_one && root_two) || (root_one && !root_two))
        return false;
        
    else if (!root_one && !root_two)
        return true;
        
    return (!root_one->get_city()->compare(root_two->get_city())
        && is_equal(root_one->get_left(), root_two->get_left())
        && is_equal(root_one->get_right(), root_two->get_right()));
}

//Builds a neighbor list
void tree::build_neighbor_list(deque <city*> & neighbor_list, int size)
{
    traverse_and_build(root, neighbor_list, size);
}

void tree::traverse_and_build(tree_node * root, deque <city*> & neighbor_list, int size)
{
    if (!root)
        return;
           
    else
    {
        traverse_and_build(root->get_right(), neighbor_list, size-1);
        neighbor_list.push_back(root->get_city());
        traverse_and_build(root->get_left(), neighbor_list, size-1);
    }
}
//***************************************************************
//***************************OPERATORS***************************
//Add a player_item to an existing tree
tree & tree::operator += ( city * to_add)
{
    add_to_tree(to_add); //adds the item to the tree
    return *this;
}

//Adds a tree to an existing tree
tree & tree::operator += ( tree & to_add)
{
    tree temp;
    if (this == &to_add) //if same object passed, need to copy it into temp tree
    {
        temp = to_add;
        traverse_and_add(temp.root, *this);
        return *this;
    }
    
    traverse_and_add(to_add.root, *this);
    return *this;
}

//Sets the tree equal to the other
tree & tree::operator = ( tree & source)
{
    if (this == &source)
        return *this;
        
    if (root)
        clear_tree();
        
    copy(source.root, root);
    return *this;
}

//Adds an item to the tree, residual value is a temporary tree
tree tree::operator + ( city * to_add)
{
    tree temp;
    copy(root, temp.root);
    temp.add_to_tree(to_add);
    return temp;
}

//Adds a tree to a tree, residual value is a temporary tree
tree tree::operator + ( tree & tree_in)
{
    tree temp = tree_in;
    traverse_and_add(root, temp);
    return temp;
}

//Returns true if the two trees are equivalent
bool tree::operator == ( tree & tree_in)
{
    if (this == &tree_in)
        return true;
        
    else if (!root && !tree_in.root)
        return true;
    
    else
        return is_equal(root, tree_in.root);
}

//Returns true if the two trees are not equivalent
bool tree::operator != ( tree & tree_in)
{
    if (this == &tree_in)
        return false;
        
    else if (!root && !tree_in.root)
        return false;
    
    else
        return !is_equal(root, tree_in.root);
}

//Adds a tree and an item, alternate arg
tree operator + ( city * item_in,  tree & tree_in)
{
    tree temp = tree_in;
    temp.add_to_tree(item_in);
    return temp;
}

//Displays an ordered list of the items in the tree
ostream & operator << (ostream & output,  tree & source)
{
    traverse_and_output(output, source.root);
    return output;
}

//Recursively outputs all item names in a BST:
void traverse_and_output(ostream & output, tree_node * root)
{
        if (!root)
            return;
            
        traverse_and_output(output, root->get_left());
        root->get_city()->output_id(output);
        output << endl;
        traverse_and_output(output, root->get_right());
}    
