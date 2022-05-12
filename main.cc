#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <sched.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::cerr;
using std::string;

static void run(int argc, char **argv);
static string cmd(int argc, char **argv);

int main(int argc, char **argv) {

    if (argc < 3) {
        cerr << "Too few arguments" << endl;
        exit(-1);
    }

    if (!strcmp(argv[1], "run")) {
        run(argc - 2, &argv[2]);
    }
}

static void run(int argc, char **argv) {
    cout << "Running " << cmd(argc, argv) << endl;    

    execvp(argv[0], argv); 
}

static string cmd(int argc, char **argv) {
    string cmd = "";
    for (int i = 0; i < argc; i++) {
        cmd.append(argv[i]);
    }
    return cmd;
}