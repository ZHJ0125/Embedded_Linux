int open_semaphore_set(key_t keyval, int numsems){
    int sid;
    if(!numsems){
        return -1;
    }
    if((sid = semget(keyval, numsems, IPC_CREAT|0666)) == -1){
        return -1;
    }
    else{
        return sid;
    }
}