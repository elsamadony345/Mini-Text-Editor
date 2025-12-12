//
//  main.cpp
//  DSA mini Text editor project
//
//  Created by Mohamed Elsamadony on 2025-12-12.
//
#include <string>
#include <iostream>
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
            }
        }
        void insertLine(string newLineText , int placeOfInsertion) {
            Line* newline = new Line(newLineText) ;
            if(isEmpty()) {
                cout<<"sorry but line"<<placeOfInsertion<<"is not found , there are 0 lines"<<endl;
            }else if(placeOfInsertion > numberOfLines+1) {
                cout<<"sorry but the line "<<placeOfInsertion<<" is out of scope the file contains : "<<numberOfLines<<" lines "<<endl;
            }else if (numberOfLines == 1 ){
                Start = newline ;
                End = newline;
                numberOfLines = 1;
                }else{
                if(placeOfInsertion < numberOfLines/2){
                    Line* temp = Start ;
                    int counter = 0 ;
                    while (counter != placeOfInsertion-1) {
                        counter++;
                        temp =temp->nextLine ;
                    }
                    numberOfLines++ ;
                    newline->nextLine = temp->nextLine ;
                    temp->nextLine->previousLine = newline ;
                    temp->nextLine = newline ;
                    newline->previousLine = temp ;
                }else {
                    Line* temp = End ;
                    int counter = numberOfLines ;
                    while (counter != placeOfInsertion-1) {
                        counter-- ;
                        temp =temp->previousLine ;
                    }
                    numberOfLines++ ;
                    newline->nextLine = temp->nextLine ;
                    temp->nextLine->previousLine = newline ;
                    temp->nextLine = newline ;
                    newline->previousLine = temp ;
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
    };


    




int main(int argc, const char * argv[]) {
    // insert code here...
    
    return 0;
}
