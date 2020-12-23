# ChatProgram

디렉토리(프로젝트)설명

    - ChatServer
        = 서버 프로그램(https://www.boost.org/doc/libs/1_75_0/libs/beast/example/websocket/server/chat-multi/)

    - ChatClient_QT
        = 클라이언트 프로그램(https://www.boost.org/doc/libs/1_75_0/libs/beast/example/websocket/client/async/websocket_client_async.cpp 참조)
        = UI: QT(QML)로 구현
        = 모든 기능은 Visual Studio 2019 (c++) IDE 로만 구현(qt라이브러리 연동)
        = 오픈소스 라이브러리 사용(boost[ver:1.75.0], qt[ver:5.15.2])
        = 웹소켓, json사용
        = json 메시지 형태는 { "message":"[메시지 전송 시간] 발신자이름 : 메시지" }
        = 연동기능은 오로지 C++로만 구현

    - bin : 실행파일 배포용 폴더
        = 프로그램 구동 관련.pdf 참고

참고문서

    https://www.boost.org/doc/libs/1_75_0/libs/beast/doc/html/beast/using_websocket.html
    https://www.boost.org/doc/libs/1_75_0/libs/json/doc/html/index.html
    https://www.boost.org/doc/libs/1_75_0/doc/html/date_time.html
    https://www.boost.org/doc/libs/1_75_0/doc/html/thread.html
    https://www.boost.org/doc/libs/1_65_1/doc/html/property_tree/parsers.html#property_tree.parsers.json_parser

