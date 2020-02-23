// cluelessServer.cpp : 
// to test without a client around: in a command prompt on another system, type nc <serverAddr> 1337
//

#ifdef __WIN
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #include <time.h>

  #pragma comment(lib, "ws2_32.lib")

#else
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <sys/select.h>        // for select API,  According to POSIX.1-2001 
  #include <errno.h>
  #include <string.h>
#endif

#include <stdio.h>
#include <iostream>

const char defServer[] = { "192.168.1.19" };
const unsigned short defPort = 1337;

bool initWinSock();  // for windows only...need to initialize the socket subsystem
int  getLastError(); // windows -- wrapper aound WSAGetLastError; linux -- returns errno.

int main()
{
    int                 sockfd, connfd;
    unsigned int        len;
    struct sockaddr_in  servAddr, cliAddr;
    int                 nRet;

    // TODO : process command line arguments...only use default if necessary.

    if (initWinSock())
    {
        if (-1 != (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
        {
            memset((void*)&servAddr, 0, sizeof(struct sockaddr_in));

            servAddr.sin_family = AF_INET;
            servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
            servAddr.sin_port = htons(defPort);

            if (0 == (nRet = bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr))))
            {
                if (0 == listen(sockfd, 5))
                {
                    bool bRun = true;
                    int  ret;                          // return value from select
                    len = sizeof(cliAddr);
                    fd_set         rdfs;               // input descriptor to listen on...
                    struct timeval tv;

                    while (bRun)                       // enter our infinite loop...
                    {
                        FD_ZERO(&rdfs);
                        FD_SET(0, &rdfs);                  // monitor on stdin to see if we have input
                        FD_SET(sockfd, &rdfs);             // monitor our listening socket for input

                        tv.tv_sec = 5;                 // set timeout for 5 sec
                        tv.tv_usec = 0;

                        ret = select(sockfd + 1, &rdfs, nullptr, nullptr, &tv);
                        if (-1 == ret)
                        {
                            std::cerr << "select failed" << std::endl;
                            bRun = false;
                        }
                        else if (ret > 0)
                        {
                            if (FD_ISSET(0, &rdfs))            // data on stdin
                            {
                                char chIn = getchar();
                                if (chIn == 'q')
                                    bRun = false;
                            }
                            else if (FD_ISSET(sockfd, &rdfs))   // data on listening socket
                            {
						        if (0 < (connfd = accept(sockfd, (struct sockaddr*)&cliAddr, (int*)&len)))
						        {
							        // TODO : process client connection, pass around connfd
							        std::cout << "got a connection" << std::endl;
						        }
						        else
						        {
							        std::cerr << "failed to accept connect, error: " << getLastError() << std::endl;
                                    bRun = false;
						        }
                            }
                            else                                // this should not happen
                            {
                                std::cerr << "unexpected file descriptor signaled?" << std::endl;
                            }
                        }
                        else
                        {
                            std::cerr << "timeout has occured" << std::endl;
                        }
                    }
                }
                else
                {
                    std::cerr << "failed to listen on socket, error: " << getLastError() << std::endl;
                }
            }
            else
            {
                std::cerr << "failed to bind socket, error: " << getLastError() << std::endl;
            }
        }
        else
        {
            std::cerr << "Socket creation failed.  error: " << getLastError() << std::endl;
        }
#ifdef __WIN
        WSACleanup();
#endif
    }

    return 0;
}


bool initWinSock()
{
    bool      bRet = false;
#ifdef __WIN
    WORD      wVerReq;
    int       nRet = 0;

    wVerReq = MAKEWORD(2, 2);
    WSADATA   wsaData;

    if (0 == (nRet = WSAStartup(wVerReq, &wsaData)))   // return zero on success...only MS would return false on success
    {
        if ((LOBYTE(wsaData.wVersion) == 2) && (HIBYTE(wsaData.wVersion) == 2))
        {
            bRet = true;
        }
        else
        {
            std::cout << "Unable to find acceptable winsock dll" << std::endl;
            WSACleanup();
        }
    }
    else
    {
        std::cout << "WsAFailed, error is: " << nRet << std::endl;
    }
#else
	bRet = true;
#endif

    return bRet;
}


int getLastError()
{
	int nRet = 0;

#ifdef __WIN
	nRet = WSAGetLastError();
#else
	nRet = errno;
#endif

	return nRet;
}

