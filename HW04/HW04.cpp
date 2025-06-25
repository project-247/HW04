#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// Book 클래스 (책 기본 정보)
class Book {
public:
	string title;
	string author;

	Book(const string& title, const string& author)
		: title(title), author(author) {
	}
};

// BookManager 클래스 (책 추가 및 검색 담당)
class BookManager {
private:
	vector<Book> books;

public:
	void addBook(const string& title, const string& author) {
		books.push_back(Book(title, author));
		cout << "책이 추가되었습니다: " << title << " by " << author << endl;
	}

	void displayAllBooks() const {
		if (books.empty()) {
			cout << "현재 등록된 책이 없습니다." << endl;
			return;
		}
		cout << "=== 도서 목록 ===" << endl;
		for (const auto& book : books) {
			cout << "- " << book.title << " by " << book.author << endl;
		}
	}

	Book* findBookByTitle(const string& title) {
		for (auto& book : books) {
			if (book.title == title)
				return &book;
		}
		return nullptr;
	}

	Book* findBookByAuthor(const string& author) {
		for (auto& book : books) {
			if (book.author == author)
				return &book;
		}
		return nullptr;
	}
};

// BorrowManager 클래스 (대여 시스템 담당)
class BorrowManager {
private:
	unordered_map<string, int> stock;  // 책 제목 → 재고 수량

public:
	void initializeStock(const Book& book, int quantity = 3) {
		stock[book.title] = quantity;
	}

	void borrowBook(const string& title) {
		if (stock.find(title) == stock.end()) {
			cout << "해당 도서는 존재하지 않습니다." << endl;
			return;
		}
		if (stock[title] == 0) {
			cout << "대여 불가: 재고가 없습니다." << endl;
			return;
		}
		stock[title]--;
		cout << "도서를 대여했습니다: " << title << endl;
	}

	void returnBook(const string& title) {
		if (stock.find(title) == stock.end()) {
			cout << "해당 도서는 존재하지 않습니다." << endl;
			return;
		}
		stock[title]++;
		cout << "도서를 반납했습니다: " << title << endl;
	}

	void displayStock() const {
		cout << "=== 도서 재고 현황 ===" << endl;
		for (const auto& pair : stock) {
			cout << pair.first << " - 재고: " << pair.second << endl;
		}
	}
};

// 메인 프로그램
int main() {
	BookManager bookManager;
	BorrowManager borrowManager;

	while (true) {
		cout << "\n도서관 관리 프로그램" << endl;
		cout << "1. 책 추가" << endl;
		cout << "2. 전체 책 목록 보기" << endl;
		cout << "3. 책 제목 검색" << endl;
		cout << "4. 저자명 검색" << endl;
		cout << "5. 책 대여" << endl;
		cout << "6. 책 반납" << endl;
		cout << "7. 재고 보기" << endl;
		cout << "8. 종료" << endl;
		cout << "선택: ";

		int choice;
		cin >> choice;
		cin.ignore(); // 버퍼 정리

		if (choice == 1) {
			string title, author;
			cout << "책 제목: ";
			getline(cin, title);
			cout << "저자: ";
			getline(cin, author);
			bookManager.addBook(title, author);
			borrowManager.initializeStock(Book(title, author));
		}
		else if (choice == 2) {
			bookManager.displayAllBooks();
		}
		else if (choice == 3) {
			string title;
			cout << "검색할 책 제목: ";
			getline(cin, title);
			Book* book = bookManager.findBookByTitle(title);
			if (book)
				cout << "검색 결과: " << book->title << " by " << book->author << endl;
			else
				cout << "해당 제목의 책을 찾을 수 없습니다." << endl;
		}
		else if (choice == 4) {
			string author;
			cout << "검색할 저자명: ";
			getline(cin, author);
			Book* book = bookManager.findBookByAuthor(author);
			if (book)
				cout << "검색 결과: " << book->title << " by " << book->author << endl;
			else
				cout << "해당 저자의 책을 찾을 수 없습니다." << endl;
		}
		else if (choice == 5) {
			string title;
			cout << "대여할 책 제목: ";
			getline(cin, title);
			borrowManager.borrowBook(title);
		}
		else if (choice == 6) {
			string title;
			cout << "반납할 책 제목: ";
			getline(cin, title);
			borrowManager.returnBook(title);
		}
		else if (choice == 7) {
			borrowManager.displayStock();
		}
		else if (choice == 8) {
			cout << "프로그램 종료" << endl;
			break;
		}
		else {
			cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
		}
	}

	return 0;
}
