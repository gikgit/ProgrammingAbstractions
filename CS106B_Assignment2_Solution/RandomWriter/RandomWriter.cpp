/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <stdlib.h>
#include <time.h>

using namespace std;


void loadFileIntoString(string& article);
void statisticFile(string& article, int nOrder, map<string,int>& selectSeed);
string findSeed(map<string, int>& selectSeed);
void seedUpdate(string& article, string& seed, int nOrder, string& sentence);
void markovProb(map<string, double>& records, map<string, double>& cp);
void update(map<string, double>& cp, string & seed, string & sentence, int nOrder);

int main() {
	
	ifstream infile;
	string article = "";
	map<string,int> selectSeed;
	string sentence = "";
	
	loadFileIntoString(article);
	
	cout << "order?: ";
	int nOrder;
	cin >> nOrder;
	
	statisticFile(article,nOrder,selectSeed);
	string seed = findSeed(selectSeed);
	sentence += seed;
	
	for (int i=0; i<2000; i++) {
		seedUpdate(article, seed, nOrder, sentence);
	}
	
	cout << sentence << endl;
	
	return 0;
}

void loadFileIntoString(string& article) {	
	ifstream infile;
	
	string line;
	char c;

	infile.open("TomSawyer.txt");

	if(infile.fail()) {
		printf("Can't read the data file");
		infile.clear();
	}

	while (!infile.fail()) {
		getline(infile, line);
		line += '\n';
		article += line;
	}

}


void statisticFile(string& article, int nOrder, map<string,int>& selectSeed) {
	string str;
	int index;
	for(int i=0; i<article.length()-nOrder-1; i++) {
		int count = 0;
		int start = 0;
		str = article.substr(i,nOrder);
		while((index = article.find(str,start))!=string::npos) {
			count++;
			start = index + 1;
		}
		if(selectSeed.count(str) == 0) selectSeed.insert(pair<string,int>(str, count));
	}

}



string findSeed(map<string,int> & selectSeed) {
	int max = 0;
	string seed;

	for (map<string,int>::iterator it = selectSeed.begin(); it != selectSeed.end(); ++it){
		string key = it->first;
		int value = selectSeed.at(key);
		// cout << value << '\n';
		if(value>max) {
			max = value;
			seed = key;
		}
	}
	
	return seed;	
}


void seedUpdate (string& article, string& seed, int nOrder, string& sentence) {
		
	int index;
	string ch;
	map<string,double> records;
	map<string,double> cp;
	map<string,double>::iterator it;
	
	int start = 0;
	while((index = article.find(seed,start))!=string::npos) {
		ch = article.substr(index+nOrder,1);
		if (records.count(ch) > 0) {
			double val = records.at(ch);
			it = records.find(ch);
			records.erase(it);
			records.insert(pair<string,double>(ch,val+1.0));
		}
		else {
			records.insert(pair<string,double>(ch, 1.0));
		}
				
		start = index + 1;
	}
	
	if (records.size()!=0) {
		markovProb(records, cp);
		update(cp, seed, sentence, nOrder);
	}
	else {
		seed += " ";
		seed = seed.substr(1, nOrder);
	}
}

void markovProb(map<string,double> & records, map<string,double> & cp){
	int sum = 0;	
	map<string,double>::iterator it;

	for (it=records.begin(); it!=records.end(); ++it)
	{
		sum += it->second;
	}
	
	for (it=records.begin(); it!=records.end(); ++it)
	{
		string key = it->first;
		double per = it->second/(sum+1);
		if(per < 0.0001) per = 0.0;
		cp.insert(pair<string, double>(key, per));
	}
}

void update(map<string,double>& cp, string& seed, string& sentence, int nOrder) {

	double max = 0;
	string choice = "";
	vector<string> choices;
	srand (time(NULL));

	for (map<string,double>::iterator it=cp.begin(); it!=cp.end(); ++it)
	{
		string key = it->first;
		double val = it->second;
		if(val > max) {
			max = val;
		}
	}

	for (map<string,double>::iterator it=cp.begin(); it!=cp.end(); ++it)
	{	
		if(it->second == max) {
			choices.push_back(it->first);
		}
	}

	int pos = rand() % choices.size();
	choice = choices.at(pos);	
	seed += choice; 
	seed = seed.substr(1, nOrder);
	sentence += choice;
}



