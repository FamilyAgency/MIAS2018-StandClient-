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

    function formatSeconds(seconds)
    {
        var minutes = Math.floor(seconds / 60);
        var secs = (seconds % 60).toFixed(0);

        if(minutes < 10)
        {
            minutes = "0" + minutes
        }

        if(secs < 10)
        {
            secs = "0" + secs;
        }

        return minutes + ":" + secs;
    }

    property var decCache: [];
    function decOfNum(number, titles)
    {
        if(!decCache[number]) decCache[number] = number % 100 > 4 && number % 100 < 20 ? 2 : decCases[Math.min(number % 10, 5)];
        return titles[decCache[number]];
    }

    function getTimeToStart(seconds)
    {
        var minutes = Math.floor(seconds / 60);
        if(minutes > 0)
        {
            if (minutes === 4 || minutes === 3 || minutes === 2)
                return  minutes + " минуты";

            if (minutes === 1)
                return  minutes + " минуту";

            return  minutes + " минут";
        }
        else
        {
            return  "1 минуту";
            //return  seconds + " секунд";
           // return  decOfNum(seconds, ['секунда', 'секунды', 'секунд']);
        }
    }
}
