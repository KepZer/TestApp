'use strict';
var express = require('express');
var router = express.Router();
var tMod = require('bindings')('TestModule');


//title: testModule.ContainsUser("Гость") 
router.get('/', function (req, res) {
    res.render('index', {});
});

router.get('/check', function (req, res) {
    var name = req.param("userName");
    if (tMod.ContainsUser(name)) {
        console.log("yes");
    } else {
        console.log("no");
    }


    res.render('index', {});
});

module.exports = router;