//
//  main.cpp
//  DSA mini Text editor project
//
//  Created by Mohamed Elsamadony on 2025-12-12.
//
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Line {
    string text ;
    Line* nextLine ;
    Line* previousLine;
    
    Line(string val) : text(val) , nextLine(nullptr) , previousLine(nullptr) {};
};
    
    
    class TextEditor {
        private :
        Line* Start;
        Line* End ;
        int numberOfLines ;
        
        public :
        TextEditor() : numberOfLines(0) , Start(nullptr) ,End(nullptr) {} ;
        
        ~TextEditor() {
            Line* temp = Start ;
            while ( temp != nullptr) {
                Line* delptr = temp ;
                delete delptr ;
                temp = temp->nextLine ;
            }
            Start = nullptr ;
            End = nullptr ;
        }
        
        Line* getStart() {
            return Start ;
        }
        Line* getEnd() {
            return End ;
        }
        int getNumberofLines() {
            return numberOfLines ;
        }
        void setStart(Line* firstLine) {
            Start = firstLine ;
        }
        void setEnd(Line* lastLine) {
            End = lastLine ;
        }
        void setNumberOfLines(int NewNumberOfLines){
            numberOfLines = NewNumberOfLines ;
        }
        bool isEmpty(){
            return (Start == nullptr) ;
        }
        void addLine(string newLineText) {
            Line* newline = new Line(newLineText) ;
            if(isEmpty()) {
                Start = newline ;
                End = newline ;
                numberOfLines++ ;
            }else {
                End->nextLine = newline ;
                newline->previousLine = End ;
                End = newline ;
                numberOfLines++ ;
            }
        }
        void insertLine(string newLineText , int placeOfInsertion) {
            Line* newline = new Line(newLineText) ;
            if(isEmpty()) {
                cout<<"sorry but line"<<placeOfInsertion<<"is not found , there are 0 lines"<<endl;
            }else if(placeOfInsertion > numberOfLines+1) {
                cout<<"sorry but the line "<<placeOfInsertion<<" is out of scope the file contains : "<<numberOfLines<<" lines "<<endl;
            }else if (numberOfLines == 1 ){
                newline->nextLine =Start ;
                Start->previousLine = newline ;
                Start = newline ;
                numberOfLines++;
            }else if (placeOfInsertion == numberOfLines+1){
                End->nextLine = newline ;
                newline->previousLine = End ;
                End = newline ;
            }else{
                if(placeOfInsertion < numberOfLines/2){
                    Line* temp = Start ;
                    int counter = 0 ;
                    while (counter != placeOfInsertion-1) {
                        counter++;
                        temp =temp->nextLine ;
                    }
                    newline->nextLine = temp->nextLine ;
                    temp->nextLine->previousLine = newline ;
                    temp->nextLine = newline ;
                    newline->previousLine = temp ;
                    numberOfLines++ ;
                }else {
                    Line* temp = End ;
                    int counter = numberOfLines ;
                    while (counter != placeOfInsertion-1) {
                        counter-- ;
                        temp =temp->previousLine ;
                    }
                    newline->nextLine = temp->nextLine ;
                    temp->nextLine->previousLine = newline ;
                    temp->nextLine = newline ;
                    newline->previousLine = temp ;
                    numberOfLines++ ;
                }
            }
        }
        string GetLine(int lineNumber){
            if(isEmpty()){
                cout<<"sorry , you can't fetch this line , the file is empty"<<endl ;
            }else if ( lineNumber > numberOfLines || lineNumber < 0 ){
                cout<<"sorry this line is out of scope "<<endl ;
            }else {
                if(lineNumber < numberOfLines/2){
                    Line* temp = Start ;
                    int counter = 0 ;
                    while (counter != lineNumber) {
                        counter++;
                        temp =temp->nextLine ;
                    }
                    return temp->text ;
                }else {
                    Line* temp = End ;
                    int counter = numberOfLines ;
                    while (counter != lineNumber) {
                        counter-- ;
                        temp =temp->previousLine ;
                    }
                    return temp->text ;
                }}
            return "NAN" ;
        }
        void DeleteLine(int lineNumber){
            if(isEmpty()){
                cout<<"nothing to delete the file is empty "<<endl ;
            }else if (lineNumber > numberOfLines || lineNumber < 0 ){
                cout<<"sorry, but this line is out of scope"<<endl;
            }else  if(numberOfLines == 1){
                Line* delptr = Start ;
                cout<<"the line of number 1 has been successfully deleted"<<endl ;
                Start = nullptr ;
                End = nullptr ;
                delete delptr ;
                numberOfLines = 0 ;
            }else if(lineNumber == numberOfLines){
                Line * delptr = End ;
                End = End->previousLine ;
                End->nextLine = nullptr ;
                delete delptr ;
                cout<<"the last line of number : "<<numberOfLines<<" has been deleted successfully."<<endl;
                numberOfLines-- ;
            }else if (lineNumber == 1 ) {
                Line*delptr = Start ;
                Start = Start->nextLine;
                delete delptr ;
                cout<<"the line of number 1 has been successfully deleted"<<endl;
            }else{
                if(lineNumber < numberOfLines/2){
                    Line* temp = Start ;
                    int counter = 0 ;
                    while (counter != lineNumber) {
                        counter++;
                        temp =temp->nextLine ;
                    }
                    Line* delptr = temp ;
                    delptr->nextLine->previousLine = delptr->previousLine ;
                    delptr->previousLine->nextLine = delptr->nextLine ;
                    cout<<"the line of number : "<<lineNumber<<" has been succesfully deleted "<<endl ;
                    delete delptr ;
                    numberOfLines-- ;
                }else {
                    Line* temp = End ;
                    int counter = numberOfLines ;
                    while (counter != lineNumber) {
                        counter-- ;
                        temp =temp->previousLine ;
                    }
                    Line* delptr = temp ;
                    delptr->nextLine->previousLine = delptr->previousLine ;
                    delptr->previousLine->nextLine = delptr->nextLine ;
                    cout<<"the line of number : "<<lineNumber<<" has been succesfully deleted "<<endl ;
                    delete delptr ;
                    numberOfLines-- ;
                }}
        }
        void UpdateLine(string updatedText  , int lineNumber) {
            if (isEmpty()) {
                cout<<"sorry , you can't update this line , the file is empty "<<endl;
            }else if (lineNumber > numberOfLines || lineNumber < 0 ) {
                cout<<"sorry , but this line is out of scope "<<endl ;
            }else {
                if(lineNumber < numberOfLines/2){
                    Line* temp = Start ;
                    int counter = 0 ;
                    while (counter != lineNumber) {
                        counter++;
                        temp =temp->nextLine ;
                    }
                    temp->text = updatedText ;
                }else {
                    Line* temp = End ;
                    int counter = numberOfLines ;
                    while (counter != lineNumber) {
                        counter-- ;
                        temp =temp->previousLine ;
                    }
                    temp->text = updatedText ;
                }
            }
        }
        void findAll(string wordToBeFound){
            Line* temp = Start ;
            int counter = 1 ;
            vector<int> nbOfLinesTheWordIsFoundIn ;
            while ( temp != nullptr ){
                if(temp->text.find(wordToBeFound) != string::npos){
                    nbOfLinesTheWordIsFoundIn.push_back(counter);
                }
                temp = temp->nextLine ;
                counter++ ;
            }
            if(nbOfLinesTheWordIsFoundIn.size() == 0){
                cout<<"sorry but this word is not found anywhere in the file"<<endl;
            }else{
                cout<<"the lines that the word is present in is : ";
                for(size_t i = 0 ;nbOfLinesTheWordIsFoundIn.size() > i ; i++ ){
                    cout<<nbOfLinesTheWordIsFoundIn[i]<<" " ;
                }
                cout<<endl;
            }
        }
//        int isFoundInTheString(string word , size_t startingIndex, string searchedText){
//            if(searchedText.find(word) != string::npos){
//            return isFoundInTheString(word,searchedText.find(word) , searchedText);
//            }else {
//                return -1 ;
//            }
//        }
        void findAllAndReplace(string newWord ,string WordToBeReplaced) {
            Line* temp = Start ;
            size_t newWordSize = newWord.size() ;
            size_t wordSize = WordToBeReplaced.size() ;
            for(int i = 0 ;  i < numberOfLines ; i++) {
                size_t newIndex = 0;
                while(true){
                    size_t foundPosition = temp->text.find(WordToBeReplaced, newIndex) ;
                    if ( foundPosition != string::npos ){
                        newIndex = temp->text.find(WordToBeReplaced , newIndex) + newWordSize;
                        temp->text.replace(newIndex- newWordSize, wordSize, newWord);
                    }else {
                        break ;
                    }
                }
                temp = temp->nextLine ;
            }
        }
        void Display(){
            Line* temp = Start ;
            int counter = 1 ;
            while(temp != nullptr){
                cout<<counter<<" "<<temp->text<<endl;
                counter++ ;
                temp = temp->nextLine ;
            }
        }
    };


    




int main(int argc, const char * argv[]) {
    // insert code here...
    TextEditor file ;
    file.addLine("heeeeey this is mohamed ");
    file.Display();
    return 0;
}
