
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// Book class stores information about each book
class Book {
public:
    string title, author, id;
    int pages;
    bool borrowed;

    Book(string t, string a, int p, string i, bool b)
        : title(t), author(a), pages(p), id(i), borrowed(b) {}

    void display() const {
        cout << "\nID: " << id
             << "\nTitle: " << title
             << "\nAuthor: " << author
             << "\nPages: " << pages
             << "\nStatus: "
             << (borrowed ? "Borrowed" : "Available")
             << "\n";
    }
};

// Read books from the text file
vector<Book> loadBooks(const string& filename) {
    vector<Book> books;
    ifstream file(filename);
    string line;

    if (!file) {
        cout << "Error: Cannot open " << filename << "\n";
        return books;
    }

    while (getline(file, line)) {
        string title, author, pages, id, status;
        stringstream ss(line);

        if (getline(ss, title, ',') &&
            getline(ss, author, ',') &&
            getline(ss, pages, ',') &&
            getline(ss, id, ',') &&
            getline(ss, status)) {
            try {
                books.emplace_back(title, author, stoi(pages),
                                   id, status == "true");
            }
            catch (...) {
                cout << "Skipping invalid book record.\n";
            }
        }
    }
    return books;
}

// Save updated book information
void saveBooks(const vector<Book>& books, const string& filename) {
    ofstream file(filename);

    if (!file) {
        cout << "Error: Could not save book data.\n";
        return;
    }

    for (const Book& book : books) {
        file << book.title << "," << book.author << ","
             << book.pages << "," << book.id << ","
             << (book.borrowed ? "true" : "false") << "\n";
    }
}

// Find a book using its ID
Book* findBook(vector<Book>& books, const string& id) {
    for (Book& book : books) {
        if (book.id == id)
            return &book;
    }
    return nullptr;
}

// Display all books
void viewAllBooks(const vector<Book>& books) {
    cout << "\n===== ALL BOOKS =====\n";
    for (const Book& book : books) {
        cout << book.id << " - " << book.title
             << " ("
             << (book.borrowed ? "Borrowed" : "Available")
             << ")\n";
    }
}

// Borrow or return a selected book
void updateBook(vector<Book>& books, bool borrow) {
    string id;
    cout << "Enter book ID: ";
    cin >> id;

    Book* book = findBook(books, id);

    if (book == nullptr) {
        cout << "Book not found.\n";
    }
    else if (book->borrowed == borrow) {
        cout << (borrow ? "Already borrowed.\n"
                        : "Book is not borrowed.\n");
    }
    else {
        book->borrowed = borrow;
        cout << (borrow ? "Book borrowed successfully.\n"
                        : "Book returned successfully.\n");
        saveBooks(books, "bookData.txt");
    }
}

int main() {
    const string filename = "bookData.txt";
    vector<Book> books = loadBooks(filename);

    if (books.empty()) {
        cout << "No books loaded. Program exiting.\n";
        return 1;
    }

    int choice;

    while (true) {
        cout << "\n===== BOOK MANAGER =====\n";
        cout << "1. View All Books\n";
        cout << "2. View Book Details\n";
        cout << "3. Borrow a Book\n";
        cout << "4. Return a Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number.\n";
            continue;
        }

        if (choice == 1) {
            viewAllBooks(books);
        }
        else if (choice == 2) {
            string id;
            cout << "Enter book ID: ";
            cin >> id;
            Book* book = findBook(books, id);
            if (book)
                book->display();
            else
                cout << "Book not found.\n";
        }
        else if (choice == 3) {
            updateBook(books, true);
        }
        else if (choice == 4) {
            updateBook(books, false);
        }
        else if (choice == 5) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid menu choice.\n";
        }
    }
    return 0;
}
