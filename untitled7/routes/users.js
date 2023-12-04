var express = require('express');
var router = express.Router();
var users = require("../src/users.json"); // Убедитесь, что путь к файлу правильный


/* GET users listing. */

// Маршрут для получения пользователя по ID
router.route('/:id').get(function(req, res, next) {
  const id = parseInt(req.params.id);
  const user = users.find(user => user.id === id);

  if (!user) {
    // Лучше отправить ответ с ошибкой, чем вызывать исключение
    return res.status(404).send("User not found");
  }

  // Получение списка друзей пользователя
  const friendList = users.filter(curUser => user.friendlist.includes(curUser.id));
  const msgList = user.msg;



  // Рендеринг страницы пользователя с нужными данными
  res.render("user", { title: user.name, user, friendList, msgList});

});


router.route('/:id(\\d+)/friends').get(
    function (req, res, next) {
        const id = parseInt(req.params.id);
        const user = users.find(user => user.id === id);

        if (!user) {
            return res.status(404).send("User not found");
        }

        const friendList = users.filter(curUser => user.friendlist.includes(curUser.id));
        friendList.sort((a,b) => a.name.localeCompare(b.name));

        // Рендеринг страницы пользователя с нужными данными
        res.render("friend", { title: `Friends of ${user.name}`, friendList});
    }
)

// Маршрут для получения списка всех пользователей
router.get('/', function(req, res, next) {
  // Добавил список пользователей на страницу всех пользователей
  res.render("users", { title: "Users", users });
});


router.route('/:id(\\d+)/news').get(function (req, res, next) {
    const id = parseInt(req.params.id);
    const user = users.find(user => user.id === id);
    if (!user) {
        return res.status(404).send("User not found");
    }

    const msgList = user.msg;
    msgList.sort((a,b) => new Date(b.date) - new Date(a.date));

    // Рендеринг страницы пользователя с нужными данными

    res.render("user-news", { title: `News by ${user.name}`, msgList});

});


router.route('/:id(\\d+)/news').post(function (req, res, next) {
    const id = parseInt(req.params.id);
    const user = users.find(user => user.id === id);
    if (!user) {
        return res.status(404).send("User not found");
    }

    const msgList = user.msg;
    msgList.push({
        msg: req.body.msg,
        date: req.body.date
    });

    res.send("SUCC");

});



module.exports = router;
