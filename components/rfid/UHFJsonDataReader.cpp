#include "UHFJsonDataReader.h"

UHFJsonDataReader::UHFJsonDataReader(QObject *parent) : UHFDataReader(parent)
{

}

void UHFJsonDataReader::onReadyRead()
{
    if(!serialPort->isOpen())
    {
        return;
    }

    QByteArray bytesReaded = serialPort->readAll();

    if(bytesReaded.isEmpty())
    {
        return;
    }

    //qDebug()<<"bytesReaded:: "<< bytesReaded;
    QString hex_string;
//    std::vector<uint8_t> buff;
//    create_hex_str(buff, hex_string);
//    qDebug() << "hex_string  :: "<<hex_string;


    const QString idIdentificator  = "49 44 3a";
    const std::string semicolon = "3b";

    auto index1 = hex_string.contains(idIdentificator);

     qDebug() << "index1  :: "<<index1;

//    std::string id = "";
//    if (index1 != std::string::npos)
//    {
//        auto cur = hex_string.substr(index1, hex_string.size() - 1);
//        auto index2 = cur.find(semicolon);

//        if (index2 != std::string::npos)
//        {
//            auto fin = cur.substr(0, index2);
//            id = fin.substr(8, fin.size() - 1);
//        }
//    }

   // auto _id = stringTools().fromHex(id);
}

void UHFJsonDataReader::create_hex_str(std::vector<uint8_t> data, std::string &tgt)
{
//    std::stringstream ss;
//    ss << std::hex << std::setfill('0');
//    ss << "\n";

//    for (int i = 0; i < data.size(); i++)
//    {
//        ss << std::setw(2) << static_cast<unsigned>(data[i]) << " ";
//    }
//    tgt = ss.str();
}
