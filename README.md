## Internship description:
I’ve completed my internship period as a software developer intern at BİTES - Defence & Aerospace Technologies. I worked directly with Ugur Melih Surme [@ugurmelihsurme](https://github.com/ugurmelihsurme).

## Overview of internship experience:
During my internship course, I’ve assigned to develop a program that transfers files using sockets and threads. The program reads and writes in binary mode to the extent of being able to read and write any file type. While structuring my code, I’ve used several design patterns, such as the factory method for creating and initializing sockets and observer (listener) pattern from behavioral patterns in order to notify the socket when the worker has exhausted itself. All of the code is written in C++ language.
In the below section, project files will be summarized in the interest of briefly explaining how the program works.
#### - main.cpp: 
When it is executed with appropriate arguments (for instance ./file_transfer -tcp -port=5000 -s -file=”pathname”) it creates the desired socket and executes the apt lines depending on whether the socket is a server socket or a client socket.
#### - include/IFile.h: 
It contains a pure virtual class of IFile class, and it’s a subclass of File. It has three different constructers, and it has read and write methods which has return types of uint8_t* in favor of consistency across different platforms.
#### - include/ISocket.h: 
This header file embodies [factory method](https://refactoring.guru/design-patterns/factory-method) as a creational design pattern and a virtual abstract class of ISocket where its subclasses [(TCPServer, TCPClient, UDPServer, UDPClient)](https://www.ibm.com/docs/en/ssw_ibm_i_74/rzab6/rzab6pdf.pdf) inherits open(), recv(), and send() methods as well as several variables which each socket requires.
#### - include/IWorker.h: 
In this header file, pure virtual class IWorker class and its subclass Worker class are implemented. This class inherits four methods accordingly, start(), run(), stop(), and setHandler() methods for the sake of initializing and running [threads](https://en.cppreference.com/w/cpp/thread/thread). Further, while using this methods a mutex and lock guard is integrated to avoid any deadlocks.
#### - include/IObserver.h: 
This file contains two pure virtual classes as IObserver and ISubject, in order to achieve a behavioral design pattern as an [observer pattern](https://refactoring.guru/design-patterns/observer).
#### - include/IHandler.h: 
It contains an IHandler class which is a necessity for Worker class to execute.
#### - include/FileReader.h: 
This header file consist of two class which are FileReader class and FileReaderSocket class. These classes benefit from the observer pattern and factory method. FileReader class becomes a publisher, and FileReaderSocket acts as a subscriber according to the observer pattern. When FileReader reads from the requested file, it notifies FileReaderSocket. Then FileReaderSocket sends the file buffer using the initially created socket. 
#### - include/FileWriter.h: 
In this header file contains the conjugate of FileReader.h header file, and it operates as the other end of the server -client- and writes the received buffer into the relevant file path.

In the source folder “src” implementations of the header files are made.

### TODO:
- [ ] creating an UI

#### GIF of the project:
![file_transfer_gif]()

### References:
1) R.Guru, https://refactoring.guru/design-patterns/factory-method, 2014.
2) IBM, https://www.ibm.com/docs/en/ssw_ibm_i_74/rzab6/rzab6pdf.pdf.
3) CPP Reference, https://en.cppreference.com/w/cpp/thread/thread, 2011.
4) R.Guru, refactoring.guru, https://refactoring.guru/design-patterns/observer, 2014.
5) S.Akkoc, Github, https://github.com/SemihAkkoc/file_transfer, 2022.
