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

#include "LibDS/Core/Discovery/Discovery.h"

//=============================================================================
// NetworkDiscovery::NetworkDiscovery
//=============================================================================

NetworkDiscovery::NetworkDiscovery()
{
    connect (&m_responder, SIGNAL (IpFound (QString, QString)),
             this,         SIGNAL (IpFound (QString, QString)));
}

//=============================================================================
// NetworkDiscovery::GetAddressType
//=============================================================================

NetworkDiscovery::AddressType NetworkDiscovery::GetAddressType (
    QString address)
{
    if (address.endsWith (".local", Qt::CaseInsensitive))
        return kMDNS;

    if (QHostAddress (address).protocol() == QAbstractSocket::IPv4Protocol)
        return kIPv4;

    if (QHostAddress (address).protocol() == QAbstractSocket::IPv6Protocol)
        return kIPv6;

    return kUnknown;
}

//=============================================================================
// NetworkDiscovery::GetIP
//=============================================================================

void NetworkDiscovery::GetIP (QString address)
{
    GetIP (address, GetAddressType (address));
}

//=============================================================================
// NetworkDiscovery::GetIP
//=============================================================================

void NetworkDiscovery::GetIP (QString address, AddressType type)
{
    switch (type)
        {
        case kMDNS:
            m_responder.Query (address);
            break;
        case kIPv4:
            emit IpFound (address, address);
            break;
        case kIPv6:
            emit IpFound (address, address);
            break;
        default:
            QHostInfo::lookupHost (address, this,
                                   SLOT (OnLookupFinished (QHostInfo)));
            break;
        }
}

//=============================================================================
// NetworkDiscovery::OnLookupFinished
//=============================================================================

void NetworkDiscovery::OnLookupFinished (QHostInfo info)
{
    for (int i = 0; i < info.addresses().count(); ++i)
        {
            QString ip = info.addresses().at (i).toString();

            if (GetAddressType (ip) == kIPv4 || GetAddressType (ip) == kIPv6)
                {
                    emit IpFound (info.hostName(), ip);
                    return;
                }
        }
}
