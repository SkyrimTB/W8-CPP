# Improve Codes with SOLID principles
## Introduction
The `hw2.cpp` file is a program which I wrote in my undergraduate, I will analyze it with SOLID Principles

### My Library System Program

```cpp
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
```

### Analysis According to SOLID Principles

#### What does it do well?

- **Single Responsibility Principle (SRP)**: This principle is well-followed. The `Book` class is responsible for book-related data, and the `Library` class manages a collection of books, including adding, removing, and displaying them.
- **Open/Closed Principle (OCP)**: The program is partially compliant. It's easy to extend the `Library` class with more functionality without modifying its existing code. For example, we can add methods to search for books by author without changing the existing methods.

#### What does it do badly?

- **Liskov Substitution Principle (LSP)**: Since there are no subclasses in this simple example, this principle is not applicable. However, if we were to extend this system with subclasses of `Book`, we would need to ensure they could be used interchangeably without breaking the program.
- **Interface Segregation Principle (ISP)**: This principle is not directly applicable to this simple example, as there are no interfaces that force the `Library` class to implement methods it doesn't use. However, creating interfaces for different types of library interactions could be beneficial when the system is getting more complex.
- **Dependency Inversion Principle (DIP)**: The program does not demonstrate this principle. The `Library` class is directly dependent on the concrete `Book` class. If we wanted to manage different types of library items (e.g., magazines, DVDs), the current design would require significant changes to the `Library` class.

#### Suggested Improvements

- **Refactor to Improve DIP**: Introduce an `ILibraryItem` interface (or abstract class) that `Book` implements. This way, the `Library` class can manage a collection of `ILibraryItem` objects, making it more flexible and open to extension with different types of library items.
- **Implement ISP**: As the system expands, consider defining interfaces for different interactions with library items (e.g., `IManageable`, `IDisplayable`). This would ensure that classes only need to implement the functionalities they require.
- **Extend with LSP in Mind**: When adding new subclasses for `Book` or other `ILibraryItem` implementations, ensure they can be used interchangeably within the `Library` without altering the expected behavior.