#include <iostream>
#include <map>
#include <regex>

using namespace std;

struct offerBook {
    int position;
    double value;
    int quantity;
};
struct bookInput {
    int position;
    int action;
    double value;
    int quantity;
};
struct offerBooks {
    map<int, offerBook> books;
};

offerBooks updateBook(string input, offerBooks books) {
    regex getLength("(^\\d{1,})(\\n)(.*)"), splitProp("^(\\d{1,}),(\\d),(\\d{1,}.?\\d*),(\\d{1,})(\\n?)(.*)");
    input = regex_replace(input, getLength, "$3");

    while(!input.empty()) {
        bookInput bookTemp{};
        bookTemp.position = stoi(regex_replace(input, splitProp, "$1"));
        bookTemp.action = stoi(regex_replace(input, splitProp, "$2"));
        bookTemp.value = stod(regex_replace(input, splitProp, "$3"));
        bookTemp.quantity = stoi(regex_replace(input, splitProp, "$4"));

        input = regex_replace(input, splitProp, "$6");
        offerBook book{};
        if (bookTemp.action == 0 && bookTemp.value > 0 && bookTemp.quantity > 0) {
            book.position = bookTemp.position;
            book.value = bookTemp.value;
            book.quantity = bookTemp.quantity;
            books.books[bookTemp.position] = book;
        } else if(bookTemp.action == 1) {
            if(bookTemp.value > 0)
                books.books[bookTemp.position].value = bookTemp.value;
            if(bookTemp.quantity > 0)
                books.books[bookTemp.position].quantity = bookTemp.quantity;
        } else if(bookTemp.action == 2){
            books.books.erase(bookTemp.position);
        }
    }
    offerBooks newBooks{};
    int position = 0;
    map<int, offerBook>:: iterator it;
    for(it = books.books.begin(); it != books.books.end(); it++) {
        it->second.position = ++position;
        newBooks.books[it->second.position] = it->second;
        cout << it->second.position << "," << it->second.value << "," << it->second.quantity << endl;
    }

    return newBooks;
}

int main() {
    string input = "12\n"
                   "1,0,15.4,50\n"
                   "2,0,15.5,50\n"
                   "2,2,0,0\n"
                   "2,0,15.4,10\n"
                   "3,0,15.9,30\n"
                   "3,1,0,20\n"
                   "4,0,16.50,200\n"
                   "5,0,17.00,100\n"
                   "5,0,16.59,20\n"
                   "6,2,0,0\n"
                   "1,2,0,0\n"
                   "2,1,15.6,0";

    offerBooks books{};
    books = updateBook(input, books);

    return 0;
}
