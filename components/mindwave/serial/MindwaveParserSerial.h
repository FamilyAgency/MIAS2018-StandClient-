#ifndef MINDWAVEPARSERSERIAL_H
#define MINDWAVEPARSERSERIAL_H

#include "components/mindwave/MindwaveParserBase.h"
#include "mindwaveserialdata.h"

class MindwaveParserSerial : public MindwaveParserBase
{
    Q_OBJECT
public:
    explicit MindwaveParserSerial(QObject *parent = nullptr);
    virtual void parse(const QByteArray& data) override;

private:
    ThinkGearStreamParser parser;
    int initParser(uchar parserType, void *customData);
    int parseByte(uchar byte);
    int parsePacketPayload();
    void parseSerialData(uchar extendedCodeLevel,
                         uchar code,
                         uchar valueLength,
                         const uchar *value,
                         void* /* Custom Data */);

    QVariantMap eegPowerDataMap;
    QVariantMap asicEegDataMap;

    //void convertEegPowerDataToVariant();
   // void convertAsicEegDataToVariant();

    uint16_t batteryData    = 0;
    uint16_t signalData     = 0;

    uint16_t heartRateData  = 0;
    uint16_t attentionData  = 0;
    uint16_t meditationData = 0;
    uint16_t raw8BitData    = 0;
    uint16_t raw16BitData   = 0;
    uint16_t rrIntervalData = 0;

signals:
    void signalLevelParsed(int value);
    void meditationParsed(int value);
    void attentionParsed(int value);
};

#endif // MINDWAVEPARSERSERIAL_H
