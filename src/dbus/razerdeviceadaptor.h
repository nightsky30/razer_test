/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp razerdevice.xml -a razerdeviceadaptor.h:razerdeviceadaptor.cpp -c RazerDeviceAdaptor
 *
 * qdbusxml2cpp is Copyright (C) 2017 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef RAZERDEVICEADAPTOR_H
#define RAZERDEVICEADAPTOR_H
#include "../led/razerled.h"

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface io.github.openrazer1.Device
 */
class RazerDeviceAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "io.github.openrazer1.Device")
    Q_CLASSINFO("D-Bus Introspection", ""
                "  <interface name=\"io.github.openrazer1.Device\">\n"
                "    <method name=\"getName\">\n"
                "      <arg direction=\"out\" type=\"s\"/>\n"
                "    </method>\n"
                "    <method name=\"getType\">\n"
                "      <arg direction=\"out\" type=\"s\"/>\n"
                "    </method>\n"
                "    <method name=\"getLedIds\">\n"
                "      <annotation value=\"QVector&lt;RazerLedId&gt;\" name=\"org.qtproject.QtDBus.QtTypeName.Out0\"/>\n"
                "      <arg direction=\"out\" type=\"a(i)\"/>\n"
                "    </method>\n"
                "    <method name=\"getLedIds2\">\n"
                "      <annotation value=\"QVector&lt;int&gt;\" name=\"org.qtproject.QtDBus.QtTypeName.Out0\"/>\n"
                "      <arg direction=\"out\" type=\"ai\"/>\n"
                "    </method>\n"
                "    <method name=\"getLedIds3\">\n"
                "      <annotation value=\"RazerLedId\" name=\"org.qtproject.QtDBus.QtTypeName.Out0\"/>\n"
                "      <arg direction=\"out\" type=\"(i)\"/>\n"
                "    </method>\n"
                "    <method name=\"getSerial\">\n"
                "      <arg direction=\"out\" type=\"s\"/>\n"
                "    </method>\n"
                "    <method name=\"getFirmwareVersion\">\n"
                "      <arg direction=\"out\" type=\"s\"/>\n"
                "    </method>\n"
                "    <method name=\"setNone\">\n"
                "      <arg direction=\"out\" type=\"b\"/>\n"
                "      <annotation value=\"RazerLedId\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
                "      <arg direction=\"in\" type=\"(i)\" name=\"led\"/>\n"
                "    </method>\n"
                "    <method name=\"setStatic\">\n"
                "      <arg direction=\"out\" type=\"b\"/>\n"
                "      <annotation value=\"RazerLedId\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
                "      <arg direction=\"in\" type=\"(i)\" name=\"led\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"red\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"green\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"blue\"/>\n"
                "    </method>\n"
                "    <method name=\"setBreathing\">\n"
                "      <arg direction=\"out\" type=\"b\"/>\n"
                "      <annotation value=\"RazerLedId\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
                "      <arg direction=\"in\" type=\"(i)\" name=\"led\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"red\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"green\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"blue\"/>\n"
                "    </method>\n"
                "    <method name=\"setBreathingDual\">\n"
                "      <arg direction=\"out\" type=\"b\"/>\n"
                "      <annotation value=\"RazerLedId\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
                "      <arg direction=\"in\" type=\"(i)\" name=\"led\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"red\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"green\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"blue\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"red2\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"green2\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"blue2\"/>\n"
                "    </method>\n"
                "    <method name=\"setBreathingRandom\">\n"
                "      <arg direction=\"out\" type=\"b\"/>\n"
                "      <annotation value=\"RazerLedId\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
                "      <arg direction=\"in\" type=\"(i)\" name=\"led\"/>\n"
                "    </method>\n"
                "    <method name=\"setBlinking\">\n"
                "      <arg direction=\"out\" type=\"b\"/>\n"
                "      <annotation value=\"RazerLedId\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
                "      <arg direction=\"in\" type=\"(i)\" name=\"led\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"red\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"green\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"blue\"/>\n"
                "    </method>\n"
                "    <method name=\"setSpectrum\">\n"
                "      <arg direction=\"out\" type=\"b\"/>\n"
                "      <annotation value=\"RazerLedId\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
                "      <arg direction=\"in\" type=\"(i)\" name=\"led\"/>\n"
                "    </method>\n"
                "    <method name=\"setWave\">\n"
                "      <annotation value=\"RazerLedId\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
                "      <arg direction=\"in\" type=\"(i)\" name=\"led\"/>\n"
                "      <annotation value=\"WaveDirection\" name=\"org.qtproject.QtDBus.QtTypeName.In1\"/>\n"
                "      <arg direction=\"in\" type=\"(i)\" name=\"direction\"/>\n"
                "    </method>\n"
                "    <method name=\"setBrightness\">\n"
                "      <arg direction=\"out\" type=\"b\"/>\n"
                "      <annotation value=\"RazerLedId\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
                "      <arg direction=\"in\" type=\"(i)\" name=\"led\"/>\n"
                "      <arg direction=\"in\" type=\"y\" name=\"brightness\"/>\n"
                "    </method>\n"
                "    <method name=\"getBrightness\">\n"
                "      <arg direction=\"out\" type=\"y\"/>\n"
                "      <annotation value=\"RazerLedId\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
                "      <arg direction=\"in\" type=\"(i)\" name=\"led\"/>\n"
                "    </method>\n"
                "  </interface>\n"
                "")
public:
    RazerDeviceAdaptor(QObject *parent);
    virtual ~RazerDeviceAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    uchar getBrightness(RazerLedId led);
    QString getFirmwareVersion();
    QVector<RazerLedId> getLedIds();
    QVector<int> getLedIds2();
    RazerLedId getLedIds3();
    QString getName();
    QString getSerial();
    QString getType();
    bool setBlinking(RazerLedId led, uchar red, uchar green, uchar blue);
    bool setBreathing(RazerLedId led, uchar red, uchar green, uchar blue);
    bool setBreathingDual(RazerLedId led, uchar red, uchar green, uchar blue, uchar red2, uchar green2, uchar blue2);
    bool setBreathingRandom(RazerLedId led);
    bool setBrightness(RazerLedId led, uchar brightness);
    bool setNone(RazerLedId led);
    bool setSpectrum(RazerLedId led);
    bool setStatic(RazerLedId led, uchar red, uchar green, uchar blue);
    void setWave(RazerLedId led, WaveDirection direction);
Q_SIGNALS: // SIGNALS
};

#endif