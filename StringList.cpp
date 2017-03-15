/**
 * author: Vahid Mavaji
 * year: 2001
 */

#include<iostream>
#include<string.h>
#include<stdlib.h>

class StringNode {
private:
    char string[80];
    StringNode *next = 0;
public:
    StringNode();

    StringNode *&getNext() { return next; }

    void setNext(StringNode *&p) { next = p; }

    char *getString();

    void setString(char str[80]);

    void appendString(char str[80]);
};

StringNode::StringNode() {
    next = 0;
    string[0] = 0;
}

char *StringNode::getString() {
    return string;
}

void StringNode::setString(char str[80]) {
    strcpy(string, str);
}

void StringNode::appendString(char str[80]) {
    strcat(string, str);
}

class StringList {
private:
    StringNode *first;
public:
    StringList();

    StringNode *GetFirst() { return first; }

    void insert(int line, char string[80]);

    void append(int line, char string[80]);

    void del(int beginLine, int endLine);

    void list(int beginLine, int endLine);
};

StringList::StringList() {
    first = 0;
//    first->setNext(0);
}

void StringList::insert(int line, char string[80]) {
    StringNode *pointer, *newNode;
    int i;

    newNode = new StringNode;
    if ((first == 0 && line > 1) || line < 1) {
        std::cout << "The Line Does Not Exist!" << std::endl;
        return;
    }

    if (first == 0 && line == 1) first = newNode;
    else if (line == 1) {
        newNode->setNext(first);
        first = newNode;
    } else {
        pointer = first;
        for (i = 1; i < line - 1; i++) {
            pointer = pointer->getNext();
            if (pointer == 0) {
                std::cout << "The Line Does Not Exist!" << std::endl;
                return;
            }
        }
        newNode->setNext(pointer->getNext());
        pointer->setNext(newNode);
    }
    newNode->setString(string);
}

void StringList::append(int line, char string[80]) {
    if (line < 1) {
        std::cout << "The Line Does Not Exist!" << std::endl;
        return;
    }
    if (first == 0) {
        std::cout << "List is Empty!" << std::endl;
        return;
    }
    StringNode *stringNode;
    int i;

    stringNode = first;
    for (i = 1; i < line; i++) {
        stringNode = stringNode->getNext();
        if (stringNode == 0) {
            std::cout << "The Line Does Not Exist!" << std::endl;
            return;
        }
    }
    stringNode->appendString(string);
}

void StringList::del(int beginLine, int endLine) {
    if (beginLine < 1) {
        std::cout << "The Line Does Not Exist!" << std::endl;
        return;
    }

    StringNode *beginPointer, *endPointer, *temp;
    int i;

    beginPointer = first;
    if (first == 0) {
        std::cout << "List is Empty!" << std::endl;
        return;
    }
    if (beginLine == 1 && first != 0) {
        first = first->getNext();
        return;
    }
    if (first->getNext() == 0 && beginLine == 2) {
        std::cout << "Begin Line Does Not Exist!" << std::endl;
        return;
    }

    for (i = 1; i < beginLine - 1; i++) {
        beginPointer = beginPointer->getNext();
        if (beginPointer->getNext() == 0 && i < beginLine) {
            std::cout << "Begin Line Does Not Exist!" << std::endl;
            return;
        }
    }
    endPointer = beginPointer->getNext();
    for (i = beginLine; i <= endLine; i++) {
        temp = endPointer;
        endPointer = endPointer->getNext();
        delete temp;
        if (endPointer == 0 && i < endLine) {
            std::cout << "End Line is Out of Range!" << std::endl;
            break;
        }
    }
    beginPointer->setNext(endPointer);
}

void StringList::list(int begin_line, int end_line) {
    StringNode *stringNode;
    int i;

    if (first == 0) {
        std::cout << "List is Empty!" << std::endl;
        return;
    }
    stringNode = first;
    for (i = 1; i < begin_line; i++) {
        stringNode = stringNode->getNext();
        if (stringNode == 0) {
            std::cout << "Begin Line Does Not Exist!" << std::endl;
            return;
        }
    }
    for (i = begin_line; i <= end_line; i++) {
        std::cout << stringNode->getString() << std::endl;
        stringNode = stringNode->getNext();
        if (stringNode == 0 && i < end_line) {
            std::cout << "End Line is Out of Range!" << std::endl;
            return;
        }
    }
}

char underLine[75];

int getValue(char command[80], int *index) {
    char s[5];
    int line, len;

    s[0] = '\0';
    while (command[(*index)] != ' ' && command[(*index)] != 0) {
        len = (int) strlen(s);
        s[len] = command[(*index)];
        s[len + 1] = '\0';
        (*index)++;
    }
    line = atoi(s);
    return line;
}

char *getCommand(char command[80], int place) {
    char string1[80];

    int i;
    for (i = place; i <= strlen(command); i++) {
        string1[i - place] = command[i];
    }

    string1[i - place - 1] = '\0';

    char *result = (char *) malloc(strlen(string1));  // allocate memory from the heap
    strncpy(result, string1, strlen(string1));
    return (result);
}

void insert(char command[80], StringList &stringList) {
    int index;
    int line;
    char string[80];

    index = 2;
    line = getValue(command, &index);
    strcpy(string, getCommand(command, index + 1));
    stringList.insert(line, string);
}

void append(char command[80], StringList &stringList) {
    int index;
    int line;
    char string[80];

    index = 2;
    line = getValue(command, &index);
    strcpy(string, getCommand(command, index + 1));
    stringList.append(line, string);

}

void del(char command[80], StringList &stringList) {
    int index;
    int line1, line2;

    index = 2;
    line1 = getValue(command, &index);
    if (command[index] == 0) line2 = line1;
    else {
        index++;
        line2 = getValue(command, &index);
    }
    stringList.del(line1, line2);
}

void list(char command[80], StringList &stringList) {
    int index;
    int line1, line2;

    index = 2;
    line1 = getValue(command, &index);
    if (command[index] == 0) line2 = line1;
    else {
        index++;
        line2 = getValue(command, &index);
    }
    std::cout << underLine << std::endl;
    stringList.list(line1, line2);
    std::cout << underLine << std::endl;
}

void exit(StringList &stringList) {
    StringNode *stringNode;
    int i = 1;

    stringNode = stringList.GetFirst();

    std::cout << underLine << std::endl;
    while (1) {
        std::cout << stringNode->getString() << std::endl;
        stringNode = stringNode->getNext();
        i++;
        if (i == 24) std::cin.get();
        if (stringNode == 0) break;
    }
    std::cout << underLine << std::endl;
    std::cout << "Program Ended!";
}

int main() {
    for (int i = 0; i < 75; i++) underLine[i] = '-';

    StringList stringList;
    char command[80];
    char ch;

    while (1) {
        std::cout << "Command:~$";
        std::cin.getline(command, sizeof(command));
        ch = command[0];
        switch (ch) {
            case 'i':
            case 'I':
                insert(command, stringList);
                break;

            case 'a':
            case 'A':
                append(command, stringList);
                break;

            case 'd':
            case 'D':
                del(command, stringList);
                break;

            case 'l':
            case 'L':
                list(command, stringList);
                break;

            case 'e':
            case 'E':
                exit(stringList);
                return 0;

            default:
                std::cout << "Bad Command or File Name!" << std::endl;
        }
    }
}