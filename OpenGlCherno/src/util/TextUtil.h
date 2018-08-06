#ifndef _TEXTUTIL
#define _TEXTUTIL

#include <vector>

//Returns true if loaded succesfully
bool loadTextFromFile(const std::string& location, std::vector<std::string>& data);

//Appends in the following order: lines[0] sep lines[1] sep...sep lines[size - 1]
std::string appendWithSeperator(const std::vector<std::string>& lines, const std::string& sep);

#endif