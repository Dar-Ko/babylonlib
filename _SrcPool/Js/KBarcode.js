//$RCSfile: KBarcode.js,v $: script file
//$Revision: 1.1 $ $Date: 2013/12/19 22:03:54 $
//$Author: ddarko $
//
//Create EAN13 barcode widget

// left margin, start character
var start = '00000000000101';

// prefix character
var prefix = ['111111', '110100', '110010', '110001', '101100', '100110', '100011', '101010', '101001', '100101'];

// left characters, odd parity
var leftodd = ['0001101', '0011001', '0010011', '0111101', '0100011', '0110001', '0101111', '0111011', '0110111', '0001011'];

// left characters, even parity
var lefteven = ['0100111', '0110011', '0011011', '0100001', '0011101', '0111001', '0000101', '0010001', '0001001', '0010111'];

// center bar
var center = '01010';

// right characters
var right = ['1110010', '1100110', '1101100', '1000010', '1011100', '1001110', '1010000', '1000100', '1001000', '1110100'];

// stop character, right margin
var stop = '10100000000000';

//
// encode EAN13(JAN13)
//

function drawEan13(context, data, x, y, w, h) {

    // check data length
    if (!/^\d{12,13}$/.test(data)) {
        throw new Error('invalid data');
    }

    // calculate check digit
    var odd = 0;
    var even = 0;
    for (var i = 0; i < 12; i += 2) {
        odd += parseInt(data.charAt(i));
        even += parseInt(data.charAt(i + 1));
    }
    var cd = (220 - odd - even * 3) % 10;

    // check digit
    if (data.length < 13) {
        data += cd;
    }
    else if (cd != parseInt(data.charAt(12))) {
        throw new Error('invalid check digit');
    }

    // build modules
    var module = '';

    // append left margin and start character
    module += start;

    // append left characters
    var parity = prefix[parseInt(data.charAt(0))];
    for (i = 1; i < 7; i++) {
        var c = parseInt(data.charAt(i));
        module += parseInt(parity.charAt(i - 1)) ? leftodd[c] : lefteven[c];
    }

    // append center bar
    module += center;

    // append right characters
    for (i = 7; i < 13; i++) {
        c = parseInt(data.charAt(i));
        module += right[c];
    }

    // append stop character and right margin
    module += stop;

    // draw modules
    for (var i = 0; i < module.length; i++) {
        context.fillStyle = parseInt(module.charAt(i)) ? 'black' : 'white';
        context.fillRect(x + i * w, y, w, h);
    }
}
