var exp = require("express")
var router = exp.Router()
var users = require("../src/users.json")
router.get("/users", (req, res) => { // Маршрут для получения списка всех пользователей
    res.json(users)
})

router.route('/users/:id(\\d+)').put(function (req, res, next) { // Маршрут для получения пользователя по ID
    console.log(req.body);
    var userId = parseInt(req.params.id); // Получаем id из URL
    var index = users.findIndex((user) => user.id === userId)
    var user = users[index];
    for (const field in req.body) {
        if (user.hasOwnProperty(field)) { // Проверяем, что такое поле существует у пользователя
            user[field] = req.body[field];
        }
    }
    users[index] = user;
    res.send("SUCC");
});

module.exports = router

