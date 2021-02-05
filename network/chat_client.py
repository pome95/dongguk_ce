# 소켓 프로그래밍 기본 (Client)

import socket

def client_program():
    host = '127.0.0.1'
    port = 10000

    client_socket = socket.socket() #서버에 접속 하기 위한 소켓을 생성
    client_socket.connect((host, port)) #소켓 API 호출(바인딩)

    message = input(' -> ') #메세지 앞 화살표 표시(실행시 나옴)

    while message.lower().strip() != 'bye': #bye입력시 종료
        client_socket.send(message.encode()) #서버로부터 메세지 수신
        data = client_socket.recv(1024).decode() #서버로 메세지 송신

        print('서버로부터 응답: ',data) #서버의 말(실행해보면 됨)

        message = input(' -> ') #메세지 앞 화살표 표시
    client_socket.close() 

if __name__ == '__main__':
    client_program()