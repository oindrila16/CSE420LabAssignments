#include "symbol_info.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class scope_table
{
private:
    int bucket_count;
    int unique_id;
    scope_table *parent_scope = NULL;
    vector<list<symbol_info *>> table;
    int scope_id;

    int hash_function(string name)
    {
        int hash = 0;
        for (char c : name)
        {
            hash = (hash + c) % bucket_count;
        }
        return hash;
    }

public:
    scope_table();
    scope_table(scope_table *parent_scope, int bucket_count, int unique_id);
    scope_table *get_parent_scope();
    int get_unique_id();
    symbol_info *lookup_in_scope(symbol_info* symbol);
    bool insert_in_scope(symbol_info* symbol);
    bool delete_from_scope(symbol_info* symbol);
    void print_scope_table(ofstream& outlog);
    ~scope_table();

    // you can add more methods if you need
    symbol_info *lookup(string name);
    bool delete_symbol(string name);
    int get_bucket_count();
    int get_scope_id();
};

// complete the methods of scope_table class

scope_table::scope_table(scope_table *parent_scope, int bucket_count, int unique_id)
{
    this->bucket_count = bucket_count;
    this->unique_id = unique_id;
    this->scope_id = unique_id;
    this->parent_scope = parent_scope;
    table.resize(bucket_count);
}

scope_table::scope_table()
{
    this->bucket_count = 0;
    this->unique_id = 0;
    this->scope_id = 0;
    this->parent_scope = NULL;
}

scope_table::~scope_table()
{
    for (int i = 0; i < bucket_count; i++)
    {
        for (auto it = table[i].begin(); it != table[i].end(); ++it)
        {
            delete *it;
        }
    }
}

scope_table *scope_table::get_parent_scope()
{
    return parent_scope;
}

int scope_table::get_unique_id()
{
    return unique_id;
}

int scope_table::get_bucket_count()
{
    return bucket_count;
}

symbol_info *scope_table::lookup_in_scope(symbol_info* symbol)
{
    if (symbol == NULL)
    {
        return NULL;
    }
    return lookup(symbol->get_name());
}

symbol_info *scope_table::lookup(string name)
{
    int index = hash_function(name);
    for (auto it = table[index].begin(); it != table[index].end(); ++it)
    {
        if ((*it)->get_name() == name)
        {
            return *it;
        }
    }
    return NULL;
}

bool scope_table::insert_in_scope(symbol_info* symbol)
{
    if (symbol == NULL)
    {
        return false;
    }
    int index = hash_function(symbol->get_name());
    for (auto it = table[index].begin(); it != table[index].end(); ++it)
    {
        if ((*it)->get_name() == symbol->get_name())
        {
            return false; 
        }
    }
    table[index].push_back(symbol);
    return true; 
}

bool scope_table::delete_from_scope(symbol_info* symbol)
{
    if (symbol == NULL)
    {
        return false;
    }
    return delete_symbol(symbol->get_name());
}

bool scope_table::delete_symbol(string name)
{
    int index = hash_function(name);
    for (auto it = table[index].begin(); it != table[index].end(); ++it)
    {
        if ((*it)->get_name() == name)
        {
            delete *it; 
            table[index].erase(it); 
            return true; 
        }
    }
    return false; 
}

void scope_table::print_scope_table(ofstream& outlog)
{
    outlog << "ScopeTable # " << unique_id << endl;

   
    for (int i = 0; i < bucket_count; i++)
    {
        if (!table[i].empty())
        {
            for (auto it = table[i].begin(); it != table[i].end(); ++it)
            {
                outlog << i << " --> " << endl;
                outlog << "< " << (*it)->get_name() << " : " << (*it)->get_type() << " >" << endl;
                
                if ((*it)->get_symbol_type() == "Array") {
                    outlog << "Array" << endl;
                    outlog << "Type: " << (*it)->get_data_type() << endl;
                    outlog << "Size: " << (*it)->get_array_size() << endl;
                } else if ((*it)->get_symbol_type() == "Function Definition") {
                    outlog << "Function Definition" << endl;
                    outlog << "Return Type: " << (*it)->get_data_type() << endl;
                    outlog << "Number of Parameters: " << (*it)->get_param_count() << endl;
                    outlog << "Parameter Details: " << (*it)->get_param_string() << endl;
                } else if ((*it)->get_symbol_type() == "Variable" || (*it)->get_symbol_type() == "") {
                    outlog << "Variable" << endl;
                    if ((*it)->get_data_type() != "") {
                        outlog << "Type: " << (*it)->get_data_type() << endl;
                    }
                }
                outlog << endl;
            }
        }
    }
}

int scope_table::get_scope_id()
{
    return scope_id;
}