#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

//MY CUSTOM BUILT IN FUNCTIONS 
int len(char* arr) {
	int i = 0;
	while (arr[i] != '\0') {
		i++;
	}
	return i;
}


void copy(char arr1[], char arr2[]) {
	if (len(arr1) > len(arr2)) {
		for (int i = 0; i < len(arr1); i++) {
			arr1[i] = arr2[i];
		}
	}
	else {
		for (int i = 0; i < len(arr2); i++) {
			arr1[i] = arr2[i];
		}
	}
}


bool check(char* arr1, char* arr2) {
	if (len(arr1)!=len(arr2)){
		return false;
	}
	for (int i = 0; i < len(arr1); i++){
		if (arr1[i] != arr2[i]) {
			return false;
		}

	}
	return true;
}

////////////////////////////////////////////////////////////////
class Book {
public:
	char publicationID[10];
	char bookName[30];
	char author[30];
	char** patronSubscribers;

	Book() {
		patronSubscribers = new char* [5];
		for (int  i = 0; i < 5; i++){
			patronSubscribers[i] = new char[30];
		}
	}

	~Book() {
		for (int i = 0; i < 5; i++){
			delete[]patronSubscribers[i];
		}
		delete[]patronSubscribers;
	}
};


int main() {
	Book books[10] = {};

	char temp[50];
	ifstream fin("books.txt");
		fin.getline(temp, 50);
		int noOfBooks = 0;
		while (noOfBooks<10 && fin >> books[noOfBooks].publicationID) {
			fin >> books[noOfBooks].bookName >> books[noOfBooks].author;
			for (int i = 0; i < 5; i++){
				fin >> books[noOfBooks].patronSubscribers[i];
			}
			noOfBooks++;
		}
		             
		//MENU
		int select = 1;
		while (select<=5&&select>=1){
			cout << "1.Add new book\n2.Update book details\n3.Delete Book\n4.Display all Books\n5.Exit\n";
			cout << "Enter your choice : ";
			cin >> select;

			if (select == 1) {
				ofstream fout("books.txt", ios::app);
				cout << "Enter new book details \n";
				cout << "Book ID: ";
				bool found = false;
				cin >> books[noOfBooks].publicationID;
				for (int i = 0; i < noOfBooks; i++){
					if (check(books[noOfBooks].publicationID,books[i].publicationID)){
						cout << "SAME BOOK ID THIS BOOK ALREADY EXISTS AGAIN ENTER THE CORRCT BOOK ID !" << endl;
						found = true;
						break;
					}
				}
				if (!found){
					cout << "Book name: ";
					cin >> books[noOfBooks].bookName;
					cout << "Author: ";
					cin >> books[noOfBooks].author;
					cout << "Enter the 5 patron Subsribers : \n";
					for (int i = 0; i <5; i++){
						cout << "Enter Subscriber " << i + 1 << ":\n";
						cin >> books[noOfBooks].patronSubscribers[i];
					}
					fout << books[noOfBooks].publicationID << " ";
					fout << books[noOfBooks].bookName << " ";
					fout << books[noOfBooks].author << " ";
					for (int  i = 0; i < 5; i++){
						fout << books[noOfBooks].patronSubscribers[i] << " ";
					}
					fout << endl;
					noOfBooks++;
				}
			}

			//UPDATE BOOK
			else if (select == 2) {
				int cho = 0;
				char bookIdChecking[5] = { '\0' };
				cout << "Enter book id of which details you want to update : ";
				cin >> bookIdChecking;
				for (int i = 0; i < noOfBooks; i++){
					if (check(bookIdChecking,books[i].publicationID)){
						cout << "1. Book Name\n2. Book Author\n3. Patron Subscribers\n";
						cin >> cho;
						if (cho==1){
							cout << "Enter new Book name : ";
							cin >> books[i].bookName;
						}
						else if (cho==2) {
							cout << "Enter new Book name : ";
							cin >> books[i].author;
						}
						else if (cho == 3) {
							cout << "Enter 5 new patrons subscribers : ";
							for (int j = 0; j < 5; j++){
								cin >> books[j].patronSubscribers[j];
							}

						}
						break;
					}
				}
			}
			 
			//DELETE BOOK
			else if (select==3) {
				char checkid[3] = { '\0' };
				cout << "Enter the book id which you want to delete : ";
				cin >> checkid;
				int delIndex = 1;
				for (int i = 0; i < noOfBooks; i++){
					if (check(checkid,books[i].publicationID)){
						delIndex = i;
						break;
					}
				}
				if (delIndex!=1){
					for (int i = delIndex; i < noOfBooks-1; i++){
						copy(books[i].publicationID, books[i + 1].publicationID);
						copy(books[i].bookName, books[i + 1].bookName);
						copy(books[i].author, books[i + 1].author);

						for (int j = 0; j < 5; j++){
							copy(books[i].patronSubscribers[i], books[i + 1].patronSubscribers[j]);
						}
					}
					char temp[] = { '\0' };
					copy(books[noOfBooks - 1].publicationID, temp);
					copy(books[noOfBooks - 1].bookName, temp);
					copy(books[noOfBooks - 1].author, temp);
					for (int j = 0; j < 5; j++){
						copy(books[noOfBooks - 1].patronSubscribers[j], temp);
					}
					noOfBooks--;
				}
				else{
					cout << "Bookk with ID " << checkid << "not found. " << endl;
				}
			}

			//DISPLAY ALL BOOKS
			else if (select==4){
				for (int i = 0; i < noOfBooks; i++){
					cout << "BOOKID\tBOOKNAME\tBOOKAUTHOR\n";
					cout << books[i].publicationID << "\t" << books[i].bookName << "\t\t" << books[i].author << "\t\t\n";
					for (int j = 0; j < 5; j++){
						cout <<"Subscriber "<<j+1<<": "<< books[i].patronSubscribers[j] << " \n";
					}
					cout << endl;
				}
			}

			//PROGRAM ENDING
			else if (select == 5) {
			cout << "THATS ALL PROGRAM ENDED !";
			break;
             }

			else{
			cout << "Wrong Input enter valid input !";
             }
		}
}