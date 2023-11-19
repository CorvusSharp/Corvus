var dialogWhoTake = document.getElementById('WHOTAKEN');

document.getElementById("whoTake").addEventListener("click", function () {
    dialogWhoTake.showModal();
    console.log('whoTakeButton clicked');
});

document.getElementById("okButtonWhoSave").addEventListener("click", function () {
    console.log('okButtonWhoSave');
    dialogWhoTake.close();
});
