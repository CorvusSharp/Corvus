var dialogTake = document.getElementById('TAKEBOOK');
var dialogWhoTake = document.getElementById('WHOTAKENBOOK');
var state = false

document.getElementById("takeBook").addEventListener("click", function () {
    dialogTake.showModal();
    console.log('takeButton clicked');
});

document.getElementById("saveButtonTake").addEventListener("click", function () {
    console.log('saveButtonTake clicked');
    var name = document.getElementById('nameFormTaken').value;
    var returnDate = document.getElementById('dateFormTaken').value;

    if (name !== '' && returnDate !== '') {
        fetch(window.location.href, {
            method: 'put',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                'borrower': name,
                'returnDate': returnDate,
                'status': 'taken'
            })
        }).then(function (response) {
            if (response.ok) {
                location.reload();
                return response.json(); // парсим тело ответа как JSON
            }
            throw new Error('Network response was not ok.');
        }).then(function (data) {
            dialogTake.close();
        }).catch(function (error) {
            console.error('Error during fetch operation:', error);
        });
    }
});



document.getElementById("cancelButtonTake").addEventListener("click", function () {
    console.log('cancelButtonTake clicked');
    dialogTake.close();
});
