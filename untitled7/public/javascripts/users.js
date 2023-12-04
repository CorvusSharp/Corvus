// GET JSON ALL USERS

$(document).ready(function() {
    $.ajax("api/users", {
        type: "GET",
        success: function(data) {
            console.log("success", data);
            data.forEach(function(user) {
                $("#usersTable").append(userTemplate(user));
            });
        },

    });
});

function userTemplate(user) {
    // return table row with user info
    return `
        <tr id="${user.id}">
        
            <td > <a href="users/${user.id}"> ${user.name}</a></td> 
            <td>${user.email}</td>
            <td>${user.dateBorn}</td>
            <td>${user.status}</td>
            <td>${user.role}</td>

        </tr>
    `
}
