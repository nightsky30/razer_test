/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp razerdevice.xml -a razerdeviceadaptor.h:razerdeviceadaptor.cpp
 *
 * qdbusxml2cpp is Copyright (C) 2017 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "razerdeviceadaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class RazerDeviceAdaptor
 */

RazerDeviceAdaptor::RazerDeviceAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

RazerDeviceAdaptor::~RazerDeviceAdaptor()
{
    // destructor
}

uchar RazerDeviceAdaptor::getBrightness(RazerLedId led)
{
    // handle method call local.RazerDevice.getBrightness
    uchar out0;
    QMetaObject::invokeMethod(parent(), "getBrightness", Q_RETURN_ARG(uchar, out0), Q_ARG(RazerLedId, led));
    return out0;
}

QString RazerDeviceAdaptor::getFirmwareVersion()
{
    // handle method call local.RazerDevice.getFirmwareVersion
    QString out0;
    QMetaObject::invokeMethod(parent(), "getFirmwareVersion", Q_RETURN_ARG(QString, out0));
    return out0;
}

QVector<RazerLedId> RazerDeviceAdaptor::getLedIds()
{
    // handle method call local.RazerDevice.getLedIds
    QVector<RazerLedId> out0;
    QMetaObject::invokeMethod(parent(), "getLedIds", Q_RETURN_ARG(QVector<RazerLedId>, out0));
    return out0;
}

QVector<int> RazerDeviceAdaptor::getLedIds2()
{
    // handle method call local.RazerDevice.getLedIds2
    QVector<int> out0;
    QMetaObject::invokeMethod(parent(), "getLedIds2", Q_RETURN_ARG(QVector<int>, out0));
    return out0;
}

RazerLedId RazerDeviceAdaptor::getLedIds3()
{
    // handle method call local.RazerDevice.getLedIds3
    RazerLedId out0;
    QMetaObject::invokeMethod(parent(), "getLedIds3", Q_RETURN_ARG(RazerLedId, out0));
    return out0;
}

QString RazerDeviceAdaptor::getName()
{
    // handle method call local.RazerDevice.getName
    QString out0;
    QMetaObject::invokeMethod(parent(), "getName", Q_RETURN_ARG(QString, out0));
    return out0;
}

QString RazerDeviceAdaptor::getSerial()
{
    // handle method call local.RazerDevice.getSerial
    QString out0;
    QMetaObject::invokeMethod(parent(), "getSerial", Q_RETURN_ARG(QString, out0));
    return out0;
}

QString RazerDeviceAdaptor::getType()
{
    // handle method call local.RazerDevice.getType
    QString out0;
    QMetaObject::invokeMethod(parent(), "getType", Q_RETURN_ARG(QString, out0));
    return out0;
}

bool RazerDeviceAdaptor::setBlinking(RazerLedId led, uchar red, uchar green, uchar blue)
{
    // handle method call local.RazerDevice.setBlinking
    bool out0;
    QMetaObject::invokeMethod(parent(), "setBlinking", Q_RETURN_ARG(bool, out0), Q_ARG(RazerLedId, led), Q_ARG(uchar, red), Q_ARG(uchar, green), Q_ARG(uchar, blue));
    return out0;
}

bool RazerDeviceAdaptor::setBreathing(RazerLedId led, uchar red, uchar green, uchar blue)
{
    // handle method call local.RazerDevice.setBreathing
    bool out0;
    QMetaObject::invokeMethod(parent(), "setBreathing", Q_RETURN_ARG(bool, out0), Q_ARG(RazerLedId, led), Q_ARG(uchar, red), Q_ARG(uchar, green), Q_ARG(uchar, blue));
    return out0;
}

bool RazerDeviceAdaptor::setBreathingDual(RazerLedId led, uchar red, uchar green, uchar blue, uchar red2, uchar green2, uchar blue2)
{
    // handle method call local.RazerDevice.setBreathingDual
    bool out0;
    QMetaObject::invokeMethod(parent(), "setBreathingDual", Q_RETURN_ARG(bool, out0), Q_ARG(RazerLedId, led), Q_ARG(uchar, red), Q_ARG(uchar, green), Q_ARG(uchar, blue), Q_ARG(uchar, red2), Q_ARG(uchar, green2), Q_ARG(uchar, blue2));
    return out0;
}

bool RazerDeviceAdaptor::setBreathingRandom(RazerLedId led)
{
    // handle method call local.RazerDevice.setBreathingRandom
    bool out0;
    QMetaObject::invokeMethod(parent(), "setBreathingRandom", Q_RETURN_ARG(bool, out0), Q_ARG(RazerLedId, led));
    return out0;
}

bool RazerDeviceAdaptor::setBrightness(RazerLedId led, uchar brightness)
{
    // handle method call local.RazerDevice.setBrightness
    bool out0;
    QMetaObject::invokeMethod(parent(), "setBrightness", Q_RETURN_ARG(bool, out0), Q_ARG(RazerLedId, led), Q_ARG(uchar, brightness));
    return out0;
}

bool RazerDeviceAdaptor::setNone(RazerLedId led)
{
    // handle method call local.RazerDevice.setNone
    bool out0;
    QMetaObject::invokeMethod(parent(), "setNone", Q_RETURN_ARG(bool, out0), Q_ARG(RazerLedId, led));
    return out0;
}

bool RazerDeviceAdaptor::setSpectrum(RazerLedId led)
{
    // handle method call local.RazerDevice.setSpectrum
    bool out0;
    QMetaObject::invokeMethod(parent(), "setSpectrum", Q_RETURN_ARG(bool, out0), Q_ARG(RazerLedId, led));
    return out0;
}

bool RazerDeviceAdaptor::setStatic(RazerLedId led, uchar red, uchar green, uchar blue)
{
    // handle method call local.RazerDevice.setStatic
    bool out0;
    QMetaObject::invokeMethod(parent(), "setStatic", Q_RETURN_ARG(bool, out0), Q_ARG(RazerLedId, led), Q_ARG(uchar, red), Q_ARG(uchar, green), Q_ARG(uchar, blue));
    return out0;
}

bool RazerDeviceAdaptor::setWave(RazerLedId led, WaveDirection direction)
{
    // handle method call local.RazerDevice.setWave
    bool out0;
    QMetaObject::invokeMethod(parent(), "setWave", Q_RETURN_ARG(bool, out0), Q_ARG(RazerLedId, led), Q_ARG(WaveDirection, direction));
    return out0;
}

