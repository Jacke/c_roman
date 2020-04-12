#!/usr/bin/env node

// ** Libraries
const converter = require('./build/Release/roman_converter');

function getRomanNumber(num) {
    const result = converter.getNumber(num);
    return String.fromCharCode(result);
}

module.exports = getRomanNumber;

