#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Session.h"

#include <QQuickView>
#include <QObject>

#include <boost/beast/core.hpp>
#include <boost/thread.hpp>

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace net = boost::asio;

class ChatClient:public QObject
{
public:
    Q_OBJECT
public:
    ChatClient()
    {
        m_mainView = nullptr;
        m_rootObject = nullptr;
        m_session = nullptr;
    }
    ~ChatClient()
    {

    }

    static ChatClient& getInstance();

    QQuickWindow* GetWindow() { return m_mainView; }
    QObject* GetObject() { return m_rootObject; }

    void SetWindow(QQuickWindow* pWindow) { m_mainView = pWindow; }
    void SetObject(QObject* pObject) { m_rootObject = pObject; }

    void CallQmlFuncPrintMessage(std::string pStringValue);

    Q_INVOKABLE void cppFuncConnect(QString pIpPort);
    Q_INVOKABLE void cppFuncSend(QString stringData);
    Q_INVOKABLE void cppFuncDisconnect();
private:

    QQuickWindow* m_mainView;
    QObject* m_rootObject;
    std::shared_ptr<Session> m_session;

    void Connect(std::string pIp, std::string pPort);
    void Send(std::string pMessage);
    void Disconnect();
};

