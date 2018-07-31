import QtQuick 2.0

Item
{
    function randomPhone()
    {
        return '8' + (Math.floor((Math.random() * (9999999999 - 1111111111)) + 1111111111));
    }

    function randomEmail()
    {
        var email = "";
        var text = "";
        var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

        for (var i = 0; i < 5; i++)
        {
            text += possible.charAt(Math.floor(Math.random() * possible.length));
        }
        email = text + "@";

        text = "";
        for (var j = 0; j < 4; j++)
        {
            text += possible.charAt(Math.floor(Math.random() * possible.length));
        }
        email += text + ".com";

        return email;
    }

    function randomName()
    {
        var possible = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";

        var text = "";
        for (var i = 0; i < 10; i++)
        {
            text += possible.charAt(Math.floor(Math.random() * possible.length));
        }
        return text;
    }
}
