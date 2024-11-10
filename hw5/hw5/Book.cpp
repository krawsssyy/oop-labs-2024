#include "Book.h"

Book::Book() {
	this->title = this->author = this->ISBN = this->publisher = "";
	this->year = 0;
	this->borrowed = false;
}

Book::Book(std::string title, std::string author, std::string ISBN, std::string publisher, int year, bool borrowed) : title(title), author(author),
ISBN(ISBN), publisher(publisher), year(year), borrowed(borrowed) {} // you can add newlines during some function calls or lists like this to make the code more readable

Book::Book(const Book* book) {
	this->title = book->title;
	this->author = book->author;
	this->ISBN = book->ISBN;
	this->publisher = book->publisher;
	this->year = book->year;
	this->borrowed = book->borrowed;
}

void Book::setTitle(std::string title) {
	this->title = title;
}

void Book::setAuthor(std::string author) {
	this->author = author;
}

void Book::setISBN(std::string ISBN) {
	this->ISBN = ISBN;
}

void Book::setPublisher(std::string publisher) {
	this->publisher = publisher;
}

void Book::setYear(int year) {
	this->year = year;
}

void Book::changeBorrow() {
	this->borrowed = !this->borrowed; // negate it to change its value (0 => 1/ 1 => 0)
}

std::string Book::getTitle() {
	return this->title;
}

std::string Book::getAuthor() {
	return this->author;
}

std::string Book::getISBN() {
	return this->ISBN;
}

std::string Book::getPublisher() {
	return this->publisher;
}

int Book::getYear() {
	return this->year;
}

bool Book::getBorrow() {
	return this->borrowed;
}

void Book::print() {
	std::cout << std::endl;
	std::cout << "Title: " << this->title << std::endl;
	std::cout << "Author: " << this->author << std::endl;
	std::cout << "ISBN: " << this->ISBN << std::endl;
	std::cout << "Publisher: " << this->publisher << std::endl;
	std::cout << "Year: " << this->year << std::endl;
	std::cout << "Borrowed: " << (this->borrowed ? "Yes" : "No") << std::endl << std::endl;
}