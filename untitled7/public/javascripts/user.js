const dialog = $("#dialog-form").dialog({
    autoOpen: false,
    modal: true,
    buttons: {
        Confirm: function () {

            var name = $("#form-name").val();
            var email = $("#form-email").val();
            var dateBorn = $("#form-dateBorn").val();
            var Role = $("#form-role").val();
            var Status = $("#form-status").val();
            var id = $("#id").text();

            if (name.length === 0 || email.length === 0 || dateBorn.length === 0 || Role.length === 0 || Status.length === 0) {
                alert('Fill all fields of form!');
                return;
            }
            $.ajax({
                url: `/api/users/${id}`,
                type: "PUT",
                data: {
                    name: name,
                    email: email,
                    dateBorn: dateBorn,
                    role: Role,
                    status: Status
                },
                success: function () {
                    window.location.reload();
                }
            });
        },
        Cancel: function () {
            dialog.dialog("close");
        }
    },
    close: function () {
        dialog.dialog("close");
    }

});

$("#edit").on('click', function () {
    var name = $("#name").text();
    var email = $("#email").text();
    var dateBorn = $("#dateBorn").text();
    var formRole = $("#role").text();
    var status = $("#status").text();

    $("#form-name").val(name);
    $("#form-email").val(email);
    $("#form-dateBorn").val(dateBorn);
    $("#form-role").val(formRole);
    $("#form-status").val(status);

    dialog.dialog("open");
});


/*button(id='SendMessage') send message
div(id="dialog-form-send" style="display: none;" title="Send message")
form#form-send
div
label(for='form-msg') Message:
    input(id='form-msg' name='msg', type='text', value='')
div
label(for='form-date') Date:
    input(id='form-date', name='date', type='date', value='')*/

//use post for add massage

const dialogSend = $("#dialog-form-send").dialog({
    autoOpen: false,
    modal: true,
    buttons: {
        Confirm: function () {

            var msg = $("#form-msg").val();
            var date = $("#form-date").val();
            var id = $("#id").text();

            if (msg.length === 0 || date.length === 0) {
                alert('Fill all fields of form!');
                return;
            }
            $.ajax({
                url: `/users/${id}/news`,
                type: "POST",
                data: {
                    msg: msg,
                    date: date
                },
                success: function () {
                    window.location.reload();
                }
            });
        },
        Cancel: function () {
            dialogSend.dialog("close");
        }
    },
    close: function () {
        dialogSend.dialog("close");
    }

});

$("#SendMessage").on('click', function () {
    dialogSend.dialog("open");
});




$("#ButtonFrinedList").on('click', function () {
    var id = $("#id").text();
    window.location.href = `/users/${id}/friends`;
});


$("#ButtonNewsList").on('click', function () {
    var id = $("#id").text();
    window.location.href = `/users/${id}/news`;
});