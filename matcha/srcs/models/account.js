module.exports = {

    table: 'users_accounts',

    fields: {
        'biography': 'required:max=500',
        'gender': 'required:in=men,women,other',
        'sexual_orientation': 'required:in=hetero,homo,bi',
        'tags': 'required:max=500'
    }

};