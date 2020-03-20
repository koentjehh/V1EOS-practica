#include "shell.hh"
#include <unistd.h>
#include <syscall.h>
#include <time.h>

int main()
{ std::string input;

  // ToDo: Vervang onderstaande regel: Laad prompt uit bestand
        int fd = syscall(SYS_open, "prompt", O_RDONLY, 0755);
        char prompt[14];
        syscall(SYS_read, fd, prompt, 14); //bij meer dan 15 tekens doet het programma moeilijk

  while(true)
  { std::cout << prompt;                   // Print het prompt
    std::getline(std::cin, input);         // Lees een regel
    if (input == "new_file") new_file();   // Kies de functie
    else if (input == "ls") list();        //   op basis van
    else if (input == "src") src();        //   de invoer
    else if (input == "find") find();
    else if (input == "seek") seek();
    else if (input == "exit") return 0;
    else if (input == "quit") return 0;
    else if (input == "error") return 1;

    if (std::cin.eof()) return 0; } }      // EOF is een exit
    
//referentie: syscalls.kernelgrok.com

void new_file(){ 
    std::string bestandsnaam;
    std::string inhoud;
    std::string invoer;
    std::cout << "Geef bestandsnaam op: ";
    std::getline(std::cin, bestandsnaam);
    std::cout << "Geef inhoud voor '" << bestandsnaam << "', sluit het bestand met <EOF>:" << std::endl;

    while(invoer != "<EOF>"){
        std::getline(std::cin, invoer);
        inhoud.append(invoer + "\n");
    }

    const char* bestandsnaamc = bestandsnaam.c_str();
    const char* inhoudcst = inhoud.c_str();

    int creat = syscall(SYS_creat, bestandsnaamc, 0666);
    int fd = syscall(SYS_open, bestandsnaamc, O_WRONLY);
    char byte[1];
    syscall(SYS_write, fd, inhoudcst, strlen(inhoudcst));
    close(fd);
}

void list(){ 
    int child = syscall(SYS_fork);
        if(child == 0){
            const char* out[] = {"/bin/ls", "-la", NULL, NULL};
            syscall(SYS_execve, out[0], out, NULL);
        }else{
            syscall(SYS_wait4, child, NULL, NULL, NULL);
        }
}

void find(){
    std::string invoer;
    std::cout << "Ik zoek: ";
    std::getline(std::cin, invoer);

    const char* invoercst = invoer.c_str();

    int fd[2]; //maak pipe
    syscall(SYS_pipe, &fd);

    int fpid = syscall(SYS_fork);  //fortune child
    if(fpid = 0){
        syscall(SYS_close, fd[0]);
        syscall(SYS_dup2, fd[1], 1);
        const char * args[] = {"/usr/bin/find", ".", NULL, NULL};
        syscall(SYS_execve, args[0], args, NULL);
    }else{
        int gpid = syscall(SYS_fork);
        if(gpid == 0){
                //syscall(SYS_close, fd[1]);
                const char * args[] =  {"/usr/bin/grep", invoercst, NULL, NULL};
                syscall(SYS_dup2, fd[0], 0);
                syscall(SYS_execve, args[0], args, NULL);
        }else{
                syscall(SYS_close, fd[0]);
                syscall(SYS_close, fd[1]);
                syscall(SYS_wait4, fpid, NULL, NULL, NULL);
                syscall(SYS_wait4, gpid, NULL, NULL, NULL);
        }
    }
}

void seek(){
    std::cout << "Aanmaken...\n";
    time_t starttijd = time(NULL);

    int seek    = syscall(SYS_creat, "seek", 0666);
    int loop    = syscall(SYS_creat, "loop", 0666);
    int fdseek  = syscall(SYS_open, "seek", O_WRONLY, 0666);

    syscall(SYS_write, fdseek, "x", 1);
    syscall(SYS_lseek, fdseek, 5000000, SEEK_CUR);
    syscall(SYS_write, fdseek, "x", 1);
    close(fdseek);
    time_t stopseek = time(NULL);

    int fdloop = syscall(SYS_open, "loop", 0666);
    syscall(SYS_write, fdloop, "x",1);
    for(unsigned i = 0; i <= 5000000; i++){
        syscall(SYS_write, fdloop, "\0",1);
    }
    syscall(SYS_write, fdloop, "x",1);
    close(fdloop);
    time_t stoploop = time(NULL);

    std::cout << "Seek is aangemaakt in " << stopseek - starttijd << " sec\n";
    std::cout << "Loop is aangemaakt in " << stoploop - starttijd << " sec\n";
    /* output van ls -ls op beide files:
        8    -rw-rw-r-- 1 koen koen 5000002 mrt 20 12:53 seek
        4884 -rw-rw-r-- 1 koen koen 5000003 mrt 20 12:53 loop
    */
    }

void src() // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
{ int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
  char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
  while(syscall(SYS_read, fd, byte, 1))                   // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
    std::cout << byte; }                                  //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.
