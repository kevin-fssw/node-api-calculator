// binding.gyp의 target_name과 동일한 이름으로 모듈 바인딩
const addon = require('bindings')('addon');

console.log('Calculator', addon.Calculator)
console.log('createCalculator', addon.createCalculator)

const calculator = new addon.Calculator(0)
console.log(calculator.add(10)); // 10
console.log(calculator.subtract(5)); // 5
console.log(calculator.multiply(8)); // 40
console.log(calculator.divide(4)); // 10
console.log(calculator.getValue()); // 10

const calculator2 = addon.createCalculator(0)
console.log(calculator2.add(10)); // 10
console.log(calculator2.subtract(5)); // 5
console.log(calculator2.multiply(8)); // 40
console.log(calculator2.divide(4)); // 10
console.log(calculator2.getValue()); // 10



module.exports = {

};