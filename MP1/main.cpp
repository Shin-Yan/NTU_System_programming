#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <vector>
// #include "md5.h"
#include "loser.h"
using namespace std;

int main(int argc, char *argv[]){
	Loser loser = Loser(argc,argv);
	loser.check_params();
	loser.action();
	return 0;
}