#include "Game.h"
#include "ClientMessageHandler.h"
#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Initialize()
{
	mWorld = std::make_unique<World>();
	if (!mWorld->Initialize())
	{
		return false;
	}

	//boost::asio::io_context context;
	//mNetwork = std::make_unique<Network>(context, "localhost", 9000);
	//if (!mNetwork && !mNetwork->Initialize())
	//{
	//	return false;
	//}

	//mNetwork->SetMessageHandler([&](std::unique_ptr<Message>& Message)
	//	{
	//		std::cout << "Received" << std::endl;
	//		ClientMessageHandler::ProcessMessage(mWorld, Message);
	//	});

	//mNetwork->SetConnectHandler([&]()
	//	{
	//		std::cout << "Connected to server" << std::endl;
	//	});

	//mNetwork->SetDisconnectHandler([&](boost::system::error_code ec)
	//	{
	//		std::cout << "Disconnected from server : " << ec.message() << std::endl;
	//		mNetwork->Disconnect();
	//	});

	return true;
}

void Game::Destroy()
{
	if (mWorld)
	{
		mWorld->Destroy();
	}

	if (mNetwork)
	{
		mNetwork->Destroy();
	}
}

void Game::Run()
{
	//while (mNetwork->IsConnected() && mWorld->IsRunning())
	//{
	//	mWorld->HandleEvents();

	//	mNetwork->PollMessage();

	//	mWorld->Update();

	//	mWorld->Render();

	//	mWorld->LimitFrameRate();
	//}

	while (mWorld->IsRunning())
	{
		mWorld->HandleEvents();

		mWorld->Update();

		mWorld->Render();

		//mWorld->LimitFrameRate();
	}

	Stop();
}

void Game::Stop()
{
	Destroy();
}
