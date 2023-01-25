#ifndef LOSER_H
#define LOSER_H
#include <vector>
#include <string>
#include <map>
using namespace std;

#define FILE_NAME_MAX_LEN 255
#define MD5_LEN 16

typedef struct Commit{
    uint32_t num_of_commit, num_of_file, num_of_add, num_of_mod, num_of_copy, num_of_del, size_of_commit;
    vector<string> new_file, modified, deleted, file_list;
    vector<pair<string, string>> copied;
    map<string,string> file_MD5;
} Commit;

class Loser{
    public:
    
        Loser(int argc, char* argv[]);
        void check_params();
        void print_err_msg(string);
        void print_err_msg();
        void action();
        uint32_t count_commit(FILE*);
        uint32_t get_commit_size(Commit& commit);
        void list_file(vector<string>&);
        void seek_commit(FILE*, uint32_t);
        void get_prev_commit(FILE*, uint32_t, Commit&);
        void classify_new_commit(Commit&,Commit&);
        void get_new_commit(Commit&,Commit&);
        void write_commit(Commit&);
        void print_commit(Commit&);
        void print_hash(const uint8_t*);
        void loser_status();
        void loser_commit();
        void loser_log(int);

    private:
        
        vector<string> params;
        vector<string> builtins{"status","commit","log"};
        Commit current, previous;
        
};

#endif