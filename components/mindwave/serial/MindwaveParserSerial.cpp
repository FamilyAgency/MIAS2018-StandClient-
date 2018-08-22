#include "MindwaveParserSerial.h"
#include "tools/MathTools.h"

MindwaveParserSerial::MindwaveParserSerial(QObject *parent) : MindwaveParserBase(parent)
{
    initParser(PARSER_TYPE_PACKETS, NULL);
}

void MindwaveParserSerial::parse(const QByteArray& data)
{
    for (auto &byte : data)
    {
        parseByte(byte);
    }
}

int MindwaveParserSerial::initParser(uchar parserType, void *customData )
{
    switch (parserType)
    {
    case PARSER_TYPE_PACKETS:
        parser.state = PARSER_STATE_SYNC;
        break;

    case PARSER_TYPE_2BYTERAW:
        parser.state = PARSER_STATE_WAIT_HIGH;
        break;

    default:
        return(-2);
    }

    parser.type = parserType;
    parser.customData = customData;
    return 0;
}

int MindwaveParserSerial::parseByte(uchar byte)
{
    int returnValue = 0;

    switch (parser.state)
    {
    case PARSER_STATE_SYNC:
        if (byte == PARSER_SYNC_BYTE)
        {
            parser.state = PARSER_STATE_SYNC_CHECK;
        }
        break;

    case PARSER_STATE_SYNC_CHECK:
        if (byte == PARSER_SYNC_BYTE)
        {
            parser.state = PARSER_STATE_PAYLOAD_LENGTH;
        }
        else
        {
            parser.state = PARSER_STATE_SYNC;
        }
        break;

    case PARSER_STATE_PAYLOAD_LENGTH:
        parser.payloadLength = byte;

        if (parser.payloadLength > 170)
        {
            parser.state = PARSER_STATE_SYNC;
            returnValue = -3;
        }
        else if (parser.payloadLength == 170)
        {
            returnValue = -4;
        }
        else
        {
            parser.payloadBytesReceived = 0;
            parser.payloadSum = 0;
            parser.state = PARSER_STATE_PAYLOAD;
        }
        break;

    case PARSER_STATE_PAYLOAD:
        parser.payload[parser.payloadBytesReceived++] = byte;
        parser.payloadSum = static_cast<uchar>(parser.payloadSum + byte);

        if (parser.payloadBytesReceived >= parser.payloadLength)
        {
            parser.state = PARSER_STATE_CHKSUM;
        }
        break;

    case PARSER_STATE_CHKSUM:
        parser.chksum = byte;
        parser.state = PARSER_STATE_SYNC;

        if (parser.chksum != ((~parser.payloadSum)&0xFF))
        {
            returnValue = -2;
        }
        else
        {
            returnValue = 1;
            parsePacketPayload();
        }
        break;

    case PARSER_STATE_WAIT_HIGH:
        if ((byte & 0xC0) == 0x80)
        {
            parser.state = PARSER_STATE_WAIT_LOW;
        }
        break;

    case PARSER_STATE_WAIT_LOW:
        if ((byte & 0xC0) == 0x40)
        {
            parser.payload[0] = parser.lastByte;
            parser.payload[1] = byte;

            parseSerialData(0, PARSER_CODE_RAW_SIGNAL, 2,
                            parser.payload,
                            parser.customData);

            returnValue = 1;
        }
        parser.state = PARSER_STATE_WAIT_HIGH;
        break;

    default:
        parser.state = PARSER_STATE_SYNC;
        returnValue = -5;
        break;
    }

    parser.lastByte = byte;
    return returnValue;
}

int MindwaveParserSerial::parsePacketPayload()
{
    uchar i = 0;
    uchar extendedCodeLevel = 0;
    uchar code = 0;
    uchar numBytes = 0;

    while (i < parser.payloadLength)
    {
        while (parser.payload[i] == PARSER_EXCODE_BYTE)
        {
            extendedCodeLevel++;
            i++;
        }

        code = parser.payload[i++];
        if (code >= 0x80)
        {
            numBytes = parser.payload[i++];
        }
        else
        {
            numBytes = 1;
        }

        parseSerialData(extendedCodeLevel, code, numBytes,
                        parser.payload+i, parser.customData);
        i = static_cast<uchar>(i + numBytes);
    }

    return 0;
}


void MindwaveParserSerial::parseSerialData(uchar extendedCodeLevel,
                                           uchar code,
                                           uchar valueLength,
                                           const uchar *value,
                                           void* /* customData */)
{
    if (extendedCodeLevel == 0)
    {
        switch (code)
        {
        case PARSER_CODE_BATTERY:
            batteryData = value[0] & 0xFF;
            break;

        case PARSER_CODE_POOR_QUALITY:
            signalData = value[0] & 0xFF;
            emit signalLevelParsed(signalData);
            break;

        case 0x03:
            heartRateData = value[0] & 0xFF;
            break;

        case PARSER_CODE_ATTENTION:
            attentionData = value[0] & 0xFF;
            emit attentionParsed(attentionData);
            break;

        case PARSER_CODE_MEDITATION:
            meditationData = value[0] & 0xFF;
            emit meditationParsed(meditationData);
            break;

        case 0x06:
            raw8BitData = value[0] & 0xFF;
            break;

        case 0x07:  // raw start marker
            break;

        case 0x80:
            raw16BitData = (value[0]<<8) | value[1];
            break;

        case 0x81:
            //            eegPowerData.delta    = ((value[0]&0xFF)<<24)   | ((value[1]&0xFF)<<16)  | ((value[2]&0xFF)<<8)  | (value[3]&0xFF);
            //            eegPowerData.theta    = ((value[4]&0xFF)<<24)   | ((value[5]&0xFF)<<16)  | ((value[6]&0xFF)<<8)  | (value[7]&0xFF);
            //            eegPowerData.lowAlpha = ((value[8]&0xFF)<<24)   | ((value[9]&0xFF)<<16)  | ((value[10]&0xFF)<<8) | (value[11]&0xFF);
            //            eegPowerData.highAlpha= ((value[12]&0xFF)<<24)  | ((value[13]&0xFF)<<16) | ((value[14]&0xFF)<<8) | (value[15]&0xFF);
            //            eegPowerData.lowBeta  = ((value[16]&0xFF)<<24)  | ((value[17]&0xFF)<<16) | ((value[18]&0xFF)<<8) | (value[19]&0xFF);
            //            eegPowerData.highBeta = ((value[20]&0xFF)<<24)  | ((value[21]&0xFF)<<16) | ((value[22]&0xFF)<<8) | (value[23]&0xFF);
            //            eegPowerData.lowGamma = ((value[24]&0xFF)<<24)  | ((value[25]&0xFF)<<16) | ((value[26]&0xFF)<<8) | (value[27]&0xFF);
            //            eegPowerData.midGamma = ((value[28]&0xFF)<<24)  | ((value[29]&0xFF)<<16) | ((value[30]&0xFF)<<8) | (value[31]&0xFF);
            break;

        case 0x083:
            //            asicEegData.delta    = ((value[0]&0xFF)<<16)  | ((value[1]&0xFF)<<8)  | (value[2]&0xFF);
            //            asicEegData.theta    = ((value[3]&0xFF)<<16)  | ((value[4]&0xFF)<<8)  | (value[5]&0xFF);
            //            asicEegData.lowAlpha = ((value[8]&0xFF)<<16)  | ((value[9]&0xFF)<<8)  | (value[10]&0xFF);
            //            asicEegData.highAlpha= ((value[12]&0xFF)<<16) | ((value[13]&0xFF)<<8) | (value[14]&0xFF);
            //            asicEegData.lowBeta  = ((value[16]&0xFF)<<16) | ((value[17]&0xFF)<<8) | (value[18]&0xFF);
            //            asicEegData.highBeta = ((value[20]&0xFF)<<16) | ((value[21]&0xFF)<<8) | (value[22]&0xFF);
            //            asicEegData.lowGamma = ((value[24]&0xFF)<<16) | ((value[25]&0xFF)<<8) | (value[26]&0xFF);
            //            asicEegData.midGamma = ((value[28]&0xFF)<<16) | ((value[29]&0xFF)<<8) | (value[30]&0xFF);
            break;

        case 0x86:
            rrIntervalData = (value[0]<<8) | value[1];
            break;

        default:
            qDebug() << "Unrecognized Signal Detected...";
            qDebug() << "EXCODE: " << (value[0] & 0xFF)
                    <<" CODE: "   << code
                   <<" vLength: "<< valueLength;

            qDebug() << "DataValues: ";
            for (int i = 0; i!= valueLength; i++)
            {
                qDebug() << (value[i] & 0xFF);
            }
            break;
        }
    }
}
