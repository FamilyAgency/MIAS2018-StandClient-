import QtQuick 2.0

Item
{
    function randomPhone()
    {
        return '+7' + (Math.floor((Math.random() * (9999999999 - 1111111111)) + 1111111111));
    }

    function mapRange(value, low1, high1, low2, high2)
    {
        return low2 + (high2 - low2) * (value - low1) / (high1 - low1);
    }

    function mapRangeClamp(value, low1, high1, low2, high2)
    {
        if(value < low1) return low2;
        if(value > high1) return high2;
        return low2 + (high2 - low2) * (value - low1) / (high1 - low1);
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

    function formatSeconds1(seconds)
    {
        var minutes = Math.floor(seconds / 60);
        var secs = (seconds % 60).toFixed(0);

        if(secs < 10)
        {
            secs = "0" + secs;
        }

        return minutes + ":" + secs;
    }

    property var decCache: [];
    property var decCases : [2, 0, 1, 1, 1, 2];

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
            return minutes + " " + decOfNum(minutes, ['минуту', 'минуты', 'минут']);
        }
        else
        {
            return  "1 минуту";
        }
    }
}
