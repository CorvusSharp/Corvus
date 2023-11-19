var dialogEdit = document.getElementById('EDITBOOK');

document.getElementById('editBookForm').addEventListener('click', function () {
    dialogEdit.showModal();
    console.log('editButton clicked');
});

document.getElementById('cancelButtonEdit').addEventListener('click', function () {
    dialogEdit.close();
});

//save data from edit form
document.getElementById('SaveBook').addEventListener('click', function () {
    console.log('saveButton clicked');
    //get data from form
    var author = document.getElementById('editAuthor').value;
    var data = document.getElementById('editDate').value;
    var title = document.getElementById('editTitle').value;
    console.log(title, author, data);

    if (author !== '', data !== '', title !== '') {

        fetch(window.location.href, {
            method: 'put',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                'author': author,
                'date': data,
                'title': title
            })
        }).then(function (response) {
            if (response.ok) {
                console.log(response);
                location.reload();
                return response.json();
            }
            throw new Error('Network response was not ok.');

        }).then(function (data) {
            dialogEdit.close();
        }).catch(function (error) {
            console.error('Error during fetch operation:', error);
        });
    }
});