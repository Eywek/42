var db = require('./database')
var userModel = require('./user')
var faker = require('faker');
faker.locale = "fr";

var count = 0;
for (var i = 0; i < 700; i++) {
  var user = faker.name
  var firstname = user.firstName();
  var lastname = user.lastName();
  db.query('INSERT INTO `users` SET name = ?, last_name = ?, username = ?, email = ?, password = ?, last_login = ?, created_at = ?', [
    firstname,
    lastname,
    faker.internet.userName(firstname, lastname),
    faker.internet.email(firstname, lastname),
    userModel.hashPassword(faker.internet.password()),
    faker.date.recent(),
    faker.date.past()
  ], function (err, insert) {
    if (err)
      console.error(err)
    var address = faker.address
    db.query('INSERT INTO `users_accounts` SET user_id = ?, biography = ?, tags = ?, gender = ?, sexual_orientation = ?, age = ?, location = ?', [
      insert.insertId,
      faker.lorem.text(),
      faker.lorem.word() + ',' + faker.lorem.word() + ',' + faker.lorem.word() + ',' + faker.lorem.word() + ',' + faker.lorem.word() + ',' + faker.lorem.word() + ',' + faker.lorem.word(),
      faker.random.boolean() ? 'men' : 'women',
      faker.random.boolean() ? 'hetero' : (faker.random.boolean ? 'homo' : 'bi'),
      faker.random.number({
        min: 18,
        max: 90
      }),
      address.city() + ', ' + address.country()
    ], function (err) {
      if (err)
        console.error(err)
      count++
      if (count === 700)
        process.exit(0);
    })
  })
}