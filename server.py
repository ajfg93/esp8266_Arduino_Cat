import socket


HOST = '0.0.0.0'
PORT = 12700

catSafeZone = False
serverTimeout = 3

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);
    s.bind((HOST, PORT))
    s.listen()
    print("Start listening")
    print("Device is not conncted")

    while True:
        conn, addr = s.accept()
        try:
            with conn:
                print("Connected by", addr)
                print("Cat is online")
                conn.settimeout(serverTimeout)

                # client won't try to disconnect on its own.
                # So we only need to capture connection timeout exception
                while True:
                    data = conn.recv(128)
                    if data:
                        if catSafeZone == False:
                            catSafeZone = True
                            print("Cat is in safe zone.")
                        conn.send(b'1')
                    else:
                        print("Unexpected condition")
                        print("Client disconnected on its own.")
                        raise Exception("server data NULL")

                    # Code that is used for wifi signal strength detection:
                    #
                    # if not data:
                    #     break
                    # wifiStrength = int.from_bytes(data, byteorder='big', signed=True)
                    # print(wifiStrength)

        except socket.timeout:
            print("!!!Cat is out of safe zone")
            # Warn user in some ways
            catSafeArea = False



# never reach here
print("Server shutdown")