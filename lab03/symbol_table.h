#include "scope_table.h"
#include <iostream>
#include <fstream>


class symbol_table
{
private:
    scope_table *current_scope;
    int bucket_count;
    int current_scope_id;

public:
    symbol_table(int bucket_count);
    ~symbol_table();
    void enter_scope();
    void exit_scope();
    bool insert(symbol_info* symbol);
    symbol_info* lookup(symbol_info* symbol);
    void print_current_scope();
    void print_all_scopes(ofstream& outlog);

    // you can add more methods if you need 
    symbol_info* lookup(string name);
    bool delete_symbol(symbol_info* symbol);
    bool delete_symbol(string name);
    int get_current_scope_id();
};

// complete the methods of symbol_table class

symbol_table::symbol_table(int bucket_count)
{
    this->bucket_count = bucket_count;
    current_scope = NULL;
    current_scope_id = 1; 
    enter_scope(); 
}

symbol_table::~symbol_table()
{
    while (current_scope != NULL)
    {
        exit_scope();
    }
}

void symbol_table::enter_scope()
{
    current_scope = new scope_table(current_scope, bucket_count, current_scope_id++);
}

void symbol_table::exit_scope()
{
    if (current_scope != NULL)
    {
        scope_table *temp = current_scope;
        current_scope = current_scope->get_parent_scope();
        delete temp;
    }
}

bool symbol_table::insert(symbol_info* symbol)
{
    if (current_scope != NULL)
    {
        return current_scope->insert_in_scope(symbol);
    }
    return false;
}

symbol_info* symbol_table::lookup(symbol_info* symbol)
{
    if(symbol == NULL)
    {
        return NULL;
    }
    return lookup(symbol->get_name());
}

symbol_info* symbol_table::lookup(string name)
{
    scope_table *temp = current_scope;
    while (temp != NULL)
    {
        symbol_info *found = temp->lookup(name);
        if (found != NULL)
        {
            return found;
        }
        temp = temp->get_parent_scope();
    }
    return NULL;
}

bool symbol_table::delete_symbol(symbol_info* symbol)
{
    if (current_scope != NULL && symbol != NULL)
    {
        return current_scope->delete_from_scope(symbol);
    }
    return false;
}

bool symbol_table::delete_symbol(string name)
{
    if (current_scope != NULL)
    {
        return current_scope->delete_symbol(name);
    }
    return false;
}

void symbol_table::print_current_scope()
{
    if (current_scope != NULL)
    {
        ofstream dummy;
        current_scope->print_scope_table(dummy);
    }
    else
    {
        cout << "No current scope." << endl;
    }
}

void symbol_table::print_all_scopes(ofstream& outlog)
{
    outlog<<"################################"<<endl<<endl;
    scope_table *temp = current_scope;
    while (temp != NULL)
    {
        temp->print_scope_table(outlog);
        temp = temp->get_parent_scope();
    }
    outlog<<"################################"<<endl<<endl;
}

int symbol_table::get_current_scope_id()
{
    if (current_scope != NULL)
    {
        return current_scope->get_scope_id();
    }
    return -1; 
}