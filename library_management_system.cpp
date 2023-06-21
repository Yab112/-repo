#include <iostream>
#include <string>
using namespace std;

// Book record structure
struct Book {
    string title;
    string author;
    int year;
    string isbn;
    // Doubly linked list pointers
    Book* prev;
    Book* next;
};

// Doubly linked list class
class BookList {
public:
    // Constructor
    BookList() {
        head = nullptr;
        tail = nullptr;
    }
    // Destructor
    ~BookList() {
        // Delete all nodes
        Book* current = head;
        while (current != nullptr) {
            Book* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
    // Add a book record to the list
    void add(Book* book) {
        book->prev = nullptr;
        book->next = nullptr;
        if (head == nullptr) {
            head = book;
            tail = book;
        } else {
            tail->next = book;
            book->prev = tail;
            tail = book;
        }
    }
    // Display all book records in the list
    void display() {
        cout << "Book List:" << endl;
        Book* current = head;
        while (current != nullptr) {
            cout << "Title: " << current->title << endl;
            cout << "Author: " << current->author << endl;
            cout << "Year: " << current->year << endl;
            cout << "ISBN: " << current->isbn << endl;
            cout << endl;
            current = current->next;
        }
    }
    // Search for a book record by title or ISBN
    Book* search(string keyword) {
        Book* current = head;
        while (current != nullptr) {
            if (current->title == keyword || current->isbn == keyword) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    // Edit a book record by title or ISBN
    void edit(string keyword) {
        Book* book = search(keyword);
        if (book != nullptr) {
            cout << "Enter new author: ";
            getline(cin, book->author);
            cout << "Enter new year: ";
            cin >> book->year;
            cin.ignore();
            cout << "Book record updated." << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }
    // Delete a book record by title or ISBN
    void remove(string keyword) {
        Book* book = search(keyword);
        if (book != nullptr) {
            if (book == head) {
                head = book->next;
            }
            if (book == tail) {
                tail = book->prev;
            }
            if (book->prev != nullptr) {
                book->prev->next = book->next;
            }
            if (book->next != nullptr) {
                book->next->prev = book->prev;
            }
            delete book;
            cout << "Book record deleted." << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }
private:
    Book* head;
    Book* tail;
};

int main() {
    // Initialize book list
    BookList books;
    // Command menu loop
    while (true) {
        cout << "Library Management System" << endl;
        cout << "1. Add a book record" << endl;
        cout << "2. Display book information" << endl;
        cout << "3. Search for a book" << endl;
        cout << "4. Edit book information" << endl;
        cout << "5. Delete a book" << endl;
        cout << "6. Exit" << endl;
        int choice;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: {
            Book* book = new Book;
            cout << "Enter title: ";
            getline(cin, book->title);
            cout << "Enter author: ";
            getline(cin, book->author);
            cout << "Enter year: ";
            cin >> book->year;
            cin.ignore();
            cout << "Enter ISBN: ";
            getline(cin, book->isbn);
            books.add(book);
            cout << "Book record added." << endl;
            break;
        }
        case 2: {
            books.display();
            break;
        }
        case 3: {
            cout << "Enter title or ISBN: ";
            string keyword;
            getline(cin, keyword);
            Book* book = books.search(keyword);
            if (book != nullptr) {
                cout << "Book found:" << endl;
                cout << "Title: " << book->title << endl;
                cout << "Author: " << book->author << endl;
                cout << "Year: " << book->year << endl;
                cout << "ISBN: " << book->isbn << endl;
            } else {
                cout << "Book not found." << endl;
            }
            break;
        }
        case 4: {
            cout << "Enter title or ISBN: ";
            string keyword;
            getline(cin, keyword);
            books.edit(keyword);
            break;
        }
        case 5: {
            cout << "Enter title or ISBN: ";
            string keyword;
            getline(cin, keyword);
            books.remove(keyword);
            break;
        }
        case 6: {
            cout << "Exiting program." << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }
    return 0;
}
