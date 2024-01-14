#include <iostream>
#include <regex>

using namespace std;

void decryptMessage(string msg) {
    string bins[] = {"01100001", "01100010", "01100011", "01100100", "01100101", "01100110",
                     "01100111", "01101000", "01101001", "01101010", "01101011", "01101100",
                     "01101101", "01101110", "01101111", "01110000", "01110001", "01110010",
                     "01110011", "01110100", "01110101", "01110110", "01110111", "01111000",
                     "01111001", "01111010", "00000000", "00100000"},
            chars[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
                         "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
                         "u", "v", "w", "x", "y", "z", " ", "   "},
            decriptedMessage;

    regex re1("(^\\d{6})(\\d)(0)(.*)"), re2("(^\\d{6})(\\d)(1)(.*)"), re3("(^\\d{4})(\\d{4})(.*)");

    msg = regex_replace(msg, regex("\\s"), "");

    while (!msg.empty()) {
        string tempChar;

        if(regex_match(msg, re1))
            tempChar = regex_replace(msg, re1, "$1$021");
        else
            tempChar = regex_replace(msg, re2, "$1$020");

        tempChar = regex_replace(tempChar, re3, "$2$1");

        for(int i = 0; i < (sizeof(bins) / sizeof(string)); i++) {
            if(regex_match(tempChar, regex(bins[i]))) {
                tempChar = regex_replace(tempChar, regex(bins[i]), chars[i]);
                break;
            }
        }

        decriptedMessage += tempChar;
        msg = regex_replace(msg, re3, "$3");
    }

    cout << decriptedMessage << endl;
}

int main() {
    string encryptedMessage = "10010110 11110111 01010110 00000001 00010111 00100110 01010111 00000001 00010111 01110110 01010111 00110110 11110111 11010111 01010111 00000011";

    decryptMessage(encryptedMessage);
}
