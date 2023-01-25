#define ERRFORM "usage:  ./loser %s %s %s\n"
#include "loser.h"
#include "md5.h"
#include <string>
#include <cstdio>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <iostream>
using namespace std;
Loser::Loser(int argc, char* argv[]){
    for(int i = 0 ; i < argc; i++){
        string temp(argv[i]);
        params.push_back(temp);
    }
}

void Loser::print_err_msg(string type){
    if(type == "log")
        fprintf(stderr,ERRFORM,"log","<#log>","<dir>");
    if(type == "status")
        fprintf(stderr,ERRFORM,"status","<dir>","");
    if(type == "commit")
        fprintf(stderr,ERRFORM,"commit","<dir>","");

}

void Loser::print_err_msg(){
    fprintf(stderr,"usage:  ./loser %s %s\n\t./loser %s %s\n\t./loser %s %s %s\n","status","<dir>","commit","<dir>","log","<#log>","<dir>");
    return;
}

void Loser::check_params(){
    if(params.size() < 3 || params.size() > 4){
        if(params.size() == 1){
            print_err_msg();
            exit(-1);
        }
        for(auto &s:builtins){
            if(s==params[1]){
                print_err_msg(s);
                exit(-1);
            }
        }
        print_err_msg();
    }
    if(params.size() == 4){
        if(params[1]!="log"){
            if(params[1]=="status" || params[1]=="commit"){
                print_err_msg(params[1]);
                exit(-1);
            }
            else{
                print_err_msg();
                exit(-1);
            }
        }
    }
}

void Loser::action(){
    if(params[1] == "status"){
		if(chdir(params[2].c_str())!=0){
            perror(params[2].c_str());
            print_err_msg(params[1]);
            exit(-1);
        }
        else
            loser_status();
	}
	if(params[1] == "commit"){
		if(chdir(params[2].c_str())!=0){
            perror(params[2].c_str());
            print_err_msg(params[1]);
            exit(-1);
        }
        else
		    loser_commit();
	}
	if(params[1] == "log"){
		if(chdir(params[3].c_str())!=0){
            perror(params[3].c_str());
            print_err_msg(params[1]);
            exit(-1);
        }
        else
		    loser_log(stoi(params[2]));
	}
}

uint32_t Loser::count_commit(FILE* loser_record){
    uint32_t num_of_commit = 0, commit_size;
    fseek(loser_record, 0 , SEEK_SET);
    
    while(1){
        fseek(loser_record, 6 * sizeof(uint32_t), SEEK_CUR);
        if(!fread(&commit_size, sizeof(uint32_t), 1, loser_record))
            break;
        num_of_commit ++;
        fseek(loser_record,commit_size-7*sizeof(uint32_t),SEEK_CUR);
    }
    return num_of_commit;
}

uint32_t Loser::get_commit_size(Commit& commit){
    uint32_t commit_size = 7*sizeof(uint32_t);
    for(auto &s:commit.new_file)
        commit_size += sizeof(uint8_t) + s.size() * sizeof(char);
    for(auto &s:commit.modified)
        commit_size += sizeof(uint8_t) + s.size() * sizeof(char);
    for(auto &s:commit.copied){
        commit_size += sizeof(uint8_t) + s.first.size() * sizeof(char);
        commit_size += sizeof(uint8_t) + s.second.size() * sizeof(char);
    }
    for(auto &s:commit.deleted)
        commit_size += sizeof(uint8_t) + s.size() * sizeof(char);
    for(auto &s:commit.file_list)
        commit_size += sizeof(uint8_t) + s.size() * sizeof(char) + MD5_LEN * sizeof(uint8_t);
    return commit_size;
}

void Loser::list_file(vector<string>& file_list){
    string file_name;
    struct dirent* cur_dir;
    DIR* dirptr;
    if(!(dirptr = opendir("."))){
        perror("error:");
        exit(-1);
    }
    else{
        while((cur_dir = readdir(dirptr))!=NULL){
            file_name = cur_dir->d_name;
            
            if (file_name != "." && file_name != ".." && file_name != ".loser_record")
			    file_list.push_back(file_name);
        }
    }
    sort(file_list.begin(),file_list.end());
    closedir(dirptr);
}

void Loser::seek_commit(FILE* loser_record, uint32_t commit_number){
    fseek(loser_record, 0 , SEEK_SET);
    uint32_t commit_size;
    for(uint32_t i = 1 ; i < commit_number ; i++ ){
        fseek(loser_record, 6 * sizeof(uint32_t), SEEK_CUR);
        if(fread(&commit_size, sizeof(uint32_t), 1, loser_record)!=1){
            perror("error:");
            exit(-1);
        }
        fseek(loser_record,commit_size-7*sizeof(uint32_t),SEEK_CUR);
    }
    return;
}

void Loser::get_prev_commit(FILE* loser_record, uint32_t commit_number, Commit& target_commit){
    seek_commit(loser_record, commit_number);
    
    uint8_t file_name_size;
    char buffer1[FILE_NAME_MAX_LEN], buffer2[FILE_NAME_MAX_LEN];
    uint8_t md5_buffer[MD5_LEN+1] = {0};

    fread(&(target_commit.num_of_commit), sizeof(uint32_t), 1, loser_record);
    fread(&(target_commit.num_of_file), sizeof(uint32_t), 1, loser_record);
    fread(&(target_commit.num_of_add), sizeof(uint32_t), 1, loser_record);
    fread(&(target_commit.num_of_mod), sizeof(uint32_t), 1, loser_record);
    fread(&(target_commit.num_of_copy), sizeof(uint32_t), 1, loser_record);
    fread(&(target_commit.num_of_del), sizeof(uint32_t), 1, loser_record);
    fread(&(target_commit.size_of_commit), sizeof(uint32_t), 1, loser_record);

    for(uint32_t i = 0 ; i < target_commit.num_of_add ; i++){
        fread(&file_name_size, sizeof(uint8_t), 1, loser_record);
        memset(buffer1, 0 , FILE_NAME_MAX_LEN);
        fread(buffer1, sizeof(char), file_name_size, loser_record);
        target_commit.new_file.push_back(string(buffer1));
    }
    for(uint32_t i = 0 ; i < target_commit.num_of_mod ; i++){
        fread(&file_name_size, sizeof(uint8_t), 1, loser_record);
        memset(buffer1, 0 , FILE_NAME_MAX_LEN);
        fread(buffer1, sizeof(char), file_name_size, loser_record);
        target_commit.modified.push_back(string(buffer1));
    }
    for(uint32_t i = 0 ; i < target_commit.num_of_copy ; i++){
        fread(&file_name_size, sizeof(uint8_t), 1, loser_record);
        memset(buffer1, 0 , FILE_NAME_MAX_LEN);
        fread(buffer1, sizeof(char), file_name_size, loser_record);
        fread(&file_name_size, sizeof(uint8_t), 1, loser_record);
        memset(buffer2, 0 , FILE_NAME_MAX_LEN);
        fread(buffer2, sizeof(char), file_name_size, loser_record);
        target_commit.copied.push_back({string(buffer1),string(buffer2)});
    }
    for(uint32_t i = 0 ; i < target_commit.num_of_del ; i++){
        fread(&file_name_size, sizeof(uint8_t), 1, loser_record);
        memset(buffer1, 0 , FILE_NAME_MAX_LEN);
        fread(buffer1, sizeof(char), file_name_size, loser_record);
        target_commit.deleted.push_back(string(buffer1));
    }
    for(uint32_t i = 0 ; i < target_commit.num_of_file ; i++){
        fread(&file_name_size, sizeof(uint8_t), 1, loser_record);
        memset(buffer1, 0 , FILE_NAME_MAX_LEN);
        memset(md5_buffer, 0 , MD5_LEN);
        fread(buffer1, sizeof(char), file_name_size, loser_record);
        fread(md5_buffer, sizeof(uint8_t), MD5_LEN, loser_record);
        target_commit.file_list.push_back(string(buffer1));
        target_commit.file_MD5[string(buffer1)] = string((char*)md5_buffer);
    }
    return;
}

void Loser::classify_new_commit(Commit& current, Commit& previous){

    uint8_t* MD5_buffer;
    string MD5_string;
    FILE* cur_file;
    for(auto &s1: current.file_list){
        cur_file = fopen(s1.c_str(),"rb");
        MD5_buffer = md5File(cur_file);
        MD5_string = string((char*)MD5_buffer);
        current.file_MD5[s1] = MD5_string;
        const uint8_t* p1 = reinterpret_cast<const uint8_t*>(previous.file_MD5[s1].c_str());
        const uint8_t* p2 = reinterpret_cast<const uint8_t*>(MD5_string.c_str());
        // file exist
        if(find(previous.file_list.begin(), previous.file_list.end(), s1) != previous.file_list.end()){
            // MD5 not the same => modified
            if(!compare_MD5(p1,p2))
                current.modified.push_back(s1);
        }
        // file doesn't exist
        else{
            bool find_md5 = false;
            for(auto &s2:previous.file_list){
                // MD5 exist => copied
                const uint8_t* p1 = reinterpret_cast<const uint8_t*>(previous.file_MD5[s2].c_str());
                if(compare_MD5(p1,p2)){
                    current.copied.push_back({s2,s1});
                    find_md5 = true;
                    break;
                }
            }
            // MD5 doesn't exist => new file
            if(!find_md5)
                current.new_file.push_back(s1);
        }
    }
    for(auto &s:previous.file_list){
        // previous file not exist now => deleted
        if(find(current.file_list.begin(),current.file_list.end(),s)==current.file_list.end())
            current.deleted.push_back(s);
    }

    return;
}

void Loser::get_new_commit(Commit& current, Commit& previous){
    FILE* loser_record = fopen(".loser_record","rb");
    uint8_t* MD5_buffer;
    list_file(current.file_list);
    current.num_of_file = current.file_list.size();
    if(!loser_record){
        current.num_of_commit = 0;
        string MD5_string;
        FILE* cur_file;
        for(auto &s:current.file_list){
            current.new_file.push_back(s);
            cur_file = fopen(s.c_str(),"rb");
            MD5_buffer = md5File(cur_file);
            MD5_string = string((char*)MD5_buffer);
            current.file_MD5[s] = MD5_string;
        }
    }
    else{
        current.num_of_commit = count_commit(loser_record);
        get_prev_commit(loser_record, current.num_of_commit, previous);
        classify_new_commit(current, previous);

        fclose(loser_record);
    }
    sort(current.new_file.begin(), current.new_file.end());
    sort(current.modified.begin(), current.modified.end());
    sort(current.copied.begin(), current.copied.end());
    sort(current.deleted.begin(), current.deleted.end());

    current.num_of_commit++;
    current.num_of_add = current.new_file.size();
    current.num_of_mod = current.modified.size();
    current.num_of_copy = current.copied.size();
    current.num_of_del = current.deleted.size();
    current.size_of_commit = get_commit_size(current);
}

void Loser::write_commit(Commit& commit){

    FILE* loser_record = fopen(".loser_record","ab");
    uint8_t file_name_size;

    fwrite(&(commit.num_of_commit) , sizeof(uint32_t) , 1 , loser_record);
	fwrite(&(commit.num_of_file) , sizeof(uint32_t) , 1 , loser_record);
	fwrite(&(commit.num_of_add) , sizeof(uint32_t) , 1 , loser_record);
	fwrite(&(commit.num_of_mod) , sizeof(uint32_t) , 1 , loser_record);
	fwrite(&(commit.num_of_copy) , sizeof(uint32_t) , 1 , loser_record);
	fwrite(&(commit.num_of_del) , sizeof(uint32_t) , 1 , loser_record);
	fwrite(&(commit.size_of_commit) , sizeof(uint32_t) , 1 , loser_record);

    for(auto &s:commit.new_file){
        cout << s << endl;
        file_name_size = min((int)s.size(), FILE_NAME_MAX_LEN);
        fwrite(&file_name_size, sizeof(uint8_t),1,loser_record);
        fwrite(s.c_str(),sizeof(char),file_name_size,loser_record);
    }
    for(auto &s:commit.modified){
        cout << s << endl;
        file_name_size = min((int)s.size(), FILE_NAME_MAX_LEN);
        fwrite(&file_name_size, sizeof(uint8_t),1,loser_record);
        fwrite(s.c_str(),sizeof(char),file_name_size,loser_record);
    }
    for(auto &s:commit.copied){
        cout << s.first << s.second << endl;
        file_name_size = min((int)s.first.size(), FILE_NAME_MAX_LEN);
        fwrite(&file_name_size, sizeof(uint8_t),1,loser_record);
        fwrite(s.first.c_str(),sizeof(char),file_name_size,loser_record);

        file_name_size = min((int)s.second.size(), FILE_NAME_MAX_LEN);
        fwrite(&file_name_size, sizeof(uint8_t),1,loser_record);
        fwrite(s.second.c_str(),sizeof(char),file_name_size,loser_record);
    }
    for(auto &s:commit.deleted){
        cout << s << endl;
        file_name_size = min((int)s.size(), FILE_NAME_MAX_LEN);
        fwrite(&file_name_size, sizeof(uint8_t),1,loser_record);
        fwrite(s.c_str(),sizeof(char),file_name_size,loser_record);
    }
    for(auto &s:commit.file_list){
        file_name_size = min((int)s.size(), FILE_NAME_MAX_LEN);
        fwrite(&file_name_size, sizeof(uint8_t),1,loser_record);
        fwrite(s.c_str(),sizeof(char),file_name_size,loser_record);
        fwrite(commit.file_MD5[s].c_str(), sizeof(uint8_t), MD5_LEN, loser_record);
    }
    fclose(loser_record);
    return;
}

void Loser::print_commit(Commit& commit){
    cout << "[new_file]\n";
	for (auto &s:commit.new_file)
		cout << s << endl;

	cout << "[modified]\n";
	for (auto &s:commit.modified)
		cout << s << endl;

	cout << "[copied]\n";
	for (auto &s:commit.copied)
		cout << s.first << " => " << s.second << endl;

	cout << "[deleted]\n";
	for (auto &s:commit.deleted)
		cout << s << endl;
}

void Loser::print_hash(const uint8_t* md5){
    for(unsigned int i = 0 ; i <MD5_LEN ;i++)
        printf("%02x",md5[i]);
}

void Loser::loser_status(){
    get_new_commit(current, previous);
    print_commit(current);
}

void Loser::loser_commit(){
    get_new_commit(current, previous);
    write_commit(current);
}

void Loser::loser_log(int n){
    FILE* loser_record = fopen(".loser_record","rb");
    if(!loser_record)
        return;
    uint32_t num_of_commit = count_commit(loser_record);
    for(auto i = num_of_commit; (i >= num_of_commit - n + 1) && (i>=1) ; i--){
        Commit commit;
        get_prev_commit(loser_record, i, commit);
        cout << "# commit "<< i << endl;
        print_commit(commit);
        cout << "(MD5)" << endl;
        for(auto &s:commit.file_list){
            const uint8_t* p = reinterpret_cast<const uint8_t*>(commit.file_MD5[s].c_str());
            cout << s << " " ;
            print_hash(p);
            cout << endl;
        }
        if (i != num_of_commit - n + 1)
			cout << endl;
    }
    fclose(loser_record);
    return;
}