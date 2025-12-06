import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 1628

def main():
    try:
        while True:
            lua_code = input("Bleed> ")
            if not lua_code:
                break

            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.connect((SERVER_IP, SERVER_PORT))
            sock.sendall(lua_code.encode("utf-8"))

            buffer = b""
            while True:
                chunk = sock.recv(4096)
                if not chunk:
                    break
                buffer += chunk

            try:
                print("string: ",buffer.decode("utf-8").rstrip())
            except:
                pass

            print("==============================================")
            print("buffer:  ",buffer.hex(" "))

            sock.close()

    except KeyboardInterrupt:
        print("\nExiting client...")

if __name__ == "__main__":
    main()
