/*
 * Copyright (c) 2015 WinT 3794 <http://wint3794.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

//=============================================================================
// System includes
//=============================================================================

#include <QList>

//=============================================================================
// Library includes
//=============================================================================

#include "LibDS/Core/ProtocolBase.h"
#include "LibDS/Core/ProtocolManager.h"

//=============================================================================
// DS_ProtocolManager::DS_ProtocolManager
//=============================================================================

DS_ProtocolManager::DS_ProtocolManager()
{
    m_protocol = Q_NULLPTR;
    m_joysticks = new QList<DS_Joystick*>;
}

//=============================================================================
// DS_ProtocolManager::~DS_ProtocolManager
//=============================================================================

DS_ProtocolManager::~DS_ProtocolManager()
{
    delete m_protocol;
    delete m_joysticks;
}

//=============================================================================
// DS_ProtocolManager::currentProtocol
//=============================================================================

DS_ProtocolBase* DS_ProtocolManager::currentProtocol() const
{
    return isValid() ? m_protocol : Q_NULLPTR;
}

//=============================================================================
// DS_ProtocolManager::isValid
//=============================================================================

bool DS_ProtocolManager::isValid() const
{
    return (m_protocol != Q_NULLPTR);
}

//=============================================================================
// DS_ProtocolManager::joystickCount
//=============================================================================

int DS_ProtocolManager::joystickCount() const
{
    return isValid() ? currentProtocol()->joysticks()->count() : 0;
}

//=============================================================================
// DS_ProtocolManager::setProtocol
//=============================================================================

void DS_ProtocolManager::setProtocol (DS_ProtocolBase* protocol)
{
    if (protocol != Q_NULLPTR)
        {
            delete m_protocol;
            m_protocol = protocol;
            m_protocol->setJoysticks (m_joysticks);

            connect (m_protocol, SIGNAL (emergencyStopped       (void)),
                     this,       SIGNAL (emergencyStopped       (void)));
            connect (m_protocol, SIGNAL (codeChanged            (bool)),
                     this,       SIGNAL (codeChanged            (bool)));
            connect (m_protocol, SIGNAL (radioCommChanged       (bool)),
                     this,       SIGNAL (radioCommChanged       (bool)));
            connect (m_protocol, SIGNAL (communicationsChanged  (DS_CommStatus)),
                     this,       SIGNAL (communicationsChanged  (DS_CommStatus)));
            connect (m_protocol, SIGNAL (robotAddressChanged    (QString)),
                     this,       SIGNAL (robotAddressChanged    (QString)));
            connect (m_protocol, SIGNAL (controlModeChanged     (DS_ControlMode)),
                     this,       SIGNAL (controlModeChanged     (DS_ControlMode)));
            connect (m_protocol, SIGNAL (diskUsageChanged       (int)),
                     this,       SIGNAL (diskUsageChanged       (int)));
            connect (m_protocol, SIGNAL (ramUsageChanged        (int)),
                     this,       SIGNAL (ramUsageChanged        (int)));
            connect (m_protocol, SIGNAL (cpuUsageChanged        (int)),
                     this,       SIGNAL (cpuUsageChanged        (int)));
            connect (m_protocol, SIGNAL (voltageChanged         (QString)),
                     this,       SIGNAL (voltageChanged         (QString)));
            connect (m_protocol, SIGNAL (voltageBrownoutChanged (bool)),
                     this,       SIGNAL (voltageBrownoutChanged (bool)));
            connect (m_protocol, SIGNAL (CANInfoReceived        (DS_CAN)),
                     this,       SIGNAL (CANInfoReceived        (DS_CAN)));
            connect (m_protocol, SIGNAL (fmsChanged             (bool)),
                     this,       SIGNAL (fmsChanged             (bool)));

            m_protocol->setRobotAddress ("127.0.0.1");
        }
}

//=============================================================================
// DS_ProtocolManager::resetJoysticks
//=============================================================================

void DS_ProtocolManager::resetJoysticks()
{
    m_joysticks->clear();

    if (isValid())
        currentProtocol()->onJoysticksChanged();
}

//=============================================================================
// DS_ProtocolManager::addJoystick
//=============================================================================

void DS_ProtocolManager::addJoystick (int axes, int buttons, int POVs)
{
    DS_Joystick* js = new DS_Joystick;

    js->numAxes = axes;
    js->numPOVs = POVs;
    js->numButtons = buttons;

    js->axes = new double  [axes];
    js->POVs = new int  [POVs];
    js->buttons = new bool [buttons];

    for (int i = 0; i < js->numAxes; i++)
        js->axes [i] = 0;

    for (int i = 0; i < js->numPOVs; i++)
        js->POVs [i] = -1;

    for (int i = 0; i < js->numButtons; i++)
        js->buttons [i] = false;

    m_joysticks->append (js);

    if (isValid())
        currentProtocol()->onJoysticksChanged();
}

//=============================================================================
// DS_ProtocolManager::updateJoystickPOV
//=============================================================================

void DS_ProtocolManager::updateJoystickPOV (int js, int hat, int angle)
{
    if (joystickExists (js))
        m_joysticks->at (js)->POVs [hat] = angle;
}

//=============================================================================
// DS_ProtocolManager::updateJoystickAxis
//=============================================================================

void DS_ProtocolManager::updateJoystickAxis (int js, int axis, double value)
{
    if (joystickExists (js))
        m_joysticks->at (js)->axes [axis] = value;
}

//=============================================================================
// DS_ProtocolManager::updateJoystickButton
//=============================================================================

void DS_ProtocolManager::updateJoystickButton (int js, int bt, bool status)
{
    if (joystickExists (js))
        m_joysticks->at (js)->buttons [bt] = status;
}

//=============================================================================
// DS_ProtocolManager::readRobotPacket
//=============================================================================

void DS_ProtocolManager::readRobotPacket (QByteArray data)
{
    if (isValid())
        currentProtocol()->readRobotPacket (data);
}

//=============================================================================
// DS_ProtocolManager::joystickExists
//=============================================================================

bool DS_ProtocolManager::joystickExists (int js) const
{
    return (js < m_joysticks->count());
}
