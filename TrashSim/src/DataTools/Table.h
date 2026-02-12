#pragma once

#include <vector>
#include <string>
#include <map>
#include <exception>
#include <functional>

class BadCSVException : public std::exception
{
public:
	const char* what() { return "CSV file format is wrong or unsupported"; }
};

// A class for CSV-tables with indexing by indices and column names
class Table
{
	std::vector <std::vector<double>> table;
	std::map<std::string, size_t> col_names;
public:
	Table(const std::string& filename, 
		std::function<double(double, const std::string&, size_t idx)> transform = [](double x, const std::string& s, size_t idx) {return x; });
	Table() {}
	inline const std::map<std::string, size_t>& get_col_names() { return col_names; }
	void rename_col(const std::string& old_name, const std::string& new_name);

	inline const std::vector<double>& operator[](size_t idx) const { return table[idx]; }
	inline const std::vector<double>& operator[](const std::string& name) const { return table[col_names.find(name)->second]; }
	
};