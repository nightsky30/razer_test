/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2018-2019  Luca Weiss <luca@z3ntu.xyz>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bringuputil.h"
#include "../validjsonvalues.h"
#include "../device/razerclassicdevice.h"
#include "../device/razermatrixdevice.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

#include <iostream>

BringupUtil::BringupUtil(struct hid_device_info *hid_dev_info)
    : hid_dev_info(hid_dev_info)
{
}

BringupUtil::BringupUtil(RazerDevice *device)
    : device(device)
{
}

const QVector<QVector<RazerDeviceQuirks>> quirksCombinations {
    {},
    { RazerDeviceQuirks::MouseMatrix },
    { RazerDeviceQuirks::MouseMatrix, RazerDeviceQuirks::MatrixBrightness },
    { RazerDeviceQuirks::MatrixBrightness }
};

RazerDevice *BringupUtil::tryDevice(QString pclass, QVector<razer_test::RazerLedId> ledIds, QStringList fx, QVector<RazerDeviceQuirks> quirks)
{
    RazerDevice *device;
    if (pclass == "classic") {
        device = new RazerClassicDevice(hid_dev_info->path, hid_dev_info->vendor_id, hid_dev_info->product_id, /*name*/ "", /*type*/ "", ledIds, fx, validFeatures, quirks, /*dims*/ {}, /*maxDPI*/ 0);
    } else if (pclass == "matrix") {
        device = new RazerMatrixDevice(hid_dev_info->path, hid_dev_info->vendor_id, hid_dev_info->product_id, /*name*/ "", /*type*/ "", ledIds, fx, validFeatures, quirks, /*dims*/ {}, /*maxDPI*/ 0);
    } else {
        qFatal("Unhandled pclass in BringupUtil::tryDevice");
        return nullptr;
    }

    if (!device->openDeviceHandle()) {
        qCritical("Failed to open device handle.");
        qCritical("You can give your current user permissions to access the hidraw nodes with the following commands:");
        qCritical("$ sudo chmod g+rw /dev/hidraw*");
        qCritical("$ sudo chgrp $(id -g) /dev/hidraw*");
        qFatal("Exiting now.");
    }
    if (!device->initialize()) {
        qWarning("Failed to initialize device.");
        delete device;
        return nullptr;
    }
    qInfo("Successfully initialized LEDs.");
    return device;
}

bool BringupUtil::newDevice()
{
    QTextStream cin(stdin);

    QString input;
    bool inputValid = true;

    QString name;
    QString vid;
    QString pid;
    QString type;

    qInfo("== razer_test bringup util ==");
    name = QString::fromWCharArray(hid_dev_info->product_string);
    qInfo("Product: %s", qUtf8Printable(name));
    vid = QString::number(hid_dev_info->vendor_id, 16).rightJustified(4, '0');
    qInfo("VID: %s", qUtf8Printable(vid));
    pid = QString::number(hid_dev_info->product_id, 16).rightJustified(4, '0');
    qInfo("PID: %s", qUtf8Printable(pid));
    qInfo("Do you want to bring up this new device? (y/N)");
    std::cout << "> ";
    input = cin.readLine();
    if (input.compare("y", Qt::CaseInsensitive) != 0) {
        qInfo("Exiting bringup util.");
        return false;
    }

    QVector<RazerLedId> ledIds = {};
    QStringList features = {};
    MatrixDimensions dims = {};
    ushort maxDPI = 0;

    QString pclass;
    QVector<RazerDeviceQuirks> quirks;

    for (const QString &pclass_try : validPclass) {
        for (QVector<RazerDeviceQuirks> quirks_try : quirksCombinations) {
            device = tryDevice(pclass_try, /*FIXME allLedIds*/ { RazerLedId::LogoLED }, minimalFx, quirks_try);
            if (device == nullptr)
                continue;

            // Save the values that have worked
            pclass = pclass_try;
            quirks = quirks_try;

            RazerDevice *rgbDevice = tryDevice(pclass_try, allLedIds, validFx, quirks_try);
            if (rgbDevice == nullptr) {
                qInfo("Device seems incapable of RGB effects, ignore the warnings above.");
                deviceHasRgb = false;
            } else {
                delete device;
                device = rgbDevice;
                deviceHasRgb = true;
            }
            // Exit the loop
            goto device_valid;
        }
    }
    if (device == nullptr) {
        qCritical("Tried all quirks and pclasses and none worked. Exiting");
        return true;
    }

device_valid:
    for (auto led : device->getLeds()) {
        led->setOff();
    }
    qInfo("Now all LEDs should be off. Is that correct? (y/N)");
    std::cout << "> ";
    input = cin.readLine();
    if (input.compare("y", Qt::CaseInsensitive) != 0) {
        qCritical("That's bad :( Exiting for now (TODO: Test out existing quirks if they help)"); // TODO
        return true;
    }

    // Try setStatic if the device has RGB, otherwise setOn
    for (auto led : device->getLeds()) {
        const char *effectDesc;
        if (deviceHasRgb) {
            led->setStatic({ 0xFF, 0xFF, 0x00 });
            effectDesc = "yellow";
        } else {
            led->setOn();
            effectDesc = "on";
        }
        qInfo("Did a LED just turn %s (tried %s)? (y/N)", effectDesc, qUtf8Printable(LedIdToString.value(led->getLedId())));
        std::cout << "> ";
        input = cin.readLine();
        if (input.compare("y", Qt::CaseInsensitive) == 0) {
            ledIds.append(led->getLedId());
        }
        led->setOff();
    }

    if (ledIds.isEmpty()) {
        qInfo("You said that no LED is supported. Exiting. TODO: quirks"); // TODO
        return true;
    } else if (ledIds.size() == allLedIds.size()) {
        qInfo("You said that all LEDs do something. This is most likely not true. If the same zone is always lighting up, please choose only 'backlight'. Exiting.");
        return true;
    }

    // == TYPE ==
    do {
        qInfo("What is your device type?");
        qInfo("Valid types: ");
        for (auto value : validType)
            qInfo("- %s", qUtf8Printable(value));
        std::cout << "> ";
        type = cin.readLine();
        if (!validType.contains(type)) {
            qCritical("Invalid device type.");
            inputValid = false;
        } else {
            inputValid = true;
        }
    } while (!inputValid);

    // Reinitialize device with figured-out ledIds
    // Get set FX to deduplicate the logic above with non-RGB vs RGB devices
    QStringList fxInUse = device->getSupportedFx();
    delete device;
    device = tryDevice(pclass, ledIds, fxInUse, quirks);
    if (device == nullptr) {
        qCritical("Re-initialized device with new Led IDs and failed.");
        qFatal("Exiting now.");
    }

    // == FX ==
    QVector<RazerEffect> fxVec = testLedEffects(device);

    // == FEATURES ==
    if (type == "mouse") {
        // == MAX DPI ==
        QString maxDPIstr;
        do {
            qInfo("What's the maximum DPI of the mouse (e.g. 16000)?");
            std::cout << "> ";
            maxDPIstr = cin.readLine();
            maxDPI = maxDPIstr.toUInt(nullptr, 10);
            if (maxDPI == 0) {
                qCritical("Invalid DPI.");
                inputValid = false;
            } else {
                inputValid = true;
            }
        } while (!inputValid);

        // == DPI ==
        if (testDPI(device)) {
            features.append("dpi");
        } else {
            // Try the ByteDPI quirk
            qInfo("Normal DPI check failed, trying ByteDPI quirk...");
            QVector<RazerDeviceQuirks> quirksNew = QVector<RazerDeviceQuirks>(quirks);
            quirksNew.append(RazerDeviceQuirks::ByteDPI);
            RazerDevice *deviceNew = tryDevice(pclass, ledIds, fxInUse, quirksNew);
            if (testDPI(deviceNew)) {
                delete device;
                device = deviceNew;
                quirks = quirksNew;
                features.append("dpi");
            } else {
                delete deviceNew;
                qCritical("Your device is a mouse but seems to not support DPI!");
            }
        }

        // == POLL RATE ==
        if (testPollRate(device)) {
            features.append("poll_rate");
        } else {
            qCritical("Your device is a mouse but seems to not support Poll Rate!");
        }
    }

    if (type == "keyboard") {
        // == KEYBOARD LAYOUT ==
        if (testKeyboardLayout(device))
            features.append("keyboard_layout");
    }

    // Convert to QJsonArray
    QJsonArray ledIdsJson;
    for (auto ledId : ledIds)
        ledIdsJson.append(static_cast<uchar>(ledId));
    QJsonArray fxJson;
    for (auto fx : fxVec)
        fxJson.append(EffectToString.value(fx));
    QJsonArray featuresJson = QJsonArray::fromStringList(features);
    QJsonArray quirksJson;
    for (auto quirk : quirks)
        quirksJson.append(QuirksToString.value(quirk));
    QJsonArray dimsJson = { dims.x, dims.y };

    QJsonObject deviceObj {
        { "name", name },
        { "vid", vid },
        { "pid", pid },
        { "type", type },
        { "pclass", pclass },
        { "leds", ledIdsJson },
        { "fx", fxJson },
        { "features", featuresJson },
        { "quirks", quirksJson },
        { "matrix_dimensions", dimsJson }, // TODO
        { "max_dpi", maxDPI }
    };

    // Remove unnecessary entries
    if (type != "mouse")
        deviceObj.remove("max_dpi");
    if (quirksJson.isEmpty())
        deviceObj.remove("quirks");

    QJsonDocument doc(deviceObj);
    QString jsonString = doc.toJson(QJsonDocument::Indented);
    qInfo("%s", qUtf8Printable(jsonString));

    return true;
}

bool BringupUtil::testDPI(RazerDevice *device)
{
    if (!device->checkFeature("dpi")) {
        qInfo("Skip testDPI because the device doesn't have the feature.");
        return true; // unsupported
    }
    auto dpi = device->getDPI();
    if (dpi.dpi_x == 0 && dpi.dpi_y == 0) {
        qInfo("Failed to get current DPI.");
        return false;
    }
    qInfo("The current DPI is: %hu - %hu", dpi.dpi_x, dpi.dpi_y);
    RazerDPI newDPI = { 500, 600 };
    device->setDPI(newDPI);
    auto dpi2 = device->getDPI();
    if (dpi2.dpi_x != newDPI.dpi_x || dpi2.dpi_y != newDPI.dpi_y) {
        qInfo("Failed setting DPI. A: %hu - %hu, B: %hu - %hu", newDPI.dpi_x, newDPI.dpi_y, dpi2.dpi_x, dpi2.dpi_y);
        return false;
    }
    // Reset DPI back
    device->setDPI(dpi);
    return true;
}

bool BringupUtil::testPollRate(RazerDevice *device)
{
    if (!device->checkFeature("poll_rate")) {
        qInfo("Skip testPollRate because the device doesn't have the feature.");
        return true; // unsupported
    }
    auto pollRate = device->getPollRate();
    if (pollRate == 0) {
        qInfo("Failed to get current poll rate.");
        return false;
    }
    qInfo("The current poll rate is: %hu", pollRate);
    ushort newPollRate;
    if (pollRate == 1000)
        newPollRate = 500;
    else
        newPollRate = 1000;
    device->setPollRate(newPollRate);
    auto pollRate2 = device->getPollRate();
    if (pollRate2 != newPollRate) {
        qInfo("Failed setting poll rate. A: %hu, B: %hu", newPollRate, pollRate2);
        return false;
    }
    // Reset poll rate back
    device->setPollRate(pollRate);
    return true;
}

bool BringupUtil::testBrightness(RazerDevice *device)
{
    if (!device->checkFx("brightness")) {
        qInfo("Skip testBrightness because the device doesn't have the feature.");
        return true; // unsupported
    }
    for (auto led : device->getLeds()) {
        auto brightness = led->getBrightness();
        qInfo("The current brightness on LED %s is: %hhu", qUtf8Printable(LedIdToString.value(led->getLedId())), brightness);
        uchar newBrightness;
        if (brightness > 0x80)
            newBrightness = 0x40;
        else
            newBrightness = 0xFF;
        led->setBrightness(newBrightness);
        auto brightness2 = led->getBrightness();
        if (brightness2 != newBrightness) {
            qInfo("Failed setting brightness. A: %hhu, B: %hhu", newBrightness, brightness2);
            return false;
        }
        // Reset poll rate back
        led->setBrightness(brightness);
    }
    return true;
}

bool BringupUtil::testKeyboardLayout(RazerDevice *device)
{
    if (!device->checkFeature("keyboard_layout")) {
        qInfo("Skip testKeyboardLayout because the device doesn't have the feature.");
        return true; // unsupported
    }
    auto layout = device->getKeyboardLayout();
    if (layout == "error") {
        qInfo("Failed to determine keyboard layout.");
        return false;
    } else if (layout == "unknown") {
        qInfo("Failed to determine keyboard layout. Either yours is unknown (you can get the ID output when you use the --verbose parameter) or your device doesn't support this call.");
        return false;
    } else {
        qInfo("Your keyboard layout is: %s", qUtf8Printable(layout));
        return true;
    }
}

QVector<RazerEffect> BringupUtil::testLedEffects(RazerDevice *device)
{
    QTextStream cin(stdin);

    QString input;
    QVector<RazerEffect> workingEffects;

    for (auto led : device->getLeds()) {
        qInfo("Checking functionality of LED '%s'", qUtf8Printable(LedIdToString.value(led->getLedId())));
        auto currEffect = led->getCurrentEffect();
        auto currColors = led->getCurrentColors();
        for (auto effectStr : device->getSupportedFx()) {
            if (effectStr == "custom_frame" || effectStr == "brightness")
                continue;
            RazerEffect effect = StringToEffect.value(effectStr);
            setEffect(led, effect, { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 });
            qInfo("Effect %s should be active now. Is that correct? (y/N)", qUtf8Printable(effectStr));
            std::cout << "> ";
            input = cin.readLine();
            if (input.compare("y", Qt::CaseInsensitive) == 0) {
                workingEffects.append(effect);
            }
        }
        if (currColors.size() <= 2) // should never happen
            currColors = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 } };
        setEffect(led, currEffect, currColors.at(0), currColors.at(1), currColors.at(2));
    }
    return workingEffects;
}

bool BringupUtil::setEffect(RazerLED *led, RazerEffect effect, RGB color1, RGB color2, RGB color3)
{
    Q_UNUSED(color3)
    if (effect == RazerEffect::Off) {
        led->setOff();
    } else if (effect == RazerEffect::On) {
        led->setOn();
    } else if (effect == RazerEffect::Static) {
        led->setStatic(color1);
    } else if (effect == RazerEffect::Blinking) {
        led->setBlinking(color1);
    } else if (effect == RazerEffect::Breathing) {
        led->setBreathing(color1);
    } else if (effect == RazerEffect::BreathingDual) {
        led->setBreathingDual(color1, color2);
    } else if (effect == RazerEffect::BreathingRandom) {
        led->setBreathingRandom();
    } else if (effect == RazerEffect::Spectrum) {
        led->setSpectrum();
    } else if (effect == RazerEffect::Wave) {
        led->setWave(WaveDirection::LEFT_TO_RIGHT);
    } else if (effect == RazerEffect::Reactive) {
        led->setReactive(ReactiveSpeed::_1000MS, color1);
    } else {
        qFatal("Unhandled effect %s at %s", qUtf8Printable(EffectToString.value(effect)), Q_FUNC_INFO);
        return false;
    }
    return true;
}
