#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct String {
	char* data;
	size_t length;
	size_t capacity;
} String;

String* string_new();
void string_free(String* str);
String* string_from_char_ptr(char* char_ptr);
char* string_to_char_ptr(String* str);
bool string_push_back_char(String* str, char push_char);
bool string_push_back_str(String* str, char* push_str);
void string_reverse(String* str);
String* string_from_number(size_t n);

String* string_new() {
	String* str = (String*)malloc(sizeof(String));

	if (!str) {
		printf("ERROR: String allocation failed\n");
		exit(1);
	}

	str->capacity = 1;
	str->length = 0;
	str->data = malloc(str->capacity);

	if (!str->data) {
		printf("ERROR: String data allocation failed\n");
		exit(1);
	}

	str->data[0] = '\0';

	return str;
}

void string_free(String* str) {
	free(str->data);
	free(str);
}

String* string_from_char_ptr(char* char_ptr) {
	String* str = string_new();

	string_push_back_str(str, char_ptr);

	return str;
}

char* string_to_char_ptr(String* str) {
	return str->data;
}

bool string_push_back_char(String* str, char push_char) {
	if (str->length + 1 >= str->capacity) {
		size_t new_capacity = str->capacity * 2;
		char* new_data = (char*)realloc(str->data, new_capacity);
		if (!new_data) return false;
		str->data = new_data;
		str->capacity = new_capacity;
	}

	str->data[str->length] = push_char;
	str->length += 1;
	str->data[str->length] = '\0';

	return true;
}

bool string_push_back_str(String* str, char* push_str) {
	size_t push_str_length = 0;

	while (push_str[push_str_length] != '\0') {
		++push_str_length;
	}

	if (str->length + push_str_length >= str->capacity) {
		size_t new_capacity = str->capacity * 2 + push_str_length;
		char* new_data = (char*)realloc(str->data, new_capacity);
		if (!new_data) return false;
		str->data = new_data;
		str->capacity = new_capacity;
	}

	for (size_t i = 0; i < push_str_length; ++i) {
		str->data[str->length + i] = push_str[i];
	}

	str->length += push_str_length;
	str->data[str->length] = '\0';

	return true;
}

void string_reverse(String* s) {
	for (size_t i = 0; i < s->length / 2; ++i) {
		char temp = s->data[i];
		s->data[i] = s->data[s->length - 1 - i];
		s->data[s->length - 1 - i] = temp;
	}
}

String* string_from_number(size_t n) {
	String* str = string_new();

	while (n > 0) {
		string_push_back_char(str, n % 10 + '0');
		n /= 10;
	}

	string_reverse(str);

	return str;
}

typedef struct Date {
	size_t year;
	size_t month;
	size_t day;
} Date;

Date* date_new(size_t day, size_t month, size_t year);
void date_free(Date* date);
String* date_to_string(Date* date);

Date* date_new(size_t day, size_t month, size_t year) {
	Date* new_date = (Date*)malloc(sizeof(Date));

	if (!new_date) {
		printf("ERROR: Date allocation failed\n");
		exit(1);
	}

	new_date->day = day;
	new_date->month = month;
	new_date->year = year;

	return new_date;
}

void date_free(Date* date) {
	free(date);
}

String* date_to_string(Date* date) {
	String* str = string_new();

	string_push_back_char(str, '0' + date->day / 10 % 10);
	string_push_back_char(str, '0' + date->day % 10);
	string_push_back_char(str, '/');
	string_push_back_char(str, '0' + date->month / 10 % 10);
	string_push_back_char(str, '0' + date->month % 10);
	string_push_back_char(str, '/');
	string_push_back_char(str, '0' + date->year / 1000 % 10);
	string_push_back_char(str, '0' + date->year / 100 % 10);
	string_push_back_char(str, '0' + date->year / 10 % 10);
	string_push_back_char(str, '0' + date->year % 10);

	return str;
}

typedef struct Book {
	String* name;
	size_t price;
	size_t pages;
	String* language;
	size_t weight;
	struct Date* date;
} Book;

Book* book_new(char* name, size_t price, size_t pages, char* language, size_t weight, struct Date* date);
void book_free(Book* book);
String* book_to_string(Book* book);

Book* book_new(char* name, size_t price, size_t pages, char* language, size_t weight, struct Date* date) {
	Book* new_book = (Book*)malloc(sizeof(Book));

	if (!new_book) {
		printf("ERROR: Date allocation failed\n");
		exit(1);
	}

	new_book->name = string_from_char_ptr(name);
	new_book->price = price;
	new_book->pages = pages;
	new_book->language = string_from_char_ptr(language);
	new_book->weight = weight;
	new_book->date = date;

	return new_book;
}

void book_free(Book* book) {
	string_free(book->name);
	string_free(book->language);
	date_free(book->date);
	free(book);
}

String* book_to_string(Book* book) {
	String* str = string_new();
	String* temp = string_new();

	string_push_back_str(str, "\nBook:");

	string_push_back_str(str, "\nname: ");
	string_push_back_str(str, string_to_char_ptr(book->name));

	string_push_back_str(str, "\nprice: ");
	temp = string_from_number(book->price);
	string_push_back_str(str, string_to_char_ptr(temp));
	string_push_back_str(str, " $");

	string_push_back_str(str, "\npages: ");
	temp = string_from_number(book->pages);
	string_push_back_str(str, string_to_char_ptr(temp));

	string_push_back_str(str, "\nlanguage: ");
	string_push_back_str(str, string_to_char_ptr(book->language));

	string_push_back_str(str, "\nweight: ");
	temp = string_from_number(book->weight);
	string_push_back_str(str, string_to_char_ptr(temp));
	string_push_back_str(str, " g");

	string_push_back_str(str, "\ndate: ");
	string_push_back_str(str, string_to_char_ptr(date_to_string(book->date)));

	string_push_back_str(str, "\n");

	return str;
}

typedef struct HarryPotterBooks {
	struct Book* book;
	struct HarryPotterBooks* next;
} HarryPotterBooks;

HarryPotterBooks* harry_potter_books_new();
void harry_potter_books_free(HarryPotterBooks* hp);
void harry_potter_book_push_back(HarryPotterBooks** hp, Book* book);
String* harry_potter_books_to_string(HarryPotterBooks* hp);

HarryPotterBooks* harry_potter_books_new() {
	return NULL;
}

void harry_potter_books_free(HarryPotterBooks* hp) {
	HarryPotterBooks* curr = hp;
	
	while (curr != NULL) {
		hp = (HarryPotterBooks*)curr->next;

		book_free(curr->book);
		free(curr);

		curr = hp;
	}
}

void harry_potter_book_push_back(HarryPotterBooks** hp, Book* book) {
	HarryPotterBooks* new_hp = (HarryPotterBooks*)malloc(sizeof(HarryPotterBooks));

	if (!new_hp) {
		printf("ERROR: HarryPotterBooks push_back_harry_potter_book allocation failed\n");
		exit(1);
	}

	new_hp->book = book;
	new_hp->next = NULL;

	if (*hp == NULL) {
		*hp = new_hp;
	} else {
		HarryPotterBooks* end = *hp;

		while (end->next != NULL) {
			end = end->next;
		}

		end->next = new_hp;
	}
}

String* harry_potter_books_to_string(HarryPotterBooks* hp) {
	String* str = string_new();
	HarryPotterBooks* curr = hp;

	String* temp = string_new();

	string_push_back_str(str, "\nHarry Potter Books:");
	
	while (curr != NULL) {
		temp = book_to_string(curr->book);

		string_push_back_str(str, string_to_char_ptr(temp));

		curr = curr->next;
	}

	string_free(temp);

	return str;
}

int main() {
	HarryPotterBooks* hp = harry_potter_books_new();

	harry_potter_book_push_back(
		&hp,
		book_new(
			"Harry Potter and the Philosopher's Stone",
			22,
			223,
			"English",
			500,
			date_new(26, 6, 1997)
		));

	harry_potter_book_push_back(
		&hp,
		book_new(
			"Harry Potter and the Chamber of Secrets",
			24,
			251,
			"English",
			700,
			date_new(2, 7, 1998)
		));

	harry_potter_book_push_back(
		&hp,
		book_new(
			"Harry Potter and the Prisoner of Azkaban",
			26,
			317,
			"English",
			850,
			date_new(8, 7, 1999)
		));

	harry_potter_book_push_back(
		&hp,
		book_new(
			"Harry Potter and the Goblet of Fire",
			30,
			636,
			"English",
			1500,
			date_new(8, 7, 2000)
		));

	harry_potter_book_push_back(
		&hp,
		book_new(
			"Harry Potter and the Order of the Phoenix",
			34,
			766,
			"English",
			1800,
			date_new(21, 7, 2003)
		));

	harry_potter_book_push_back(
		&hp,
		book_new(
			"Harry Potter and the Half-Blood Prince",
			32,
			607,
			"English",
			1400,
			date_new(16, 7, 2005)
		));

	harry_potter_book_push_back(
		&hp,
		book_new(
			"Harry Potter and the Deathly Hallows",
			36,
			607,
			"English",
			1500,
			date_new(21, 7, 2007)
		));

	String* books = harry_potter_books_to_string(hp);
	printf("%s", string_to_char_ptr(books));

	string_free(books);
	harry_potter_books_free(hp);
}
