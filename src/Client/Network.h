#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include <queue>
#include <unordered_set>

#include "Common/Protocol/Message.h"

class Network
{
public:
    Network(const std::string& Host, const uint16_t Port);
    ~Network();

public:
    bool Initialize();
    void Destroy();

public:
    void Connect();
    void Disconnect();

    void Write(std::unique_ptr<Message> Message);
    void PollMessage();

public:
    inline bool IsConnected() const { return mIsConnected; }

public:
    void SetMessageHandler(std::function<void(std::unique_ptr<Message>)> Handler)
    {
        mMessageHandler = Handler;
    }

    void SetConnectHandler(std::function<void()> Handler)
    {
        mConnectHandler = Handler;
    }

    void SetDisconnectHandler(std::function<void(boost::system::error_code&)> Handler)
    {
        mDisconnectHandler = Handler;
    }

private:
    void ReadAsync();
    void WriteAsync();

private:
    bool mIsConnected;

    std::thread mNetworkThread;
    boost::asio::io_context mContext;
    boost::asio::ip::tcp::socket mSocket;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> mWorkGuard;

    std::string mHost;
    uint16_t mPort;

    // Read, Write
    std::array<BYTE, 8192> mRecvBuffer;
    std::size_t mRecvBufferCount;
    std::unordered_set<std::unique_ptr<Message>> mRecvMessages;
    std::mutex mRecvMutex;

    std::queue<std::unique_ptr<Message>> mWriteQueue;
    std::mutex mWriteMutex;

    // Handler
    std::function<void(std::unique_ptr<Message>)> mMessageHandler;
    std::function<void()> mConnectHandler;
    std::function<void(boost::system::error_code&)> mDisconnectHandler;
};
