var express = require('express');
var router = express.Router();
var users = require("../src/users.json");

/* GET home page. */

router.get('/news', function(req, res, next) {

    msg = [];
    users.forEach(user => {
        user.msg.forEach(m => {
            msg.push({
                id: user.id,
                name: user.name,
                ...m
            });

        });
    });

    msg.sort((a,b) => new Date(b.date) - new Date(a.date));

    res.render('news', { title: 'News', msg });


});

module.exports = router;


