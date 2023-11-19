//обработчик всех кнопок на странице

var dialog = document.getElementById('DELETEBOOK');


document.getElementById("delBook").addEventListener("click", function () {
    dialog.showModal();
    console.log('deleteButton clicked');
});

document.getElementById('cancelButtonDelete').addEventListener('click', function () {
    dialog.close();
});


document.getElementById('deleteBookButton').addEventListener('click', function () {
    fetch(window.location.href, {
        method: 'delete'

    }).then(function (response) {
        window.location.href = '/books';
    });

});

