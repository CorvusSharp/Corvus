//апи для взаимодействия с базой данных на сервере, которая описана в виде json
let books = require('../books.json');
let express = require('express');
const {request} = require("express");
let router = express.Router();

router.route("/book/:id(\\d+)").get((req, res) => {
    let id = parseInt(req.params.id);
    let book = books.find(book => book.id === id);//ищем книгу по id
    console.log(books)

    res.render("book", {book: book, title: "Book"});//передаем в шаблона book.pug книгу

}).delete((req, res) => {
    let id = req.params.id;
    let bookIndex = books.findIndex(book => book.id === id);
    books.splice(bookIndex, 1);//удаляем книгу из массива
    res.json({message: "ok"});
});

//update book after editing and save data not replace


router.route("/book/:id(\\d+)").put((req, res) => {
    let id = parseInt(req.params.id);
    let book = books.find(book => book.id === id);
    if (req.body.borrower) {
        book.borrower = req.body.borrower;
    }
    if (req.body.returnDate) {
        book.returnDate = req.body.returnDate;
    }
    if (req.body.status) {
        book.status = req.body.status;
    }
    if (req.body.author) {
        book.author = req.body.author;
    }
    if (req.body.date) {
        book.date = req.body.date;
    }
    if (req.body.title) {
        book.title = req.body.title;
    }
    res.json({message: "ok"});

});



router.route('/api/books')
    .get((req, res) => {
        console.log(req.query)
        let sort = req.query.sort;
        switch (sort) {
            case 'all':
                return res.json(books);
            case 'available':
                return res.json(books.filter(book => book.status === 'available'));
            case 'taken':
                return res.json(books.filter(book => book.status === 'taken'));
            case 'overdue':
                return res.json(books.filter(book => new Date(book.returnDate) < new Date() && book.status === 'taken'));
        }

    })
    .post((req, res) => {
        books.push(req.body);//добавляем книгу в массив
        console.log(req.body);

    });



router.route('/books')
    .get((req, res) => {
        res.render('books', {books: books, title: 'Books'})//передаем в шаблон books.ejs массив книг
    })
    .post((req, res) => {
            var book = req.body;
            book.id = books.length >= 1 ? books[books.length - 1].id + 1 : 1;
            book.status = 'available';//при добавлении книги она сразу доступна
            book.returnDate = null
            book.borrower = null
            books.push(book);
            res.redirect('/books');//перенаправляем на страницу books

        }
    );


module.exports = router; // экспортируем настроенный роутер
