#include "ChatClient.h"

ChatClient& ChatClient::getInstance()
{
    static ChatClient* mpInstance;
    if (mpInstance == nullptr) {
        mpInstance = new ChatClient();
    }
    return *mpInstance;
}

void ChatClient::CallQmlFuncPrintMessage(std::string pMessage)
{
    QString stringValue = pMessage.c_str();
    QMetaObject::invokeMethod(getInstance().GetObject(), "qmlFuncPrintMessage", Q_ARG(QVariant, stringValue));

    return;
}

void ChatClient::cppFuncConnect(QString pIpPort)
{
    auto ip = pIpPort.split(":")[0].toStdString();
    auto port = pIpPort.split(":")[1].toStdString();

    boost::thread th = boost::thread(boost::bind(&ChatClient::Connect, this, ip, port));

    return;
}

void ChatClient::cppFuncSend(QString pMessage)
{
    auto message = pMessage.toStdString();

    Send(message);

    return;
}

void ChatClient::cppFuncDisconnect()
{
    Disconnect();

    return;
}

void ChatClient::Connect(std::string pIp, std::string pPort)
{
    net::io_context m_ioc;

    m_session = std::make_shared<Session>(m_ioc);
    m_session->Run(pIp, pPort, std::bind(&ChatClient::CallQmlFuncPrintMessage, this, std::placeholders::_1));
    m_ioc.run();
    m_session = nullptr;

    return;
}

void ChatClient::Send(std::string pMessage)
{
    if (m_session == nullptr) {
        CallQmlFuncPrintMessage("not connected!!!!");
        return;
    }
    m_session->Send(pMessage);

    return;
}

void ChatClient::Disconnect()
{
    if (m_session == nullptr) {
        CallQmlFuncPrintMessage("not connected!!!!");
        return;
    }
    m_session->Close();

    return;
}
