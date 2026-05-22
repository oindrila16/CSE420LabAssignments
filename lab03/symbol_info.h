#include<bits/stdc++.h>
using namespace std;

class symbol_info
{
private:
    string name;
    string type;

    // Write necessary attributes to store what type of symbol it is (variable/array/function)
    string symbol_type; 
    // Write necessary attributes to store the type/return type of the symbol (int/float/void/...)
    string data_type;
    // Write necessary attributes to store the parameters of a function
    vector<string> parameter_types; 
    vector<string> parameter_names;
    // Write necessary attributes to store the array size if the symbol is an array
    int array_size;

public:
    symbol_info(string name, string type, string symbol_type = "", vector<string> parameter_types = vector<string>(), vector<string> parameter_names = vector<string>())
    {
        this->name = name;
        this->type = type;
        this->symbol_type = symbol_type;
        this->array_size = 0;
        this->parameter_types = parameter_types;
        this->parameter_names = parameter_names;
    }
    
    string get_name()
    {
        return name;
    }
    void set_name(string name)
    {
        this->name = name;
    }

    string get_type()
    {
        return type;
    }
    void set_type(string type)
    {
        this->type = type;
    }

    string get_symbol_type()
    {
        return symbol_type;
    }
    void set_symbol_type(string symbol_type)
    {
        this->symbol_type = symbol_type;
    }
    
    string get_data_type()
    {
        return data_type;
    }
    void set_data_type(string data_type)
    {
        this->data_type = data_type;
    }
    
    int get_array_size()
    {
        return array_size;
    }
    void set_array_size(int array_size)
    {
        this->array_size = array_size;
    }
    
    vector<string> get_param_types()
    {
        return parameter_types;
    }
    void set_param_types(vector<string> param_types)
    {
        this->parameter_types = param_types;
    }
    
    vector<string> get_param_names()
    {
        return parameter_names;
    }
    void set_param_names(vector<string> param_names)
    {
        this->parameter_names = param_names;
    }
    
    void add_parameter(string param_type, string param_name)
    {
        parameter_types.push_back(param_type);
        parameter_names.push_back(param_name);
    }
    
    int get_param_count()
    {
        return parameter_types.size();
    }
    
    bool is_function()
    {
        return symbol_type == "Function";
    }
    
    bool is_array()
    {
        return symbol_type == "Array";
    }
    
    string get_param_string()
    {
        string result = "";
        for (int i = 0; i < parameter_types.size(); i++)
        {
            result += parameter_types[i];
            if (!parameter_names[i].empty())
                result += " " + parameter_names[i];
                
            if (i < parameter_types.size() - 1)
                result += ", ";
        }
        return result;
    }
    
    string get_full_name()
    {
        if (is_array())
            return name + "[" + to_string(array_size) + "]";
        return name;
    }

    ~symbol_info()
    {
        // No dynamic memory allocation in this class, so nothing to deallocate
    }
};