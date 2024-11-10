#pragma once
#include <string>
#include <iostream>

class Book {
	private:
		std::string title;
		std::string author;
		std::string ISBN;
		std::string publisher;
		int year;
		bool borrowed;
	public:
		Book();
		Book(std::string title, std::string author, std::string ISBN, std::string publisher, int year, bool borrowed);
		Book(const Book* book);

		void setTitle(std::string title);
		void setAuthor(std::string author);
		void setISBN(std::string ISBN);
		void setPublisher(std::string publisher);
		void setYear(int year);
		void changeBorrow();

		std::string getTitle();
		std::string getAuthor();
		std::string getISBN();
		std::string getPublisher();
		int getYear();
		bool getBorrow();

		void print();
};