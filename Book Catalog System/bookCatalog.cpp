#include <bits/stdc++.h>
using namespace std;

enum Category{FICTION,NONFICTION,MYSTERY,MYTHOLOGY};
class Book{
    private:
    string name;
    string author;
    string publisher;
    int publishYear;
    double price;
    int count;
    Category category;
    
     // Getters for properties
     public:
   Book(string name, string author, string publisher, int publishYear, double price, int count, Category category) {
    this->name = name;
    this->author = author;
    this->publisher = publisher;
    this->publishYear = publishYear;
    this->price = price;
    this->count = count;
    this->category = category;
}
    string getName() const {
        return name;
    }

    string getAuthor() const {
        return author;
    }

    string getPublisher() const {
        return publisher;
    }

    int getPublishYear() const {
        return publishYear;
    }

    double getPrice() const {
        return price;
    }

    int getCount() const {
        return count;
    }

    Category getCategory() const {
        return category;
    }
};

class catalog{
    list<Book>catalog;
                    // count , book
   typedef priority_queue<pair<int,Book*>> countQueue; // max-heap
   
   unordered_map<string,countQueue>authorMap;
   unordered_map<Category,countQueue>categoryMap;
  public:
  void createBook(Book& book){
      catalog.push_back(book);
      authorMap[book.getAuthor()].push({book.getCount(),&catalog.back()});
      categoryMap[book.getCategory()].push({book.getCount(),&catalog.back()});
      
  }
    vector<Book>searchByAuthor(string prefix){
           vector<Book>ans;
           
           for(auto it:catalog){
               auto name=it.getName();
               if(name.substr(0,prefix.size())==prefix){
                   ans.push_back(it);
               }
           }
           return ans;
      }
    vector<Book>searchByAuthorName(string name){
            vector<Book>ans;
           
           for(auto it:catalog){
              auto authorName=it.getAuthor();
               if(authorName==name){
                   ans.push_back(it);
               }
           }
           return ans;
      }
       
    vector<Book> mostSoldBooksByAuthor(string author, int size) {
    vector<Book> ans;
    auto &q = authorMap[author];  // Use a reference to the priority_queue

    while (!q.empty() && size > 0) {
        ans.push_back(*(q.top().second));  // Access the second element using ->
        q.pop();
        size--;
    }

    return ans;
}
    vector<Book>mostSoldBooksByCatgory(Category category,int size){
            vector<Book> ans;
    auto &q = categoryMap[category];  // Use a reference to the priority_queue

    while (!q.empty() && size > 0) {
        ans.push_back(*(q.top().second));  // Access the second element using ->
        q.pop();
        size--;
    }

    return ans;
      }
       
};

int main() {
    catalog library;
    
     cout << "*************** Book Catalog ***************" << endl << endl;
    // Test createBook
    Book book1("The Great Gatsby", "F. Scott Fitzgerald", "Scribner", 1925, 10.99, 50, FICTION);
    library.createBook(book1);

    Book book2("To Kill a Mockingbird", "Harper Lee", "J. B. Lippincott & Co.", 1960, 12.49, 40, FICTION);
    library.createBook(book2);

    Book book3("1984", "George Orwell", "Secker & Warburg", 1949, 9.99, 60, FICTION);
    library.createBook(book3);

    Book book4("Sapiens: A Brief History of Humankind", "Yuval Noah Harari", "Harper", 2011, 15.79, 30, NONFICTION);
    library.createBook(book4);

    Book book5("Atomic Habits", "James Clear", "Avery", 2018, 14.99, 45, NONFICTION);
    library.createBook(book5);

    Book book6("The Da Vinci Code", "Dan Brown", "Doubleday", 2003, 11.25, 20, MYSTERY);
    library.createBook(book6);

    Book book7("Murder on the Orient Express", "Agatha Christie", "Collins Crime Club", 1934, 8.99, 35, MYSTERY);
    library.createBook(book7);

    Book book8("Norse Mythology", "Neil Gaiman", "W. W. Norton & Company", 2017, 9.49, 25, MYTHOLOGY);
    library.createBook(book8);

    Book book9("The Hero with a Thousand Faces", "Joseph Campbell", "Pantheon Books", 1949, 12.99, 15, MYTHOLOGY);
    library.createBook(book9);

    Book book10("Educated", "Tara Westover", "Random House", 2018, 13.95, 18, NONFICTION);
    library.createBook(book10);

    /* Test searchByAuthor */
    vector<Book> authorBooks = library.searchByAuthor("F. Scott");
    cout << "Books by F. Scott Fitzgerald:" << endl;
    for (const Book &book : authorBooks) {
        cout << book.getName() << endl;
    }

    /* Test searchByAuthorName */
    vector<Book> authorNameBooks = library.searchByAuthorName("Neil Gaiman");
    cout << "Books by Neil Gaiman (exact match):" << endl;
    for (const Book &book : authorNameBooks) {
        cout << book.getName() << endl;
    }

    /* Test mostSoldBooksByAuthor */
    vector<Book> mostSoldByAuthor = library.mostSoldBooksByAuthor("George Orwell", 3);
    cout << "Most sold books by George Orwell:" << endl;
    for (const Book &book : mostSoldByAuthor) {
        cout << book.getName() << endl;
    }

    /* Test mostSoldBooksByCategory */
    vector<Book> mostSoldByCategory = library.mostSoldBooksByCatgory(FICTION, 2);
    cout << "Most sold Fiction books:" << endl;
    for (const Book &book : mostSoldByCategory) {
        cout << book.getName() << endl;
    }

    return 0;
}
