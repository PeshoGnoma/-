#include <iostream>
#include <string>
#include <list>
using namespace std;

class BookPage {
private:
	string content;
public:
	int number;
	// explicit constructor
	BookPage(int num, string str) : number(num), content(str) {}
	// implied constructor
	BookPage() : number(0), content("") {}
	void exchangeContent(BookPage& page) {
		string temp = page.content;
		page.content = this->content;
		this->content = temp;
	}

	bool operator==(const BookPage& page) {
		return (this->number == page.number && this->content == page.content);
	}

	bool operator<(const BookPage& page) {
		return (this->number < page.number);
	}

	string toString() {
		return "Page number: " + to_string(number) + "\nContent: " + content;
	}

	friend ostream& operator<<(ostream& out, const BookPage& page) {
		out << "Page number: " << page.number << "\nContent: " << page.content;
		return out;
	}
	friend istream& operator>>(istream& in, BookPage& page) {
		cout << "Enter page number: ";
		in >> page.number;
		cout << "Enter page content: ";
		in >> page.content;
		return in;
	}
};

class BookEditor {
public:
	virtual list<BookPage> generateBook(string title, int numberPages) = 0;
	virtual void swapPages(int firstPN, int secondPN) = 0;
};

class Book : public BookEditor {
private:
	string title;
	list<BookPage> pages;
public:
	// explicit constructor
	Book(string t, int numberPages) : title(t) {
		for (int i = 0; i < numberPages; i++) {
			pages.push_back(BookPage(i + 1, ""));
		}
	}
	// default constructor
	Book(string t) : title(t) {}

	void addPage(BookPage page) {
		pages.push_back(page);
	}

	void changePage(BookPage page) {
		for (auto& p : pages) {
			if (p.number == page.number) {
				p = page;
				break;
			}
		}
	}

	void removePage(int pageNumber) {
		for (auto it = pages.begin(); it != pages.end(); it++) {
			if (it->number == pageNumber) {
				pages.erase(it);
				break;
			}
		}
	}

	void exchangeContents(BookPage& page1, BookPage& page2) {
		for (auto& p : pages) {
			if (p.number == page1.number) {
				p.exchangeContent(page2);
				break;
			}
		}
	}

	string toString() {
		string str = "Title: " + title + "\n";
		for (auto& p : pages) {
			str += p.toString() + "\n";
		}
		return str;
	}

	// virtual functions from BookEditor
	list<BookPage> generateBook(string title, int numberPages) {
		list<BookPage> book;
		for (int i = 0; i < numberPages; i++) {
			book.push_back(BookPage(i + 1, ""));
		}
		return book;
	}

	void swapPages(int firstPN, int secondPN) {
		BookPage page1;
		BookPage page2;
		bool found1 = false;
		bool found2 = false;
		for (auto& p : pages) {
			if (p.number == firstPN) {
				page1 = p;
				found1 = true;
			}
			if (p.number == secondPN) {
				page2 = p;
				found2 = true;
			}
			if (found1 && found2) {
				break;
			}
		}
		if (found1 && found2) {
			page1.exchangeContent(page2);
		}
		else {
			cout << "One or both of the specified pages were not found." << endl;
		}
	}
};

int main() {
	Book book("My Book", 10);
	cout << book.toString() << endl;

	BookPage page(11, "This is a new page.");
	book.addPage(page);
	cout << book.toString() << endl;

	book.removePage(10);
	cout << book.toString() << endl;

	book.swapPages(1, 2);
	cout << book.toString() << endl;

	return 0;
}