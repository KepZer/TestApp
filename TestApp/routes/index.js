'use strict';
var express = require('express');
var router = express.Router();
var tMod = require('bindings')('TestModule');


//title: testModule.ContainsUser("Гость") 
router.get('/', function (req, res) {
    res.render('index', {title: ''});
});

router.get('/check', function (req, res) {
    var name = req.param("userName");
    if (tMod.ContainsUser(name)) {
        res.render('index', {title: 'Такой пользователь есть'});
    } else {
        res.render('index', {title: 'такого пользователя нет'});
    }
});

module.exports = router;