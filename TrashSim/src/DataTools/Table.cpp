#include "pch.h"

#include "Table.h"

Table::Table(const std::string& filename, std::function<double(double, const std::string&, size_t idx)> transform)
{
	std::ifstream in(filename);
	
	std::string line;
	if (!getline(in, line)) { 
		throw BadCSVException(); // There is no first line
	}
	
	std::stringstream lss(line);
	std::string value_str;
	if (!getline(lss, value_str, ',')) {
		throw BadCSVException(); // First line is empty
	}

	double value_double;
	bool has_header = false;
	try {
		value_double = std::stof(value_str);
	}
	catch (...) {
		has_header = true;
	}

	size_t col_count = 0;
	std::vector<std::string> tmp_names;
	if (has_header) {
		table.push_back(std::vector<double>());
		col_names.insert({ value_str, col_count });
		tmp_names.push_back(value_str);
		col_count++;

		while (getline(lss, value_str, ',')) { // getting all other column names
			tmp_names.push_back(value_str);
			table.push_back(std::vector<double>());
			col_names.insert({ value_str, col_count });
			col_count++;
		}
	}
	else {
		table.push_back(std::vector<double>(1, transform(value_double, "", col_count)));
		col_count++;

		while (getline(lss, value_str, ',')) { // getting all other double values
			try {
				value_double = std::stof(value_str);
			}
			catch (...) {
				throw BadCSVException();
			}

			table.push_back(std::vector<double>(1, transform(value_double, "", col_count)));
			col_count++;
		}
	}

	while (getline(in, line)) {
		lss = std::stringstream(line);
		for (size_t i = 0; i < col_count; i++) {
			if (!getline(lss, value_str, ',')) {
				throw BadCSVException(); // Number of values in a line is less than column count
			}

			try {
				value_double = std::stof(value_str);
			}
			catch (...) {
				throw BadCSVException();
			}

			std::string name = "";
			if (has_header) {
				name = tmp_names[i];
			}
			
			table[i].push_back(transform(value_double, name, i));
			
		}
	}
}

void Table::rename_col(const std::string& old_name, const std::string& new_name)
{
	auto it = col_names.find(old_name);
	if (it == col_names.end() || old_name == new_name) {
		return;
	}
	col_names.insert({ new_name, it->second });
	col_names.erase(old_name);
}