# 소켓 프로그래밍 기본 (Server)

import socket

def server_program():
    host = ''
    port = 10000
    
    server_socket = socket.socket() # 소켓 생성
    server_socket.bind((host,port)) #소켓 API 호출(바인딩)
    server_socket.listen(10) #연결 수신 대기 상태
    

    connect, address = server_socket.accept() #연결 수락
    print("연결 상대: ", str(address)) #연결 상태 확인(IP로 나타냄)
    while True: 
        data = connect.recv(1024).decode() #클라이언트로부터 메세지를 수신

        if not data: #빈 문자열일때까지 반복한다.
            break
        print("연결된 상대: ", str(data)) #연결된 사람의 말(실행해보면 됨)
        data = input(' -> ') #메세지 앞 화살표 표시(실행해보면 됨)
        connect.send(data.encode()) #클라이언트에게 메세지 송신
    connect.close()
    
if __name__ == '__main__':
    server_program()