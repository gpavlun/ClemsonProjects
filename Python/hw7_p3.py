class Book:
    def __init__(self,title,author,isbn):
        self.title=title
        self.author=author
        self.isbn=isbn
    def __str__(self):
        return f'<{self.title}> by {self.author} (ISBN:{self.isbn})'
class Library:
    def __init__(self, books:list):
        self.books=books
    def add_book(self, book):
        self.books.append(book)
    def borrow_book(self,book):
        self.books.remove(book)
    def return_book(self,book):
        self.books.append(book)
    def display_books(self):
        print(self.books)
