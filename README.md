PROXy-TOR:
    
    [*]  This is a shared library which hijacks your normal connect system call and acts as a proxy client which enables you to communicate through another end point using the TOR network. 
    [*] This project can be used in conjunction with other system binaries like curl, ssh, wget etc.

    Usage:
        proxtor <system_call>

    Pre-requisites:
        Download the tor software on your linux machine before you use the proxtor command. 
        
        Before you use proxtor, start the tor server using the command: sudo service tor start

    Steps:
    
       [*]  Download both the proxtor.c and toralizer.h files.
    
       [*]  Grab the path of the toralizer.so file, wherever you download it.  Ex: /home/xaixane/projects/proxtor/proxtor.so
        
       [*] Replace the second line of proxtor binary with export LD_PRELOAD={place your proxtor path here}

       [*]  Place the proxtor binary in /usr/bin.
       
       [*]  Run the command chmod +755 proxtor
    
       [*]  Now you can use the proxtor binary.
        
        
    Working:
        When used in conjunction with a network system call, the shared library proxtor.so replaces the system call "connect" with an alternate version of connect which connects to the tor proxy first instead of connecting directly to the server.    It redirects the traffic recieved onto the original socket file descriptor into a proxy socket file descriptor which redirects the traffic back and forth. 
