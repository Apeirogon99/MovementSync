#include <SDL.h>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

#include "Common/Math/Vector2f.h"
#include "Common/AStar/PathFinding.h"

#include "World.h"

using boost::asio::ip::udp;
using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	PathFinding pf;
	auto path = pf.FindPath({ 0,0 }, { 0, 100 });

	for (Node* node : path)
	{
		printf("(%f, %f)\n", node->mPosition.x, node->mPosition.y);
	}

	World world; 
	world.Initialize();

	world.Run();

	world.Destroy();

	return 0;
}

//int main(int argc, char* argv[])
//{
//    try {
//        std::cout << "=== 데드레커닝 클라이언트 테스트 ===" << std::endl;
//
//        // SDL 초기화
//        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//            std::cout << "SDL 초기화 실패: " << SDL_GetError() << std::endl;
//            return 1;
//        }
//
//        std::cout << "SDL 초기화 성공!" << std::endl;
//
//        // Boost.Asio 초기화 테스트
//        boost::asio::io_context io_context;
//
//        // UDP 소켓 생성 테스트 (빠른 위치 업데이트용)
//        udp::socket udp_socket(io_context);
//        std::cout << "UDP 소켓 생성 성공!" << std::endl;
//
//        // TCP 소켓 생성 테스트 (중요한 이벤트용)
//        tcp::socket tcp_socket(io_context);
//        std::cout << "TCP 소켓 생성 성공!" << std::endl;
//
//        // 간단한 창 생성 테스트
//        SDL_Window* window = SDL_CreateWindow(
//            "데드레커닝 클라이언트",
//            SDL_WINDOWPOS_CENTERED,
//            SDL_WINDOWPOS_CENTERED,
//            800, 600,
//            SDL_WINDOW_SHOWN
//        );
//
//        if (!window) {
//            std::cout << "창 생성 실패: " << SDL_GetError() << std::endl;
//            SDL_Quit();
//            return 1;
//        }
//
//        std::cout << "SDL 창 생성 성공!" << std::endl;
//        std::cout << "모든 라이브러리가 정상적으로 작동합니다!" << std::endl;
//        std::cout << "\n클라이언트가 준비되었습니다. 5초 후 종료됩니다..." << std::endl;
//
//        // 5초 대기
//        std::this_thread::sleep_for(std::chrono::seconds(5));
//
//        // 정리
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//
//        return 0;
//
//    }
//    catch (std::exception& e) {
//        std::cout << "오류 발생: " << e.what() << std::endl;
//        SDL_Quit();
//        return 1;
//    }
//}