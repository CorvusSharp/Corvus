//add books to database

var dialogAddBook = document.getElementById('ADDBOOK');

var form = document.getElementById('addBookForm');

var submit = document.getElementById('addBookButton');



function createRowForTable(book) { // функция создания строки таблицы
    var row = document.createElement('tr');

    // Создание ячейки для заголовка с ссылкой
    var title = document.createElement('td');
    var linkToBook = document.createElement('a');
    linkToBook.setAttribute('href', `/book/${book.id}`);
    linkToBook.textContent = book.title;
    title.appendChild(linkToBook); // Добавление ссылки в ячейку заголовка
    row.appendChild(title); // Добавление ячейки заголовка в строку

    var author = document.createElement('td');
    author.textContent = book.author;
    row.appendChild(author);

    var date = document.createElement('td');
    date.textContent = book.date;
    row.appendChild(date);

    var status = document.createElement('td');
    status.textContent = book.status;
    row.appendChild(status);

    var returnDate = document.createElement('td');
    if(book.returnDate){
        returnDate.textContent = book.returnDate;
    }
    row.appendChild(returnDate);

    return row;
}

function parsBooksJson(books){
    var booksHtml = document.getElementById('placer'); // получаем таблицу
    booksHtml.innerHTML ='';
    for (const book of books) { // перебираем массив кни
        booksHtml.appendChild(createRowForTable(book)); // добавляем в таблицу книгу
    }
}



document.getElementById('addButton').addEventListener('click', function () {
    dialogAddBook.showModal();// открываем  окно добавления книги при нажатии на кнопку
    console.log('addButton clicked');
});



document.getElementById('selector').addEventListener('change', function (event) {
        var selected = event.target.value;
        var urlSearchParams =window.location.search;

        fetch('/api/books?' + new URLSearchParams({sort: selected})
             ,{
            method: 'get'
        }).then(function (response) {
            if (response.ok) {
                return response.json();
            }
            throw new Error('Network response was not ok.');
        }).then(function (data) {
            parsBooksJson(data);
        }).catch(function (error) {
            console.error('Error during fetch operation:', error);
        });

});



document.getElementById('cancelButton').addEventListener('click', function () {
    dialogAddBook.close();
});


//edit book




