//===================================================================================================================
//======
// Name : SP_Project.cpp
// Author : Abdulrahman Mohamed & Ali Ibrahim & Ali Ahmed & Abdulrahman Fakhry & Youssef Ahmed & Ali Osama & Ali Sameh
// Copyright : Your copyright notice
// Description : Hello World in C++, Ansi-style
//===================================================================================================================
//======

//basic code
#include<iostream>
#include<fstream>
#include<dirent.h>
#include<string>
#include<cstring>
using namespace std;
string To_UpperCase(string text);
void choice_menu(void);
string File_TO_String(ifstream& inputFile);
void word_replace(string fileName);
void in_File_replace(string& FileData, const string& old_value, const string& new_value);
void add_word(string fileName);
void word_delete(string fileName);

string To_UpperCase(string text)
{
	char* characters;
	characters = &text[0];//characters pointer that points to the address of every char in string text
	char* res = _strupr(characters);
	return res;
}

void search_dir(const char* path) {
	dirent* entry;
	DIR* dir = opendir(path);
	int num_of_files = 0, num_of_true_files = 0;
	//char answ;
	string word, new_word, arr_of_files[100], files_true[100];
	if (dir == NULL)
	{
		cout << "files not found";
	}
	for (int i = 0; (entry = readdir(dir)) != NULL; i++) {
		arr_of_files[i] = entry->d_name; //1-. 2-.. 3-myfile 4-myfile1 5-myfile2 6-myfile3 7-myfile4
		num_of_files++; //to find the number of files in folder
	}
	cout << "Write the word you're searching for\n";
	cin >> word;

	for (int i = 2; i < num_of_files; i++)
	{
		string file_path; //1-path = myfile
		file_path = arr_of_files[i];
		fstream file(file_path.c_str()); //a file to read from

		if (file.is_open()) //no error with opening
		{
			int countwords = 0;
			string candidate, candidateupper, wordupper;
			while (file >> candidate) // for each candidate word read from the file
			{
				wordupper = To_UpperCase(word);
				candidateupper = To_UpperCase(candidate);

				if (wordupper == candidateupper)
					++countwords; //counter : found number of times

			}

			if (countwords != 0)
			{
				cout << "The word '" << word << "' found : " << countwords << " times in file : " << file_path << "\n";
				num_of_true_files++;
				files_true[num_of_true_files] = file_path;

			}

		}

		else //there is error with opening
		{
			cout << "Error! file : " << file_path << " not opened!\n";

		}

	}

	cout << "\nthe word you entered is found in these files : \n";//to show names of files in which we found the word
	for (int j = 0; j <= num_of_true_files; j++)
	{
		cout << files_true[j] << "\n";
	}
	closedir(dir);

	choice_menu();

}

string File_TO_String(ifstream& inputFile)
{
	// function to read the Input File Stream and Return it's Data
	string FileData;
	for (char ch; inputFile.get(ch); FileData.push_back(ch)) {}//put file data into a string char by char
	return FileData;
}

void add_word(string fileName) //add word
{
	string word_added;
	fstream file(fileName);
	file.close();//to check that this file is not already opened
	cout << "Enter a word to be added\n";
	cin >> word_added;
	file.open(fileName, ios::app);
	file << "" << endl;//add a space at the end of file text
	file << word_added;//to add the word into our file at the end of it
	// << write
	// >> Read
	cout << "Done !\nAdded to file. ";
}

void word_replace(string fileName) {
	string word, newword;
	cout << "Write the word you want to replace \n";
	cin >> word;
	ifstream file(fileName);

	file.close();//to check that our file is not already opened
	cout << "Enter the new word\n";
	cin >> newword;
	file.open(fileName);
	if (file.is_open())
	{
		cout << "file opened...\n";
		string Filecontents = File_TO_String(file);
		in_File_replace(Filecontents, word, newword);
		ofstream file(fileName);
		file << Filecontents;//to write the changes into our file

	}
	char choice;
	cout << "Do you want to replace another word in this file? (y/n)\n";
	cin >> choice;
	if (choice == 'y')
	{
		word_replace(fileName);
	}
	else if (choice == 'n')
	{
		cout << "\nDone! \n";
	}
	else
	{
		cout << "Input Erorr!";
	}

}

void choice_menu(void)
{
	int choice;
	string n;
	string file_name;
	cout << "which file you want?\n";
	cin >> file_name;
	cout << "Do you want to :\n 1-Add a new word\n 2-Edit this word \n 3-Delete this word \n";
	cin >> choice;
	switch (choice) {
	case 1: {
		add_word(file_name);
		break;
	}
	case 2: {
		word_replace(file_name);
		break;
	}

	case 3: {
		word_delete(file_name);
		break;
	}

	default: {
		cout << "\nInput error !\n";
		break;
	}
		   break;
	}
}

void in_File_replace(string& FileData, const string& old_value, const string& new_value)
{
	// Get the first occurence of the old_value string.
	// get the position of the string
	auto pos = FileData.find(old_value);//first initial value

	while (pos != string::npos)//no position
	{
		FileData.replace(pos, old_value.length(), new_value);
		// Continue searching from here.
		pos = FileData.find(old_value, pos);//second initial value
	}
}

void word_delete(string fileName) {
	string word, newword;
	cout << "Write the word you want to delete \n";
	cin >> word;
	newword = "";
	ifstream file(fileName);
	file.close();
	file.open(fileName);
	if (file.is_open())
	{
		cout << "file opened...\n";
		string Filecontents = File_TO_String(file);
		in_File_replace(Filecontents, word, newword);
		ofstream file(fileName);

		file << Filecontents;
		// << write
		// >> Read
	}
	char choice;
	cout << "Do you want to delete another word in this file? y/n\n";
	cin >> choice;
	if (choice == 'y')
	{
		word_delete(fileName);
	}
	else {
		cout << "\nDone !\n";
	}

}

int main() {
	cout << "Hello !\n";
	char control;
	do
	{
		search_dir("C:\\Users\\abdu3\\source\\repos\\mini search app_finish1\\Project1\\New folder");
		cout << "\n would you like to another task (y/n)\n";
		cin >> control;
	} while (control != 'n');
}