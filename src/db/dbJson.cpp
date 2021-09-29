/****************************************************************************
  FileName     [ dbJson.cpp ]
  PackageName  [ db ]
  Synopsis     [ Define database Json member functions ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2015-present LaDs(III), GIEE, NTU, Taiwan ]
 ****************************************************************************/

#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <climits>
#include <cmath>
#include <string>
#include <algorithm>
#include "dbJson.h"
#include "util.h"

using namespace std;

/*****************************************/
/*          Global Functions             */
/*****************************************/
ostream&
operator << (ostream& os, const DBJsonElem& j)
{
	os << "\"" << j._key << "\" : " << j._value;
	return os;
}

istream& operator >> (istream& is, DBJson& j)
{
	// TODO: to read in data from Json file and store them in a DB 
	// - You can assume the input file is with correct JSON file format
	// - NO NEED to handle error file format
	assert(j._obj.empty());
	j.fflag = true;
	string line;
	string k;
	int v;
	string a,b;
    while(is.good()){
        getline(is,line);
		if(line == "")
			continue;
		if((int)line.find('{')!=-1 || (int)line.find('}')!=-1 )
			continue;
		int fir = line.find_first_of(':');
		a = line.substr(0,fir);
		b = line.substr(fir + 1, line.length() - fir - 1);
		int first_index = a.find_first_of('"');
		int last_index = a.find_last_of('"');
		k = a.substr(first_index + 1,last_index - first_index - 1);
		string b1;
		for(int i = 0;i < (int)b.length();i++){
			if((b[i] <= '9' && b[i] >= '0') || b[i] == '-')
				b1 += b[i];
		}
		stringstream ss;
		ss << b1;
		ss >> v;
		DBJsonElem jsonelem(k,v);
		j._obj.push_back(jsonelem);
	}	
	return is;
}

ostream& operator << (ostream& os, const DBJson& j)
{
	// TODO
	os << "{" << endl;
	size_t i = 0;
	while(i < j.size()){
	   DBJsonElem temp = j[i]; 
	   os << "  " << j[i];
       if(i == j.size() - 1){
           os << endl;
		   break;
	   }
	   os << "," << endl;
	   i++;
	}
    cout << "}" << endl;
	return os;
}

/**********************************************/
/*   Member Functions for class DBJsonElem    */
/**********************************************/
/*****************************************/
/*   Member Functions for class DBJson   */
/*****************************************/
void
DBJson::reset()
{
	// TODO
	_obj.clear();
}

// return false if key is repeated
bool
DBJson::add(const DBJsonElem& elm)
{
	// TODO
	size_t i = 0;
	int count = 0;
	while(i < size()){
		DBJsonElem j = _obj.at(i);
		if(elm.key() == j.key()){
			count++;
		}
		i++;
	}
	if(count != 0)
	  return false;
	else{
		DBJsonElem j_new(elm.key(),elm.value());
		_obj.push_back(j_new);
	}
	return true;
}

// return NAN if DBJson is empty
float
DBJson::ave() const
{
	// TODO
	if(size() == 0)
		return NAN;  
	double sum = 0;
	float ave;
	size_t i = 0;
	while(i < size()){
		DBJsonElem j = _obj.at(i);
		sum += j.value();
		i++;
	}
	ave = sum / size();
	
	return ave;
}

// If DBJson is empty, set idx to size() and return INT_MIN
int
DBJson::max(size_t& idx) const
{
	// TODO
	int maxN = INT_MIN;
	if(size() == 0){
	    idx = size();
		return maxN;
	}
	else{ 
		DBJsonElem MAX;	
		size_t i = 0;
		while(i < size()){
			DBJsonElem j = _obj.at(i);
			if(maxN < j.value()){
				maxN = j.value();
				MAX = j;
				idx = i;
			}
			i++;
		}
	}	
	return  maxN;
}

// If DBJson is empty, set idx to size() and return INT_MIN
int
DBJson::min(size_t& idx) const
{
	// TODO
	int minN = INT_MAX;
	if(size() == 0){
	    idx = size();
		return minN;
	}
	else{
		DBJsonElem MIN;	
		size_t i = 0;
		while(i < size()){
			DBJsonElem j = _obj.at(i);
			if(minN > j.value()){
				minN = j.value();
				MIN = j;
				idx = i;
			}
			i++;
		}
	}
	return  minN;
}

void
DBJson::sort(const DBSortKey& s)
{
	// Sort the data according to the order of columns in 's'
	::sort(_obj.begin(), _obj.end(), s);
}

void
DBJson::sort(const DBSortValue& s)
{
	// Sort the data according to the order of columns in 's'
	::sort(_obj.begin(), _obj.end(), s);
}

// return 0 if empty
int
DBJson::sum() const
{
	// TODO
	int s = 0;
    if(empty()){
		return 0;
	} 
	else{
		size_t i = 0;
		while(i < size()){
			DBJsonElem j = _obj.at(i);
			s += j.value();
			i++;
		}
	}
	return s;
}
