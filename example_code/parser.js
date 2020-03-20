var payload,
  var1,
  var2,
  var3,
  var4,
  i,
  binpayload,
  parsedData = [],
  obj = {};

//Lookup table to convert hex payload into binary
var lookupTable = {
        '0': '0000', '1': '0001', '2': '0010', '3': '0011', '4': '0100',
        '5': '0101', '6': '0110', '7': '0111', '8': '1000', '9': '1001',
        'a': '1010', 'b': '1011', 'c': '1100', 'd': '1101',
        'e': '1110', 'f': '1111',
        'A': '1010', 'B': '1011', 'C': '1100', 'D': '1101',
        'E': '1110', 'F': '1111'
    };

//convert hex payload to binary
binpayload = '';
for (i = 0; i < payload.length; i += 1) {
    binpayload += lookupTable[payload[i]];
}


//retrieve each value in the binary extension, and convert it to int
var1 = parseInt(binpayload.slice(0,5), 2);
var2 = parseInt(binpayload.slice(5,11), 2);
var3 = parseInt(binpayload.slice(11,18), 2);
var4 = parseInt(binpayload.slice(18, 19), 2);

// Store objects in parsedData array
obj = {};
obj.key = 'var1';
obj.value = var1;
obj.type = 'number';
obj.unit = '';
parsedData.push(obj);

obj = {};
obj.key = 'var2';
obj.value = var2;
obj.type = 'number';
obj.unit = '';
parsedData.push(obj);

obj = {};
obj.key = 'var3';
obj.value = var3;
obj.type = 'number';
obj.unit = '';
parsedData.push(obj);

obj = {};
obj.key = 'var4';
obj.value = var4;
obj.type = 'number';
obj.unit = '';
parsedData.push(obj);

//console.log(parsedData);
return parsedData;