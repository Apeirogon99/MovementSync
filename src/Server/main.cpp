#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using boost::asio::ip::udp;
using boost::asio::ip::tcp;

int main()
{
    try {
        std::cout << "=== 데드레커닝 서버 테스트 ===" << std::endl;

        // Boost.Asio 초기화
        boost::asio::io_context io_context;

        // UDP 서버 소켓 생성 테스트 (빠른 위치 업데이트 수신용)
        udp::socket udp_server(io_context, udp::endpoint(udp::v4(), 12345));
        std::cout << "UDP 서버 소켓 생성 성공! (포트: 12345)" << std::endl;

        // TCP 서버 소켓 생성 테스트 (중요한 이벤트 수신용)
        tcp::acceptor tcp_acceptor(io_context, tcp::endpoint(tcp::v4(), 12346));
        std::cout << "TCP 서버 소켓 생성 성공! (포트: 12346)" << std::endl;

        std::cout << "네트워크 소켓들이 정상적으로 생성되었습니다!" << std::endl;
        std::cout << "\n서버가 준비되었습니다." << std::endl;
        std::cout << "데드레커닝 시스템 구현 준비 완료!" << std::endl;
        std::cout << "5초 후 종료됩니다..." << std::endl;

        // 5초 대기
        std::this_thread::sleep_for(std::chrono::seconds(5));

        return 0;

    }
    catch (std::exception& e) {
        std::cout << "서버 오류 발생: " << e.what() << std::endl;
        return 1;
    }
}