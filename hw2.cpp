#include <iostream>
#include <vector>
#include <string>

class Book {
public:
    std::string title;
    std::string author;

    Book(std::string title, std::string author) : title(title), author(author) {}
};

class Library {
private:
    std::vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void removeBook(const std::string& title) {
        auto it = std::remove_if(books.begin(), books.end(), [&](const Book& book) {
            return book.title == title;
        });
        books.erase(it, books.end());
    }

    void displayBooks() const {
        for (const auto& book : books) {
            std::cout << "Title: " << book.title << ", Author: " << book.author << std::endl;
        }
    }
};

int main() {
    Library myLibrary;
    myLibrary.addBook(Book("1984", "George Orwell"));
    myLibrary.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald"));

    std::cout << "Library Contents:" << std::endl;
    myLibrary.displayBooks();

    myLibrary.removeBook("1984");
    std::cout << "\nAfter Removing a Book:" << std::endl;
    myLibrary.displayBooks();

    return 0;
}
