var dialogReturn = document.getElementById('RETURNBOOK');


document.getElementById('returnBook').addEventListener('click', function () {
    dialogReturn.showModal();
    console.log('returnButton clicked');

});

//return book

document.getElementById('returnBookButton').addEventListener('click', function () {
    fetch(window.location.href, {
        method: 'put',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            'status': 'available',
            'returnDate': null,
            'borrower': null
        })
    }).then(function (response) {
        if (response.ok) {
            console.log(response);
            location.reload();
            return response.json();
        }
        throw new Error('Network response was not ok.');

    }).then(function (data) {
        dialogReturn.close();

    }).catch(function (error) {
        console.error('Error during fetch operation:', error);
    });
});



document.getElementById('cancelButtonReturn').addEventListener('click', function () {
    dialogReturn.close();
});